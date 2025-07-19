#include "minishell.h"

int	add_other_token(t_token *current_token)
{
	printf("value : %s\n", current_token->value);
	printf("type : %d\n", current_token->type);
	printf("quotes : %d\n", current_token->quotes);
	return (0);
}

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

int	double_quotes(t_minishell *minishell, int *i, t_token **current_token)
{
	char	*tmp;
	int		start;
	int		j;

	j = (*i);
	start = ++(*i);
	while (minishell->input[*i] && minishell->input[*i] != '"')
	{
		if (minishell->input[*i] == '$' && minishell->input[*i + 1] 
			&& minishell->input[*i + 1] != ' ')
		{
			if (minishell->input[*i] == '$' && minishell->input[*i + 1] == '"')
			{
				(*i)++;
				break;
			}
			tmp = ft_substr(minishell->input, start, (*i) - start);
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
			add_token_to_list(&minishell->token_list, *current_token);
			if (money_money(minishell, i, current_token) && minishell->input[*i] == '"')
				return (1);
			start = *i;
		}
		(*i)++;
	}
	if (minishell->input[*i] != '"')
	{
		printf("syntax error: unclosed quote\n");
		minishell->exit_status = 2;
		return (1);
	}
	tmp = ft_substr(minishell->input, start, (*i) - start);
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
	if (minishell->input[j - 1] == ' ' && (minishell->input[*i + 1] == ' ' || minishell->input[*i + 1] == '\0'))
	{
		add_token_to_list(&minishell->token_list, *current_token);
		return(0);
	}
	if (minishell->input[j - 1] != ' ')
	{
    	t_token_list *last = minishell->token_list;
    	while (last && last->next)
    	    last = last->next;
    	if (last)
    	{
    	    char *old_value = last->token->value;
    	    char *new_value = ft_strjoin(old_value, tmp);
		
    	    if (new_value)
    	    {
    	        free(old_value);
    	        last->token->value = new_value;
    	    }
    	    // current_token'ı serbest bırak
    	    free((*current_token)->value);
    	    free(*current_token);
    	}
    	else
    	{
    	    // Liste boşsa normal ekle
    	    add_token_to_list(&minishell->token_list, *current_token);
    	}
		if ((minishell->input[*i + 1] != ' ' && minishell->input[*i + 1] != '\0'))
		{
		    int len = 0;
		    int start_pos = *i + 1;
		
		    // Uzunluğu hesapla
		    while (minishell->input[start_pos + len] && minishell->input[start_pos + len] != ' ')
		        len++;
		
		    // Sonraki kısmı al
		    char *after_text = ft_substr(minishell->input, start_pos, len);
		    if (after_text)
		    {
		        // Mevcut token ile birleştir
		        t_token_list *last = minishell->token_list;
		        while (last && last->next)
		            last = last->next;
			
		        if (last)
		        {
		            char *combined = ft_strjoin(last->token->value, after_text);
		            if (combined)
		            {
		                free(last->token->value);
		                last->token->value = combined;
		            }
		        }
			
		        free(after_text);
			
		        // Input'tan tırnakları ve sonraki kısmı kaldır
		        remove_quotes_from_input(minishell, j, start_pos + len - 1);
		        *i = j - 1;
		    }
			*i = start_pos + len - 2;
		}
	}
	else if ((minishell->input[*i + 1] != ' ' && minishell->input[*i + 1] != '\0'))
	{
		remove_quotes_from_input(minishell, j, *i);
		(*i) = j - 1;
	}
	(*i)++;
	return (0);
}

int	single_quotes(t_minishell *minishell, int *i, t_token **current_token)
{
	char	*tmp;
	int		start;

	start = ++(*i);
	while (minishell->input[*i] && minishell->input[*i] != '\'')
		(*i)++;
	if (minishell->input[*i] == '\0')
	{
		printf("syntax error: unclosed quote\n");
		minishell->exit_status = 2;
		return (1);
	}
	*current_token = ft_calloc(sizeof(t_token), 1);
	if (!*current_token)
		return (1);
	tmp = ft_substr(minishell->input, start, *i - start);
	if (!tmp)
	{
		free(*current_token);
		return (1);
	}
	(*current_token)->value = tmp;
	(*current_token)->type = TOKEN_WORD;
	add_token_to_list(&minishell->token_list, *current_token);
	(*i)++;
	return (0);
}
