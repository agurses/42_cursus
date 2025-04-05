#include "so_long.h"

int	free_tmp_map(char **tmp_map, int line_count)
{
	int i = 0;
	while (i < line_count)
	{
		free(tmp_map[i]);
		i++;
	}
	free(tmp_map);
	return (0);
}

int	read_map_lines(int fd, char **map, char **tmp_map)
{
	char *line;
	int line_count = 0;
	
	while ((line = get_next_line(fd)) != NULL)
	{
		line[ft_strcspn(line, "\n")] = 0;
		map[line_count] = line;
		tmp_map[line_count] = ft_strdup(line);
		if (!tmp_map[line_count])
		{
			free_tmp_map(tmp_map, line_count);
			return (0);
		}
		line_count++;
	}
	map[line_count] = NULL;
	tmp_map[line_count] = NULL;
	return (line_count);
}

int	allocate_maps(char ***map, char ***tmp_map, int line_count, int fd)
{
	*map = malloc(sizeof(char *) * (line_count + 1));
	if (!*map)
	{
		close(fd);
		write(2, "Error\nMemory allocation failed\n", 31);
		return (0);
	}
	*tmp_map = malloc(sizeof(char *) * (line_count + 1));
	if (!*tmp_map)
	{
		free(*map);
		close(fd);
		write(2, "Error\nMemory allocation failed\n", 31);
		return (0);
	}
	return (1);
}

int	line_counter(int fd)
{
	int		line_count;
	char	*line;

	line_count = 0;
	line = NULL;
	while ((line = get_next_line(fd)) != NULL)
		line_count++;
	return (line_count);
}

int	open_map_file(const char *filename, int *fd, int *line_count)
{
	*fd = open(filename, O_RDONLY);
	if (*fd == -1)
	{
		write(2, "Error\nCannot open map file\n", 27);
		return (0);
	}
	*line_count = line_counter(*fd);
	close(*fd);
	*fd = open(filename, O_RDONLY);
	if (*fd == -1)
	{
		write(2, "Error\nCannot open map file\n", 27);
		return (0);
	}
	return (1);
}
