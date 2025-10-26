#include "../include/cub3d.h"

void	calculate_ray_steps(t_game *game)
{
	if (game->ray.ray_dir_x < 0)
	{
		game->ray.step_x = -1;
		game->ray.side_dist_x = game->player.pos_x - game->ray.map_x;
	}
	else
	{
		game->ray.step_x = 1;
		game->ray.side_dist_x = game->ray.map_x + 1 - game->player.pos_x;
	}
	// y ekseni aşağı gittikçe artıyor.
	if(game->ray.ray_dir_y < 0)
	{
		game->ray.step_y = -1;
		game->ray.side_dist_y = game->player.pos_y - game->ray.map_y;
	}
	else
	{
		game->ray.step_y = 1;
		game->ray.side_dist_y = game->ray.map_y + 1 - game->player.pos_y;
	}
}

void perform_dda(t_game *game)
{
	game->ray.delta_dist_x = fabs(1 / game->ray.ray_dir_x);
	game->ray.delta_dist_y = fabs(1 / game->ray.ray_dir_y);
	while (game->ray.hit == 0)
	{
		if (game->ray.side_dist_x < game->ray.side_dist_y)
		{
			game->ray.map_x += game->ray.step_x;
			game->ray.side_dist_x += game->ray.delta_dist_x;
			game->ray.side = 0;
		}
		else
		{
			game->ray.map_y += game->ray.step_y; 
			game->ray.side_dist_y += game->ray.delta_dist_y;
			game->ray.side = 1;
		}
		if (game->map.grid[game->ray.map_x][game->ray.map_y] == '1')
			game->ray.hit = 1;
	}
}
