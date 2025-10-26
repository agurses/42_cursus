#include "../include/cub3d.h"

int	load_textures(t_game *game)
{
	printf("Textures are loading...\n");
	if (!game->map.north_texture || !game->map.south_texture
		|| !game->map.east_texture || !game->map.west_texture)
		return (return_error("All tissues must be (NO, SO, EA, WE)")); // Eğer .cub dosyasında dört yönün (NO, SO, EA, WE) biri eksikse hata verir.
	if (!load_single_texture(game, &game->textures.north, // load_single_texture() → .xpm dosyasını okur ve MLX image objesi oluşturur. Aynı işlemler diğer yönler için de tekrarlanır
			game->map.north_texture))
		return (return_error("North texture could not be loaded"));
	printf("North texture: %s (%dx%d)\n", game->map.north_texture,
		game->textures.north.width, game->textures.north.height);
	if (!load_single_texture(game, &game->textures.south,
			game->map.south_texture))
		return (return_error("South texture could not be loaded")); // Güney duvarı yüklenir. Başarısız olursa hata, başarılıysa bilgi yazdırılır.
	printf("South texture: %s (%dx%d)\n", game->map.south_texture,
		game->textures.south.width, game->textures.south.height);
	if (!load_single_texture(game, &game->textures.east,
			game->map.east_texture))
		return (return_error("East texture could not be loaded")); //  Doğu duvarı yüklenir ve bilgisi yazılır.
	printf("East texture: %s (%dx%d)\n", game->map.east_texture,
		game->textures.east.width, game->textures.east.height);
	if (!load_single_texture(game, &game->textures.west,
			game->map.west_texture))
		return (return_error("West texture could not be loaded")); // Batı duvarı yüklenir ve bilgisi yazılır.
	printf("West texture: %s (%dx%d)\n", game->map.west_texture,
		game->textures.west.width, game->textures.west.height);
	return (1);
}
