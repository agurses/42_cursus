#include "minishell.h"

// Function to check if current command has redirects
static int	has_redirect_in_current_command(t_token_list *token_list)
{
	t_token_list	*tmp;
	
	tmp = token_list;
	while (tmp && tmp->token->type != TOKEN_PIPE)
	{
		if (tmp->token->type == TOKEN_REDIRECT_IN || 
			tmp->token->type == TOKEN_REDIRECT_OUT ||
			tmp->token->type == TOKEN_APPEND ||
			tmp->token->type == TOKEN_HEREDOC)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

static void execute_pipe_builds(t_minishell *minishell, char **cmd)
{
	if (!ft_strcmp(cmd[0], "env"))
		minishell->exit_status = ft_env(minishell);
	else if (!ft_strcmp(cmd[0], "pwd"))
		minishell->exit_status = ft_pwd();
	else if (!ft_strcmp(cmd[0], "echo"))
		minishell->exit_status = process_for_echo(&minishell->token_list);
	else if (!ft_strcmp(cmd[0], "export"))
		minishell->exit_status = ft_export(minishell);
	else if (!ft_strcmp(cmd[0], "cd"))
		minishell->exit_status = ft_cd(minishell);
	else if (!ft_strcmp(cmd[0], "unset"))
		minishell->exit_status = ft_unset(minishell, *cmd);
	else if (!ft_strcmp(cmd[0], "exit"))
		minishell->exit_status = ft_exit(minishell);
	exit(minishell->exit_status);
}

void execute_pipe_child(t_minishell *minishell)
{
	char **cmd;
	char *path;
	struct stat	st;

	// Handle redirects only for this child process
	if (has_redirect_in_current_command(minishell->token_list))
	{
		handle_redirect_for_current_command(minishell, &minishell->token_list);
		exit(minishell->exit_status);
	}
	
	cmd = current_token(minishell->token_list);
	if (!ft_strcmp(cmd[0], "env") || !ft_strcmp(cmd[0], "pwd")
		|| !ft_strcmp(cmd[0], "echo") || !ft_strcmp(cmd[0], "export")
		|| !ft_strcmp(cmd[0], "cd") || !ft_strcmp(cmd[0], "unset")
		|| !ft_strcmp(cmd[0], "exit"))
		execute_pipe_builds(minishell, cmd);
	else
	{
		path = get_path(minishell->envp, cmd[0]);
		if (!path && is_dot(cmd))
		{
			if (access(cmd[0], F_OK) == 0)
				path = ft_strdup(cmd[0]);
		}
		if (stat(path, &st) == 0 && is_dot(cmd))
		{
			if (S_ISDIR(st.st_mode))
			{
				write(2, "minishell: ", 11);
				write(2, cmd[0], ft_strlen(cmd[0]));
				write(2, ": is a directory\n", 17);
				free(path);
				exit(126);
			}
			else if (!(st.st_mode & S_IXUSR))
			{
				write(2, "minishell: ", 11);
				write(2, cmd[0], ft_strlen(cmd[0]));
				write(2, ": Permission denied\n", 20);
				free(path);
				exit(126);
			}
		}
		else if(is_dot(cmd))
		{
			write(2, "minishell: ", 11);
			write(2, cmd[0], ft_strlen(cmd[0]));
			write(2, ": No such file or directory\n", 28);
			free(path);
			exit(127);
		}
		if (!path)
		{
			write(2, "minishell: ", 11);
			write(2, cmd[0], ft_strlen(cmd[0]));
			write(2, ": command not found\n", 20);
			exit(127);
		}
		cmd = ft_same_tokens(&minishell->token_list);
		minishell->exit_status = execve(path, cmd, make_env_array(minishell));
		if (minishell->exit_status == -1)
		{
			perror("minishell");
			minishell->exit_status = 126;
		}
		free(path);
		exit(minishell->exit_status);
	}
}

static void	setup_pipe_and_fork(t_minishell *minishell, int i, pid_t *pids, int **fd)
{
    if (i < minishell->count->pipe_count)
        pipe(fd[i]);
    pids[i] = fork();
    if (pids[i] == 0)
    {
        set_default_signals();
        // Set up input/output redirections for this specific child
        if (i > 0)
            dup2(fd[(i - 1)][0], STDIN_FILENO);
        if (i < minishell->count->pipe_count)
			dup2(fd[i][1], STDOUT_FILENO);
        execute_pipe_child(minishell);
    }
}

void	processor(t_minishell *minishell, pid_t *pids, int **fd)
{
    int				i;
    t_token_list	*tmp;

    i = 0;
    tmp = minishell->token_list;
    while (i < minishell->count->pipe_count + 1)
    {
        minishell->token_list = tmp;
        setup_pipe_and_fork(minishell, i, pids, fd);
		if (i > 0)
            close(fd[i - 1][0]);
        if (i < minishell->count->pipe_count)
            close(fd[i][1]);
        if (tmp)
        {
            while (tmp && tmp->token->type != TOKEN_PIPE)
                tmp = tmp->next;
            if (tmp && tmp->token->type == TOKEN_PIPE)
            {    
				tmp = tmp->next;
				if (!tmp)
				{
					minishell->token_list = NULL;
					perror("minishell");
					break ;
				}
			}
        }
        i++;
    }
}

int	execute_pipe_line(t_minishell *minishell, int i)
{
	int		**fd;
	pid_t	*pids;
	int		status;
	int		first_error_status;
	int		child_failed;
	int		completed_processes;
	int		saved_stdout;
	int		temp_pipe[2];

	status = 0;
	first_error_status = 0;
	child_failed = 0;
	completed_processes = 0;
	minishell->exit_status = malloc_fd_and_pid(&fd, &pids, minishell);
	if (minishell->exit_status)
		return (1);
	
	// Create a temporary pipe to capture output
	if (pipe(temp_pipe) == -1)
	{
		perror("pipe");
		return (1);
	}
	
	// Save original stdout and redirect to temp pipe
	saved_stdout = dup(STDOUT_FILENO);
	dup2(temp_pipe[1], STDOUT_FILENO);
	close(temp_pipe[1]);
	
	set_ignore_signals();
	processor(minishell, pids, fd);
	
	// Close all pipe file descriptors in parent
	while (i < minishell->count->pipe_count)
	{
		close(fd[i][0]);
		close(fd[i][1]);
		i++;
	}
	
	// Wait for all processes to complete, but check for errors immediately
	while (completed_processes < minishell->count->pipe_count + 1 && !child_failed)
	{
		pid_t finished_pid = waitpid(-1, &status, 0);
		if (finished_pid > 0)
		{
			completed_processes++;
			// Find which process this was
			int process_index = -1;
			for (int j = 0; j < minishell->count->pipe_count + 1; j++)
			{
				if (pids[j] == finished_pid)
				{
					process_index = j;
					break;
				}
			}
			
			if (WIFEXITED(status) && process_index >= 0)
			{
				int exit_status = WEXITSTATUS(status);
				// If this is the first error, save it and kill remaining processes
				if (exit_status != 0 && !child_failed)
				{
					first_error_status = exit_status;
					child_failed = 1;
					// Kill all remaining child processes immediately
					for (int j = 0; j < minishell->count->pipe_count + 1; j++)
					{
						if (j != process_index)
						{
							kill(pids[j], SIGKILL);
						}
					}
					// Wait for killed processes to clean up
					for (int j = 0; j < minishell->count->pipe_count + 1; j++)
					{
						if (j != process_index)
						{
							waitpid(pids[j], NULL, 0);
						}
					}
					break;
				}
				// Only update exit status if no error occurred yet
				if (!child_failed)
					minishell->exit_status = exit_status;
			}
		}
	}
	
	// Restore original stdout
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdout);
	
	// If no error occurred, output the captured output
	if (!child_failed)
	{
		char buffer[4096];
		ssize_t bytes_read;
		close(temp_pipe[1]);
		while ((bytes_read = read(temp_pipe[0], buffer, sizeof(buffer) - 1)) > 0)
		{
			buffer[bytes_read] = '\0';
			write(STDOUT_FILENO, buffer, bytes_read);
		}
	}
	
	close(temp_pipe[0]);
	
	// Set the exit status to the first error encountered
	if (child_failed)
		minishell->exit_status = first_error_status;
	
    i = 0;
    while (i < minishell->count->pipe_count)
        free(fd[i++]);
    free(fd);
    free(pids);
	return (0);
}
