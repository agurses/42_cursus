/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agurses <agurses@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 07:20:12 by agurses           #+#    #+#             */
/*   Updated: 2025/04/08 07:21:30 by agurses          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	count_map_elements(char **map, t_game *game, int col, int row)
{
	row = 0;
	while (row < game->map_height)
	{
		col = 0;
		while (col < game->map_width)
		{
			if (map[row][col] == 'P')
			{
				game->player_count++;
				game->player_x = col;
				game->player_y = row;
			}
			else if (map[row][col] == 'E')
			{	
				game->door_y = row;
				game->door_x = col;
				game->door_count++;
			}
			else if (map[row][col] == 'C')
				game->collectible_count++;
			col++;
		}
		row++;
	}
}

int	check_map_borders(char **map, t_game *game)
{
	int	col;
	int	row;

	col = 0;
	while (col < game->map_width)
	{
		if (map[0][col] != '1' || map[(game->map_height) - 1][col] != '1')
		{
			write(2, "Error\nMap must be surrounded by walls\n", 38);
			return (0);
		}
		col++;
	}
	row = 0;
	while (row < game->map_height)
	{
		if (map[row][0] != '1' || map[row][game->map_width - 1] != '1')
		{
			write(2, "Error\nMap must be surrounded by walls\n", 38);
			return (0);
		}
		row++;
	}
	return (1);
}
