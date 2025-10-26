#include "../include/cub3d.h"

int render(void *param)
{
	t_game *game;
	int i;
	int y;

	game = param;
	mlx_clear_window(game->mlx.mlx_ptr, game->mlx.win_ptr);
	i = 0;
	while (i < WIN_WIDTH)
	{
		ray_cast(game, i);
		ray_pos(game);
		calculate_ray_steps(game);
		perform_dda(game);
		draw_wall_column(game, i);
		wall_size(game);
		wall_draw_height(game);
		y = get_wall_color(game);
		while (y < draw_end)
		{
			mlx_pixel_put(game->mlx.mlx_ptr, game->mlx.win_ptr, x, y, color);
			y++;
		}
		i++;
	}

}

