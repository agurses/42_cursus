#include "../include/cub3d.h"

int	validate_map(t_game *game)
{
	printf("Map validation...\n"); // Başlangıç mesajı
	
	if (!check_valid_characters(&game->map))
		return (0);
	printf("All characters are valid\n"); // Geçerli karakterler mesajı
	
	if (!check_walls_closed(&game->map))
		return (0);
	printf("The map is surrounded by walls\n"); // Duvarlarla çevrili mesajı
	
	return (1);
}
