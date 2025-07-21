#include "minishell.h"

void remove_quotes_from_input(t_minishell *minishell, int j_pos, int i_pos)
{
	char *new_input;
	int len = ft_strlen(minishell->input);
	int new_len = len - 2; // İki tırnak kaldırılacak
	int k = 0;
	
	new_input = malloc(new_len + 1);
	if (!new_input)
		return;
	// j pozisyonuna kadar kopyala (açılış tırnağı hariç)
	for (int idx = 0; idx < j_pos; idx++)
		new_input[k++] = minishell->input[idx];
	
	// j+1'den i'ye kadar kopyala (tırnak içindeki içerik)
	for (int idx = j_pos + 1; idx < i_pos; idx++)
		new_input[k++] = minishell->input[idx];
	
	// i+1'den sonrasını kopyala (kapanış tırnağı hariç)
	for (int idx = i_pos + 1; idx < len; idx++)
		new_input[k++] = minishell->input[idx];
	
	new_input[k] = '\0';
	
	// Eski input'u serbest bırak ve yenisini ata
	free(minishell->input);
	minishell->input = new_input;
}

static int	handle_dollar_in_quotes(t_minishell *minishell, int *i, t_token **current_token, int *start)
{
	char	*tmp;

	if (minishell->input[*i] == '$' && minishell->input[*i + 1] == '"')
	{
		(*i)++;
		return (1);
	}
	tmp = ft_substr(minishell->input, *start, (*i) - *start);
	if (!tmp)
		return (-1);
	*current_token = ft_calloc(sizeof(t_token), 1);
	if (!*current_token)
	{
		free(tmp);
		return (-1);
	}
	(*current_token)->value = tmp;
	(*current_token)->type = TOKEN_WORD;
	add_token_to_list(&minishell->token_list, *current_token);
	//if (money_money(minishell, i, current_token) && minishell->input[*i] == '"')
	//	return (-1);
	*start = *i;
	return (0);
}

int	handle_after_quote_text(t_minishell *minishell, int *i, int j)
{
	int		len;
	int		start_pos;
	char	*after_text;
	t_token_list	*last;
	char	*combined;

	len = 0;
	start_pos = *i + 1;
	while (minishell->input[start_pos + len] && minishell->input[start_pos + len] != ' ')
		len++;
	after_text = ft_substr(minishell->input, start_pos, len);
	if (!after_text)
		return (1);
	last = minishell->token_list;
	while (last && last->next)
		last = last->next;
	if (last)
	{
		combined = ft_strjoin(last->token->value, after_text);
		if (combined)
		{
			free(last->token->value);
			last->token->value = combined;
		}
	}
	free(after_text);
	remove_quotes_from_input(minishell, j, start_pos + len - 1);
	return (0);
}

int	merge_with_previous_token(t_minishell *minishell, t_token **current_token)
{
	t_token_list	*last;
	char			*new_value;

	last = minishell->token_list;
	while (last && last->next)
		last = last->next;
	if (last)
	{
		new_value = ft_strjoin(last->token->value, (*current_token)->value);
		if (new_value)
		{
			free(last->token->value);
			last->token->value = new_value;
		}
		free((*current_token)->value);
		free(*current_token);
	}
	else
		add_token_to_list(&minishell->token_list, *current_token);
	return (0);
}

static int	handle_quote_merging(t_minishell *minishell, int *i, t_token **current_token, int j)
{
	if (minishell->input[j - 1] == ' ' && (minishell->input[*i + 1] == ' ' || minishell->input[*i + 1] == '\0'))
	{
		add_token_to_list(&minishell->token_list, *current_token);
		(*i)++;
		return (0);
	}
	if (minishell->input[j - 1] != ' ')
	{
		merge_with_previous_token(minishell, current_token);
		if ((minishell->input[*i + 1] != ' ' && minishell->input[*i + 1] != '\0'))
		{
			handle_after_quote_text(minishell, i, j);
			while (minishell->input[*i] != ' ' && minishell->input[*i] != '\0')
				(*i)++;
		}
	}
	else if ((minishell->input[*i + 1] != ' ' && minishell->input[*i + 1] != '\0'))
	{
		remove_quotes_from_input(minishell, j, *i);
		*i = j - 2;
	}
	(*i)++;
	return (0);
}

static int	create_quote_token(t_minishell *minishell, int start, int i, t_token **current_token)
{
	char	*tmp;

	tmp = ft_substr(minishell->input, start, i - start);
	if (!tmp)
		return (1);
	*current_token = ft_calloc(sizeof(t_token), 1);
	if (!*current_token)
	{
		free(tmp);
		return (1);
	}
	(*current_token)->value = tmp;
	(*current_token)->type = TOKEN_WORD;
	(*current_token)->quotes = 1;
	return (0);
}

static int	process_quote_content(t_minishell *minishell, int *i, t_token **current_token, int *start)
{
	int	ret;

	while (minishell->input[*i] && minishell->input[*i] != '"')
	{
		if (minishell->input[*i] == '$' && minishell->input[*i + 1] 
			&& minishell->input[*i + 1] != ' ')
		{
			ret = handle_dollar_in_quotes(minishell, i, current_token, start);
			if (ret != 0)
				return (ret == -1 ? 1 : 0);					/////////////////////////
		}
		(*i)++;
	}
	if (minishell->input[*i] != '"')
	{
		write(2, "syntax error: unclosed quote\n", 29);
		minishell->exit_status = 2;
		return (1);
	}
	return (0);
}

int	double_quotes(t_minishell *minishell, int *i, t_token **current_token)
{
	int	start;
	int	j;
	int	ret;

	j = (*i);
	start = ++(*i);
	ret = process_quote_content(minishell, i, current_token, &start);
	if (ret != 0)
		return (ret);
	if (create_quote_token(minishell, start, *i, current_token))
		return (1);
	return (handle_quote_merging(minishell, i, current_token, j));
}
