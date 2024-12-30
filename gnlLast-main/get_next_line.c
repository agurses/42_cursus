/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakbas <nakbas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 16:44:54 by nakbas            #+#    #+#             */
/*   Updated: 2024/12/30 15:59:18 by nakbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_nl(char *buf)
{
	int		i;
	char	*temp;
	int		count;

	i = 0;
	count = 0;
	if (!buf[i])
		return (NULL);
	while (buf[i] && buf[i] != '\n')
		i++;
	if (buf[i] == '\n')
		i++;
	temp = (char *)malloc((sizeof(char) * (i)) + 1);
	if (!temp)
		return (NULL);
	while (count < i)
	{
		temp[count] = buf[count];
		count++;
	}
	temp[count] = '\0';
	return (temp);
}

char	*continuing_nl(char *buffer)
{
	int		i;
	char	*newline;
	int		count;

	i = 0;
	count = 0;
	if (!buffer)
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i] || !buffer[i + 1])
		return (free(buffer), NULL);
	newline = (char *)malloc(sizeof(char) * (str_len(buffer) - i));
	if (!newline)
		return (NULL);
	i++;
	while (buffer[i])
		newline[count++] = buffer[i++];
	newline[count] = '\0';
	free(buffer);
	return (newline);
}

char	*read_file(int fd, char *buffer)
{
	int		read_number;
	char	*str;

	read_number = 1;
	str = buf_calloc(BUFFER_SIZE + 1);
	if (!buffer)
		buffer = buf_calloc(1);
	while (read_number > 0)
	{
		read_number = read(fd, str, BUFFER_SIZE);
		if (read_number < 0)
			return (free(buffer), NULL);
		str[read_number] = '\0';
		buffer = str_join(buffer, str);
		if (str_find_nl(str))
			read_number = -1;
	}
	free(str);
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*completed;	

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = read_file(fd, buffer);
	completed = get_nl(buffer);
	buffer = continuing_nl(buffer);
	return (completed);
}
