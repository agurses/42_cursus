#include "include/cub3d.h"

int	setup(t_game *game)
{
	ft_memset(game, 0, sizeof(t_game));
	init_game(game);
	if (!init_mlx(game))
	{
		clean_game(game);
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_game	game;
	int		result;

	(void)argv;
	if (argc != 2)
	{
		print_error("Error. Invalid input\n");
		return (1);
	}
	result = setup(&game);
	if (!parse_cub_file(argv[1], &game))
	{
		clean_game(&game);
		return (1);
	}
	if (result)
		return (1);
	printf("cub3D Started!\n");
	printf("Window Size: %dx%d\n", WIN_WIDTH, WIN_HEIGHT);
	printf("You can exit with ESC\n");
	mlx_loop(game.mlx.mlx_ptr);
	return (0);
}
