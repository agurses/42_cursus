/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves_key.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agurses <agurses@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 07:02:00 by agurses           #+#    #+#             */
/*   Updated: 2025/04/08 07:04:52 by agurses          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	move_right(t_game *game)
{
	if (game->player_x + 1 < game->map_width
		&& game->map[game->player_y][game->player_x + 1] != '1'
		&& check_move_for_door(game, game->player_x + 1, game->player_y) == 1)
	{
		if (game->map[game->player_y][game->player_x]
			== game->map[game->door_y][game->door_x])
			game->map[game->player_y][game->player_x] = 'E';
		else
			game->map[game->player_y][game->player_x] = '0';
		game->player_x++;
		game->map[game->player_y][game->player_x] = 'P';
		game->moment_count++;
		ft_printf("Score: %d\n", game->moment_count);
		return (1);
	}
	return (0);
}

int	move_left(t_game *game)
{
	if (game->player_x - 1 > 0
		&& game->map[game->player_y][game->player_x - 1] != '1'
		&& check_move_for_door(game, game->player_x - 1, game->player_y) == 1)
	{
		if (game->map[game->player_y][game->player_x]
			== game->map[game->door_y][game->door_x])
			game->map[game->player_y][game->player_x] = 'E';
		else
			game->map[game->player_y][game->player_x] = '0';
		game->player_x--;
		game->map[game->player_y][game->player_x] = 'P';
		game->moment_count++;
		ft_printf("Score: %d\n", game->moment_count);
		return (1);
	}
	return (0);
}

int	move_up(t_game *game)
{
	if (game->player_y - 1 > 0
		&& game->map[game->player_y - 1][game->player_x] != '1'
		&& check_move_for_door(game, game->player_x, game->player_y - 1) == 1)
	{
		if (game->map[game->player_y][game->player_x]
			== game->map[game->door_y][game->door_x])
			game->map[game->player_y][game->player_x] = 'E';
		else
			game->map[game->player_y][game->player_x] = '0';
		game->player_y--;
		game->map[game->player_y][game->player_x] = 'P';
		game->moment_count++;
		ft_printf("Score: %d\n", game->moment_count);
		return (1);
	}
	return (0);
}

int	move_down(t_game *game)
{
	if (game->player_y + 1 < game->map_height
		&& game->map[game->player_y + 1][game->player_x] != '1'
		&& check_move_for_door(game, game->player_x, game->player_y + 1) == 1)
	{
		if (game->map[game->player_y][game->player_x]
			== game->map[game->door_y][game->door_x])
			game->map[game->player_y][game->player_x] = 'E';
		else
			game->map[game->player_y][game->player_x] = '0';
		game->player_y++;
		game->map[game->player_y][game->player_x] = 'P';
		game->moment_count++;
		ft_printf("Score: %d\n", game->moment_count);
		return (1);
	}
	return (0);
}

int	key_input(int keycode, t_game *game)
{
	if (keycode == 65307)
	{
		ft_free_for_img(game);
		ft_free_map(game);
		mlx_destroy_display(game->mlx);
		free(game->mlx);
		free(game);
		exit(0);
	}
	else if (keycode == 119 || keycode == 65362)
		move_up(game);
	else if (keycode == 115 || keycode == 65364)
		move_down(game);
	else if (keycode == 97 || keycode == 65361)
		move_left(game);
	else if (keycode == 100 || keycode == 65363)
		move_right(game);
	render_map(game, 0, 0);
	return (0);
}
