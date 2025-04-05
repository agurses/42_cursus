#include "so_long.h"

int	close_window(t_game *game)
{
	ft_free_for_img(game);
	ft_free_map(game);
	free(game);
	exit(0);
}

t_game	*init_game(void)
{
	t_game	*game;

	game = (t_game *)malloc(sizeof(t_game));
	if (!game)
		return (NULL);
	game->img = (t_img *)malloc(sizeof(t_img));
	if (!game->img)
	{
		free(game);
		return (NULL);
	}
	game->mlx = mlx_init();
	game->collectible_count = 0;
	game->player_count = 0;
	game->moment_count = 0;
	game->door_count = 0;
	game->img->player = NULL;
	game->img->wall = NULL;
	game->img->collectible = NULL;
	game->img->exit = NULL;
	game->img->floor = NULL;
	game->img->height = 0;
	game->img->width = 0;
	return (game);
}

int	main(int ac, char **arg)
{
	t_game	*game;

	game = NULL;
	if (ac != 2)
	{
		write(2, "Error\n", 6);
		return (0);
	}
	game = init_game();
	if (ft_map_reader(arg[1], game) == 0)
	{
		ft_free_for_img(game);
		free(game);
		write(2, "Error\n", 6);
		return (0);
	}
	game->win = mlx_new_window(game->mlx, game->map_width * 64, game->map_height * 64 , "so_long");
	render_map(game, 0, 0);
	mlx_hook(game->win, 2, 1L<<0, key_input, game);  // 2 = KeyPress olayı
	mlx_hook(game->win, 17, 0, close_window, game);  // 17 = Pencere kapatma olayı
	mlx_loop(game->mlx);
	return (0);
}
