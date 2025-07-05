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

char	*read_txt()
{
	
}

int	processor_redirect_in(t_minishell *minishell, pid_t *pids, int **fd, t_token_list **token_list)
{
	t_token_list	*tmp;

	tmp = *token_list;
	while(tmp->token->type != TOKEN_REDIRECT_IN)
		tmp = tmp->next;
	tmp = tmp->next;
	read_txt()
	dup2(fd[0], STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
}

int	handle_redirect_or_heredoc(t_minishell *minishell, t_token_list **token_list)
{
//	char	*path;
	int		**fd;
	pid_t	*pids;
	int		ret;
	t_token_list *tmp;

	tmp = *token_list;
	malloc_pid_redirect(&fd, &pids, minishell);
	if (!fd || !pids)
		return (1);
	while (tmp && (tmp->token->type != TOKEN_REDIRECT_IN || 
					tmp->token->type != TOKEN_REDIRECT_OUT || 
					tmp->token->type != TOKEN_APPEND || 
					tmp->token->type != TOKEN_HEREDOC))
	tmp = tmp->next;
	if (tmp->token->type == TOKEN_REDIRECT_IN) //<
	{
		ret = processor_redirect_in(minishell, pids, fd, token_list);
	}
	else if (tmp->token->type == TOKEN_REDIRECT_OUT)
	{
		ret = processor_redirect_out();
	}
	else if (tmp->token->type == TOKEN_APPEND)//>>
	{
		ret = processor_append();
	}
	else if (tmp->token->type == TOKEN_HEREDOC)
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
