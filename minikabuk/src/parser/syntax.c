/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omerfarukonal <omerfarukonal@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 20:35:24 by omerfarukon       #+#    #+#             */
/*   Updated: 2025/07/29 20:40:33 by omerfarukon      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*replace_tmp_envp(char *tmp, int *j, char *value, int len)
{
	int		i;
	int		y;
	int		k;
	char	*tmp2;

	i = 0;
	y = (*j) + len + 1;
	tmp2 = malloc(ft_strlen(tmp) + ft_strlen(value) + 1 - len);
	while (tmp[i] != '$')
	{
		tmp2[i] = tmp[i];
		i++;
	}
	k = 0;
	while (value[k])
		tmp2[i++] = value[k++];
	while (tmp[y])
		tmp2[i++] = tmp[y++];
	tmp2[i] = '\0';
	*j = i - ft_strlen(value) + ft_strlen(value) - len - 1; // Point to position after replaced value
	return (tmp2);
}

char	*env_expand(t_minishell *minishell, char *tmp, int *j)
{
	char	*key;
	char	*value;
	int		key_start;

	(*j)++;
	key_start = *j - 1;  // Remember where $ was
	key = extract_env_key(tmp, j);
	if (!key)
		return (NULL);
	value = get_env_value(minishell->envp, key);
	if (!value)
		value = "";
	*j = key_start;  // Reset j to $ position
	tmp = replace_tmp_envp(tmp, j, value, ft_strlen(key));
	*j = key_start + ft_strlen(value) - 1;  // Position after the replaced value
	free(key);
	return (tmp);
}

char	*replace_tmp(char *tmp, int *j, char *status)
{
	int		i;
	int		y;
	char	*last;

	i = 0;
	last = ft_strdup(tmp + ((*j) + 2));
	while (status[i])
	{
		tmp[*j] = status[i];
		(*j)++;
		i++;
	}
	y = (*j);
	i = 0;
	while (last[i])
	{
		tmp[y] = last[i];
		y++;
		i++;
	}
	j -= ft_strlen(status) - 1;
	tmp[y] = '\0';
	return (tmp);
}

int	money_money_process(t_minishell *minishell, char *tmp, int *j)
{
	char	*status;

	status = ft_itoa(minishell->exit_status);
	if (!status)
		return (1);
	replace_tmp(tmp, j, status);
	free(status);
	return (0);
}

int	money_money(t_minishell *minishell, char **tmp)
{
	int		j;
	char	*new_tmp;

	j = 0;
	while ((*tmp)[j])
	{
		if ((*tmp)[j] == '$')
		{
			if ((*tmp)[(j) + 1] && (*tmp)[(j) + 1] == '?')
			{
				if (money_money_process(minishell, *tmp, &j))
					return (1);
				// j is already advanced by money_money_process, don't increment again
				continue;
			}
			else if ((*tmp)[(j) + 1])
			{
				new_tmp = env_expand(minishell, *tmp, &j);
				if (!new_tmp)
				{
				    // NULL dönerse boş string olarak devam et
				    new_tmp = ft_strdup("");
				}
				free(*tmp);
				*tmp = new_tmp;
				// j is already advanced by env_expand, don't increment again
				continue;
			}
		}
		j++;
	}
	return (0);
}
