/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agurses <agurses@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 07:14:55 by agurses           #+#    #+#             */
/*   Updated: 2025/04/08 07:51:54 by agurses          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	load_image(t_game *game)
{
	game->img->player = mlx_xpm_file_to_image(game->mlx,
			"textures/slime.xpm", &game->img->width, &game->img->height);
	game->img->wall = mlx_xpm_file_to_image(game->mlx,
			"textures/walls.xpm", &game->img->width, &game->img->height);
	game->img->collectible = mlx_xpm_file_to_image(game->mlx,
			"textures/chest.xpm", &game->img->width, &game->img->height);
	game->img->exit = mlx_xpm_file_to_image(game->mlx,
			"textures/wooden_door.xpm", &game->img->width, &game->img->height);
	game->img->floor = mlx_xpm_file_to_image(game->mlx,
			"textures/wooden_floor.xpm", &game->img->width, &game->img->height);
}

void	*render_for_img(t_game *game, int i, int j)
{
	void	*rendered_img;

	rendered_img = NULL;
	if (game->map[j][i] == '1')
		rendered_img = game->img->wall;
	else if (game->map[j][i] == 'P')
		rendered_img = game->img->player;
	else if (game->map[j][i] == 'C')
		rendered_img = game->img->collectible;
	else if (game->map[j][i] == 'E')
		rendered_img = game->img->exit;
	else if (game->map[j][i] == '0')
		rendered_img = game->img->floor;
	return (rendered_img);
}

int	render_map(t_game *game, int i, int j)
{
	static int	img_loaded;
	void		*rendered_img;

	rendered_img = NULL;
	if (img_loaded == 0)
	{
		load_image(game);
		img_loaded = 1;
	}
	while (j < game->map_height)
	{
		i = 0;
		while (i < game->map_width)
		{
			rendered_img = render_for_img(game, i, j);
			if (rendered_img)
				mlx_put_image_to_window(game->mlx,
					game->win, rendered_img, i * 64, j * 64);
			i++;
		}
		j++;
	}
	return (0);
}
