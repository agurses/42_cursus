#include "../include/cub3d.h"

void	clean_game(t_game *game)
{
	printf("Cleaning continues... \n");
	free_map(&game->map);
	if (game->mlx.mlx_ptr)
		free_textures(&game->textures, game->mlx.mlx_ptr);
	close_mlx(game);
	printf("Clean is done");
}
