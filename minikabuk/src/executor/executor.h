#ifndef EXECUTOR_H
# define EXECUTOR_H

#include "minishell.h"

//builtin.c
int		ft_echo(char *current_token);
int		ft_env(t_minishell *minishell);
int		ft_pwd();

//builtin_2.c
int		ft_cd(char *current_token);
int		ft_export(t_minishell *minishell);
int		ft_unset(t_minishell *minishell, char *current_token);
int		ft_exit(t_minishell *minishell);

//exec_cmd_2.c
void	check_builtin(t_minishell *minishell);
char	**current_token(t_token_list *tmp);

//exec_cmd.c
void	execute_command(t_minishell *minishell);
int		has_redirect_or_heredoc(t_minishell *minishell);
void	execute_in_parent(char *cmd, t_minishell *minishell);

//executor_utils.c
void	malloc_fd_and_pid(int ***fd, pid_t **pids, t_minishell *minishell);
int		free_for_exit(t_minishell *minishell);
int		ft_cd_util(char *current_token, char *cwd, char *new_path);
int		process_for_echo(t_token_list **tmp);
int		is_pipeline(t_minishell *minishell);

//pipe.c
int		execute_pipe_line(t_minishell *minishell, int i);

//redirection.c
void	handle_redirect_or_heredoc(t_minishell *minishell, t_token_list **tmp, char **cmd);
char	*get_path(t_env *envp, char *cmd);
void	free_cmd_path(char **cmd_path, int i);


#endif