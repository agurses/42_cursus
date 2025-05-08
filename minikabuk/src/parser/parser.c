#include "minishell.h"

void	add_token_to_list(t_token_list **token_list, t_token *current_token)
{
	t_token_list	*new_node;
	t_token_list	*temp;

	new_node = malloc(sizeof(t_token_list));
	if (!new_node)
	{
		free(current_token->value);
		free(current_token);
		return ;
	}
	new_node->token = current_token;
	new_node->next = NULL;
	if (!*token_list)
		*token_list = new_node;
	else
	{
		temp = *token_list;
		while (temp->next)
			temp = temp->next;
		temp->next = new_node;
	}
}

void	count_tokens(t_minishell *minishell)
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

void	compare_tokens(t_token *current_token)
{
	if (ft_strcmp(current_token->value, "<") == 0)
		current_token->type = TOKEN_REDIRECT_IN;
	else if (ft_strcmp(current_token->value, ">") == 0)
		current_token->type = TOKEN_REDIRECT_OUT;
	else if (ft_strcmp(current_token->value, ">>") == 0)
		current_token->type = TOKEN_APPEND;
	else if (ft_strcmp(current_token->value, "<<") == 0)
		current_token->type = TOKEN_HEREDOC;
	else if (ft_strcmp(current_token->value, "|") == 0)
		current_token->type = TOKEN_PIPE;
	//else if (ft_strcmp(current_token->value, "$") == 0)
	//	handle_env_variable(current_token);
	//else if (ft_strcmp(current_token->value, "\'") == 0)
	//	handle_single_quote(current_token);  
	//else if (ft_strcmp(current_token->value, "\"") == 0)
	//	handle_double_quote(current_token);
	else
		current_token->type = TOKEN_WORD;
}

void	parse_tokens(t_minishell *minishell)
{
	t_token_list	*tmp;

	tmp = minishell->token_list;
	while (tmp)
	{
		compare_tokens(tmp->token);
		tmp = tmp->next;
	}
	count_tokens(minishell);
}
