#include "minishell.h"

void	malloc_fd_and_pid(int ***fd, pid_t **pids, t_minishell *minishell)
{
	int	i;

	i = 0;
	*pids = (pid_t *)ft_calloc(sizeof(pid_t), (minishell->count->pipe_count + 1));
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
		*fd = (int **)ft_calloc(2, sizeof(int));
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

char	**current_token(t_minishell *minishell)
{
	static t_token_list *tmp;
	char	**current_token;

	current_token = malloc(sizeof(char *) * 2);
	if (!current_token)
		return (NULL);
	tmp = minishell->token_list;
	if (tmp->token->type == TOKEN_PIPE)
		tmp = tmp->next;
	while (tmp)
	{
		if (tmp->token->type != TOKEN_PIPE)
		{
			current_token[0] = tmp->token->value;
			current_token[1] = NULL;
			tmp = tmp->next;
			return (current_token);
		}
	}
	return (NULL);
}

void	check_builtin(t_minishell *minishell)
{
	char **cmd;

	cmd = current_token(minishell);
	if (!ft_strcmp(cmd[0], "echo"))
		exit(ft_echo(cmd));
	else if(!ft_strcmp(cmd[0], "pwd"))
		exit(ft_pwd(cmd));
	else if(!ft_strcmp(cmd[0], "env"))
		exit(ft_env(cmd));
	execve(get_path(minishell), current_token(minishell), minishell->envp);
	exit (1);
}

void	processor(t_minishell *minishell, pid_t *pids, int **fd)
{
	int	i;

	i = 0;
	while (i < minishell->count->pipe_count + 1)
	{
		if (i < minishell->count->pipe_count)
			pipe(fd[i % 2]);
		pids[i] = fork();
		if (pids[i] == 0)
		{
			if (i > 0)
			{
				dup2(fd[(i - 1) % 2][0], STDIN_FILENO);
				close(fd[(i - 1) % 2][1]);
			}
			if (i < minishell->count->pipe_count)
			{
				dup2(fd[i % 2][1], STDOUT_FILENO);
				close(fd[i % 2][0]);
			}
			check_builtin(minishell);	
		}
		i++;
	}
}

int execute_pipeline(t_minishell *minishell, int i)
{
	int	**fd;
	pid_t *pids;

	malloc_fd_and_pid(&fd, &pids, minishell);
	if (!fd || !pids)
		return (1);
	processor(minishell, pids, fd);
	while (i <minishell->count->pipe_count)
	{
		close(fd[i % 2][0]);
		close(fd[i % 2][1]);
		i++;
	}
	i = 0;
	while (i < minishell->count->pipe_count + 1)
	{
		waitpid(pids[i], NULL, 0);
		i++;
	}
	free(pids);
    free(fd[0]);
    free(fd[1]);
    free(fd);
	return (0);
}

int	is_pipeline(t_minishell *minishell)
{
	t_token_list	*tmp;

	tmp = minishell->token_list;
	while (tmp)
	{
		if (tmp->token->type == TOKEN_PIPE)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

void analyze_command(t_minishell *minishell)
{
	t_token_list	*tmp;

	tmp = minishell->token_list;
	while (tmp)
	{
		if (tmp->token->type == TOKEN_PIPE)
			minishell->count->pipe_count++;
		else if (tmp->token->type == TOKEN_REDIRECT_IN)
			minishell->count->redir_in_count++;
		else if (tmp->token->type == TOKEN_REDIRECT_OUT)
			minishell->count->redir_out_count++;
		else if (tmp->token->type == TOKEN_APPEND)
			minishell->count->append_count++;
		else if (tmp->token->type == TOKEN_HEREDOC)
			minishell->count->heredoc_count++;
		tmp = tmp->next;
	}
}

void	execute_command(t_minishell *minishell)
{
	calloc_minishell(minishell);
	if (!minishell->count)
        return;
	analyze_command(minishell);

	if (is_pipeline(minishell))
	{
		if (execute_pipeline(minishell, 0))  // Yeni process'ler
		{
			ft_printf("Execute Error");
		}
		return;
	}
	else
	{
		execute_single_command(minishell);  // Tek child process
	}
}
