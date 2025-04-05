#include "so_long.h"

int check_move_for_door(t_game *game, int x, int y)
{
	// Eğer oradaki karakter collectible ise say
	if (game->map[y][x] == 'C')
	{
		game->collectible_count--;
		printf("Collectible alındı! Kalan: %d\n", game->collectible_count);
	}
	
	if (game->map[y][x] == 'E')
	{
		// Eğer kapı varsa ve collectiblelar toplandıysa oyunu bitir
		if (game->collectible_count <= 0)
		{
			printf("Tüm collectible'lar toplandı, oyun bitiyor!\n");
			ft_free_for_img(game);
			ft_free_map(game);
			free(game);
			exit(0);
		}
		else
		{
			printf("Henüz tüm collectible'lar toplanmadı! Kalan: %d\n", game->collectible_count);
			return (1);
		}
	}
	return (1);
}

int ft_free_for_img(t_game *game)
{
	if (game->mlx)
	{
		// t_img yapınızdaki tüm görüntüleri temizleyin
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
		
		// Window'u temizle
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
