#include "so_long.h"

int check_move_for_door(t_game *game, int x, int y)
{
	if (game->map[y][x] == 'C')
	{
		game->collectible_count--;
		printf("Collectible received! Remaining: %d\n", game->collectible_count);
	}
	
	if (game->map[y][x] == 'E')
	{
		if (game->collectible_count <= 0)
		{
			printf("All collectibles are collected, WP!\n");
			ft_free_for_img(game);
			ft_free_map(game);
			//mlx_destroy_display(game->mlx); // bu yorum satırı 42 de geri açılacak
			free(game);
			exit(0);
		}
		else
			printf("Not all collectibles collected! Remaining: %d\n", game->collectible_count);
	}
	return (1);
}

int ft_free_for_img(t_game *game)
{
	if (game->mlx)
	{
		if (game->img->player)
			mlx_destroy_image(game->mlx, game->img->player);
		if (game->img->wall)
			mlx_destroy_image(game->mlx, game->img->wall);
		if (game->img->collectible)
			mlx_destroy_image(game->mlx, game->img->collectible);
		if (game->img->exit)
			mlx_destroy_image(game->mlx, game->img->exit);
		if (game->img->floor)
			mlx_destroy_image(game->mlx, game->img->floor);
		if (game->win)
			mlx_destroy_window(game->mlx, game->win);
	}
	free(game->img);
	return (1);
}

int ft_free_map(t_game *game)
{
	int i;

	i = 0;
	while (game->map[i] != NULL)
	{
		free(game->map[i]);
		i++;
	}
	free(game->map);
	return (0);
}

int	free_both_maps(char **map, char **tmp_map, int line_count)
{
	int i = 0;
	while (i < line_count)
	{
		free(map[i]);
		i++;
	}
	free(map);
	i = 0;
	while (i < line_count)
	{
		free(tmp_map[i]);
		i++;
	}
	free(tmp_map);
	return (0);
}
