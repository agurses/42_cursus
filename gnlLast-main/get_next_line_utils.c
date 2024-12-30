/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakbas <nakbas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 16:44:51 by nakbas            #+#    #+#             */
/*   Updated: 2024/12/30 15:44:03 by nakbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	str_len(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*str_find_nl(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return ((char *)&str[i]);
		i++;
	}
	return (NULL);
}

void	*buf_calloc(size_t buffersize)
{
	char	*ptr;
	size_t	i;

	i = 0;
	ptr = malloc(buffersize * sizeof(char));
	if (!ptr)
		return (NULL);
	while (i < (buffersize))
	{
		ptr[i] = '\0';
		i++;
	}
	return (ptr);
}

char	*str_join(char *buffer, char *str)
{
	char	*joinedstr;
	int		i;
	int		j;
	int		total;

	total = str_len(buffer) + str_len(str);
	i = 0;
	joinedstr = malloc(sizeof(char) * (total + 1));
	if (!joinedstr || !buffer || !str)
		return (NULL);
	while (buffer[i])
	{
		joinedstr[i] = buffer[i];
		i++;
	}
	j = 0;
	while (str[j])
	{
		joinedstr[i] = str[j];
		j++;
		i++;
	}
	joinedstr[total] = '\0';
	free(buffer);
	return (joinedstr);
}
