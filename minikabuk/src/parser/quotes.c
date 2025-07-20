#include "minishell.h"

int	single_quotes(t_minishell *minishell, int *i, t_token **current_token)
{
	char	*tmp;
	int		start;

	start = ++(*i);
	while (minishell->input[*i] && minishell->input[*i] != '\'')
		(*i)++;
	if (minishell->input[*i] == '\0')
	{
		error_msg("syntax error: unclosed quote", NULL, 2);
		minishell->exit_status = 2;
		return (1);
	}
	*current_token = ft_calloc(sizeof(t_token), 1);
	if (!*current_token)
	{
		error_errno("malloc", 1);
		return (1);
	}
	tmp = ft_substr(minishell->input, start, *i - start);
	if (!tmp)
	{
		free(*current_token);
		error_errno("malloc", 1);
		return (1);
	}
	(*current_token)->value = tmp;
	(*current_token)->type = TOKEN_WORD;
	add_token_to_list(&minishell->token_list, *current_token);
	(*i)++;
	return (0);
}
