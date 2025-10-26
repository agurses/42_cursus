#include "../include/cub3d.h"

int	check_file_extension(char *filename)
{
	int	len;

	if (!filename)
		return (0);
	len = ft_strlen(filename);
	if (len < 4)
		return (0);
	if (ft_strcmp(filename + len - 4, ".cub") != 0)
		return (0);
	return (1);
}

int	is_empty_line(char *line)
{
	int	i;

	if (!line)
		return (1);
	i = 0;
	while (line[i])
	{
		if (!ft_isspace(line[i]))
			return (0);
		i++;
	}
	return (1);
}

int	is_map_line(char *line)
{
	int	i;

	if (!line || is_empty_line(line))
		return (0);
	i = 0;
	while (line[i])
	{
		if (!ft_isspace(line[i] && line[i] != '0' && line[i] != '1'
				&& line[i] != 'N' && line[i] != 'S' && line[i] != 'E'
				&& line[i] != 'W'))
			return (0);
		i++;
	}
	return (1);
}

char	**read_file_lines(int fd)//görevi: Bir dosyadaki tüm satırları (line’ları) okuyup bir char ** dizisine atmak.
{
	char	*line; // get_next_line(fd)` ile okunan tek bir satır.  
	char	**lines; //şu ana kadar okunan tüm satırları tutan dizi
	char	**temp; //yeni satır ekleneceği zaman geçici dizi (yeniden allocate etmek için).
	int		count; // kaç satır okunduğunu
	int		checker;

	lines = NULL;
	count = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		temp = malloc(sizeof(char *) * (count + 2)); // Yeni bir geçici dizi (temp) oluşturulur. Bu dizi, mevcut satır sayısına (count) bir eklenerek genişletilir. Ekstra bir eleman, yeni satır ve NULL sonlandırıcısı için ayrılır.
		checker = helper(temp, line, lines, count);
		if (checker)
			return (NULL);
		temp[count] = line; // Yeni satır (line), temp dizisinin sonuna eklenir.
		temp[count + 1] = NULL; 
		lines = temp;
		count++;
	}
	return (lines);
}
