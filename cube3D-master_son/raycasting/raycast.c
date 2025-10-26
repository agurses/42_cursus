#include "../include/cub3d.h"

void	ray_pos(t_game *game)
{
	game->ray.map_x = (int)game->player.pos_x;
	game->ray.map_y = (int)game->player.pos_y;
}

void	ray_cast(t_game *game, int i)
{
	game->ray.camera_x = (double)((2 * i) / WIN_WIDTH) - 1;
	game->ray.ray_dir_x = game->player.dir_x +
		game->player.plane_x * game->ray.camera_x;
	game->ray.ray_dir_y = game->player.dir_y +
		game->player.plane_y * game->ray.camera_x;
}
