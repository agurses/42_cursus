#include "minishell.h"

void	free_cmd_path(char **cmd_path, int i)
{
	while (cmd_path[i])
	{
		free(cmd_path[i]);
		i++;
	}
	free(cmd_path);
}

char	*get_path(t_env *envp, char *cmd)
{
	char	**paths;
	char	*path;
	t_env	*tmp_env;
	int		i;

	i = 0;
	tmp_env = envp;
	while (tmp_env)
	{
		if (!ft_strcmp(tmp_env->key, "PATH"))
		{
			paths = ft_split(tmp_env->value, ':');
			if (!paths)
				return (NULL);
			while (paths[i])
			{
				path = ft_strjoin(paths[i], "/");
				path = ft_strjoin(path, cmd);
				if (access(path, X_OK) == 0)
				{
					free_cmd_path(paths, i);
					return (path);
				}
				i++;
			}
			free_cmd_path(paths, i);
		}
		tmp_env = tmp_env->next;
	}
	return (NULL);
}

char	*process_env(t_minishell *minishell, char *cmd, char **cmd_path)
{
	t_env	*tmp_env;

	tmp_env = minishell->envp;
	while (tmp_env)
	{
		if (!ft_strcmp(tmp_env->key, cmd))
		{
			*cmd_path = get_path(minishell->envp, cmd);
			return (tmp_env->value);
		}
		tmp_env = tmp_env->next;
	}
	if (!tmp_env)
		ft_printf("minishell: %s: No such file or directory\n", cmd);
	return (NULL);
}

void	malloc_pid_redirect(int ***fd, pid_t **pids, t_minishell *minishell)
{
	int	i;

	i = 0;
	*pids = (pid_t *)ft_calloc(sizeof(pid_t), (minishell->count->redir_in_count +
												minishell->count->redir_out_count +
												minishell->count->append_count +
												minishell->count->heredoc_count + 1));
	if (!*pids)
		return;
	*fd = (int **)ft_calloc(2, sizeof(int *));
	if (!(*fd))
	{
		free(*pids);
		return ;
	}
	while (i < 2)
	{
		(*fd)[i] = (int *)ft_calloc(2, sizeof(int));
		if (!(*fd)[i])
		{
			while (i-- >= 0)
				free((*fd)[i]);
			free(*pids);
			free(fd);
			return ;
		}
		i++;
	}
}

int	processor_redirect_in(t_minishell *minishell, pid_t *pids, int **fd, char **cmd)
{
	//	char	*path;
	t_token_list	*tmp;
	t_token_list	*last;

	tmp = minishell->token_list;
	last = tmp;
	while(last ==)
	{

	}
	fd = open();
	if (fd == -1)
	{
		perror("minishell");
		minishell->exit_status = 1;
		exit(1);
	}
	if (!(!ft_strcmp(cmd[0], "cd") || 
		!ft_strcmp(cmd[0], "export") ||
		!ft_strcmp(cmd[0], "unset") || 
		!ft_strcmp(cmd[0], "exit")))
	{
		
	}

	cmd = current_token(tmp);
	if (i < (minishell->count->redir_in_count + 1))
		pipe(fd[i % 2]);
	pids[i] = fork();
	if (pids[i] == 0 && !(!ft_strcmp(cmd[0], "cd") || 
		!ft_strcmp(cmd[0], "export") ||
		!ft_strcmp(cmd[0], "unset") || 
		!ft_strcmp(cmd[0], "exit")))
    {
		set_default_signals();
        if (i > 0)
        {
            dup2(fd[(i - 1) % 2][0], STDIN_FILENO);
            close(fd[(i - 1) % 2][1]);
        }
        if (i < minishell->count->redir_in_count)
        {
            dup2(fd[i % 2][1], STDOUT_FILENO);
            close(fd[i % 2][0]);
        }
        execute_redirect_herodoc_child(minishell);
    }
	else if (pids[i] > 0)
	{
		if (!ft_strcmp(cmd[0], "cd") || !ft_strcmp(cmd[0], "export")
			|| !ft_strcmp(cmd[0], "unset") || !ft_strcmp(cmd[0], "exit"))
			execute_in_parent(cmd[0], minishell);
	}
    if (tmp)
    {
		while (tmp && !(tmp->token->type == TOKEN_REDIRECT_IN))
			tmp = tmp->next;
		if (tmp && (tmp->token->type == TOKEN_REDIRECT_IN))
            tmp = tmp->next;
    }
	//set_ignore_signals();
	////processor_redirect(minishell, pids, fd);
	//
	//path = get_path(minishell->envp, cmd[0]);
	//cmd = ft_same_tokens(tmp);
	//execve(path, cmd, make_env_array(minishell));
	//exit(1);
}

int	handle_redirect_or_heredoc(t_minishell *minishell, t_token_list **tmp, char **cmd)
{
//	char	*path;
	int		**fd;
	pid_t	*pids;
	int		ret;

	malloc_pid_redirect(&fd, &pids, minishell);
	if (!fd || !pids)
		return (1);
	cmd = ft_same_tokens(tmp);
	printf("%s\n", cmd[0]);
	printf("%s\n", cmd[1]);
	if ((*tmp)->next->token->type == TOKEN_REDIRECT_IN) //<
	{
		ret = processor_redirect_in(minishell, pids, fd, cmd);
	}
	else if ((*tmp)->next->token->type == TOKEN_REDIRECT_OUT)
	{
		ret = processor_redirect_out();
	}
	else if ((*tmp)->next->token->type == TOKEN_APPEND)//>>
	{
		ret = processor_append();
	}
	else if ((*tmp)->next->token->type == TOKEN_HEREDOC)
	{
		ret = processor_heredoc();
	}
	return(ret);
//  ""
	//set_ignore_signals();
	////processor_redirect(minishell, pids, fd);
	//
	//path = get_path(minishell->envp, cmd[0]);
	//cmd = ft_same_tokens(tmp);
	//execve(path, cmd, make_env_array(minishell));
	//exit(1);
	return (0);
}


int execute_redirect_herodoc_child(t_minishell *minishell)
{
	char **cmd;
	char *path;

	printf("burada\n");
	cmd = current_token(minishell->token_list);
	if (!ft_strcmp(cmd[0], "env"))
		exit(ft_env(minishell));
	else if (!ft_strcmp(cmd[0], "pwd"))
		exit(ft_pwd());
	else if (!ft_strcmp(cmd[0], "echo"))
		exit(process_for_echo(&minishell->token_list));
	else
	{
		path = get_path(minishell->envp, cmd[0]);
		if (!path)
		{
			ft_printf("minishell: %s: command not found\n", cmd[0]);
			return (127);
		}
		if (execve(path, cmd, make_env_array(minishell)) == -1)
		{
			perror("minishell");
			exit(126);
		}
		else
			exit(0);
	}
}
