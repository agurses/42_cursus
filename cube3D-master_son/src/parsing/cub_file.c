#include "../include/cub3d.h"

static char	**read_and_validate_file(char *file)
{
	int		fd;
	char	**lines;

	if (!check_file_extension(file))
	{
		return_error("Invalid file extension. (should be .cub)");
		return (NULL);
	}
	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		return_error("File cannot open!");
		return (NULL);
	}
	lines = read_file_lines(fd);
	close(fd);
	if (!lines)
	{
		return_error("File cannot read!");
		return (NULL);
	}
	return (lines);
}

static int	parse_elements(char **lines, t_game *game, int *map_start)
{
	int	i;

	i = 0;
	*map_start = -1;
	while (lines[i])
	{
		if (is_empty_line(lines[i]))
		{
			i++;
			continue ;
		}
		if (is_map_line(lines[i]))
		{
			*map_start = i;
			break ;
		}
		if (!parse_texture_line(lines[i], &game->map)
			&& !parse_color_line(lines[i], &game->colors))
		{
			return (return_error("Invalid elements line"));
		}
		i++;
	}
	return (1);
}

static int	parse_map_and_validate(char **lines, int map_start, t_game *game)
{
	if (map_start == -1 || !parse_map(lines, map_start, game))
		return (return_error("Error Map Parsing!"));
	return (1);
}

static int	parse_elements_and_map(char **lines, t_game *game)
{
	int	map_start;
	
	if (!parse_elements(lines, game, &map_start))
	{
		free_split(lines);
		return (0);
	}
	if (!parse_map_and_validate(lines, map_start, game))
	{
		free_split(lines);
		return (0);
	}
	free_split(lines);
	return (1);
}

int	parse_cub_file(char *file, t_game *game)
{
	char	**lines;

	lines = read_and_validate_file(file);
	if (!lines)
		return (0);
	if (!parse_elements_and_map(lines, game))
		return (0);
	return (1);
}
