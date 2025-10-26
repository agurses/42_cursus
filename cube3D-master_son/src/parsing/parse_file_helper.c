#include "../include/cub3d.h"

//int	helper(char **temp, char *line, char **lines, int count)
//{
//	temp = malloc(sizeof(char *) * (count + 2));
//	if (!temp)
//	{
//		free(line);
//		free_split(lines);
//		return (1);
//	}
//	if (lines)
//	{
//		ft_memcpy(temp, lines, sizeof(char *) * count);
//		free(lines);
//	}
//	return (0);
//}

int	helper(char **temp, char *line, char **lines, int count)
{
	int	i;

	if (!temp)
	{
		free(line);
		free_split(lines);
		return (1);
	}
	i = 0;
	if (lines)
	{
		while (i < count)
		{
			temp[i] = lines[i];
			i++;
		}
		free(lines);
	}
	return (0);
}