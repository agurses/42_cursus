#include "executor.h"

char	**current_token(t_token_list *tmp)
{
	char	**current_token;

	current_token = malloc(sizeof(char *) * 2);
	if (!current_token)
		return (NULL);
	current_token[0] = tmp->token->value;
	current_token[1] = NULL;
	return (current_token);
}

void	check_builtin(t_minishell *minishell)
{
	char **cmd;
		
	cmd = current_token(minishell->token_list);
	if (!ft_strcmp(cmd[0], "echo"))
		exit(ft_echo(cmd));
	else if(!ft_strcmp(cmd[0], "pwd"))
		exit(ft_pwd(cmd));
	else if(!ft_strcmp(cmd[0], "env"))
		exit(ft_env(cmd));
	execve(get_path(minishell), current_token(minishell), minishell->envp->value);
	exit (1);
}


