#include "executor.h"

void	execute_in_parent(char *cmd, t_minishell *minishell)
{
	if (ft_strcmp(cmd, "cd") == 0)
		ft_cd(cmd);
	else if (ft_strcmp(cmd, "export") == 0)
		ft_export(minishell);
	else if (ft_strcmp(cmd, "unset") == 0)
		ft_unset(minishell, cmd);
	else if (ft_strcmp(cmd, "exit") == 0)
		ft_exit(minishell);
}

int	has_redirect_or_heredoc(t_minishell *minishell)
{
	if (minishell->count->heredoc_count > 0)
		return(1);
	else if(minishell->count->append_count > 0)
		return (1);
	else if(minishell->count->redir_in_count > 0)
		return (1);
	else if(minishell->count->redir_out_count > 0)
		return (1);
	return (0);
}

char	**make_env_array(t_minishell *minishell)
{
    char	**env_array;
    t_env	*tmp;
    int		i;
    int		size;
    char	*temp;

    size = 0;
    tmp = minishell->envp;
    while (tmp && ++size)
        tmp = tmp->next;
    env_array = malloc(sizeof(char *) * (size + 1));
    if (!env_array)
        return (NULL);
    i = 0;
    tmp = minishell->envp;
    while (tmp)
    {
        temp = ft_strjoin(tmp->key, "=");
        env_array[i] = ft_strjoin(temp, tmp->value);
        free(temp);
        tmp = tmp->next;
        i++;
    }
    env_array[i] = NULL;
    return (env_array);
}

void	execute_no_pipe(t_minishell *minishell, t_token_list *tmp)
{
	char			**cmd;
	pid_t			pid;
	char			*path;

	while(tmp)
	{
		cmd = current_token(tmp);
		if (!ft_strcmp(cmd[0], "cd") || !ft_strcmp(cmd[0], "export") ||
			!ft_strcmp(cmd[0], "unset") || !ft_strcmp(cmd[0], "exit"))
			execute_in_parent(cmd[0], minishell);
		else
		{
			pid = fork();
			if (pid == 0)
			{
				if (has_redirect_or_heredoc(minishell))
					handle_redirect_or_heredoc(minishell, &tmp, cmd);
				//if(is_others(cmd))
				//	exit(execute_builtin(cmd));
				path = get_path(minishell->envp, cmd[0]);
				execve(path, cmd, make_env_array(minishell));
				exit(1);
			}
			waitpid(pid, NULL, 0);
		}
		tmp = tmp->next;
	}
}

void	execute_command(t_minishell *minishell)
{
	t_token_list	*tmp;
	
	tmp = minishell->token_list;
	if (is_pipeline(minishell))
	{
		if (execute_pipe_line(minishell, 0))
			ft_printf("Execute Error");
	}
	else
		execute_no_pipe(minishell, tmp);
	return;
}
