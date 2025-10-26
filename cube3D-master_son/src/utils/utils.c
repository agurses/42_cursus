#include "../include/cub3d.h"

int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\r'
		|| c == '\v' || c == '\f');
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

char	*ft_strtrim_whitespace(char *str)
{
	int		start;
	int		end;
	char	*result;
	int		i;

	if (!str)
		return (NULL);
	start = 0;
	while (str[start] && ft_isspace(str[start]))
		start++;
	end = ft_strlen(str) - 1;
	while (end > start && ft_isspace(str[end]))
		end--;
	result = malloc(end - start + 2);
	if (!result)
		return (NULL);
	i = 0;
	while (start <= end)
		result[i++] = str[start++];
	result[i] = '\0';
	return (result);
}

int	is_wall(t_map *map, int x, int y)
{
	if (y < 0 || y >= map->height)
		return (0);
	if (x < 0 || x >= (int)ft_strlen(map->grid[y]))
		return (0);
	if (ft_isspace(map->grid[y][x]))
		return (0);
	return (map->grid[y][x] == '1');
}
