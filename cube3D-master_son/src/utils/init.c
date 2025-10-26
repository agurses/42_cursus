#include "../include/cub3d.h"

static void	init_game_player(t_game *game)
{
	game->player.pos_x = 0.0; //oyuncunun haritadaki başlangıç koordinatları (daha sonra haritadan okunur).
	game->player.pos_y = 0.0; //bakış yönü vektörü.
	game->player.dir_x = -1.0; //Burada (-1, 0) demek, oyuncu sola (batıya) bakıyor demektir.
	game->player.dir_y = 0.0; //kamera düzlemi (raycasting’te FOV’u belirler).
	game->player.plane_x = 0.0;
	game->player.plane_y = 0.66; //0.66, genelde 66° görüş açısına denk gelir.
	game->player.move_speed = MOVE_SPEED;
	game->player.rot_speed = ROT_SPEED;
}

static void	init_game_map(t_game *game)
{
	game->map.grid = NULL; //haritayı temsil eden 2D karakter dizisidir (1, 0, N, S)
	game->map.width = 0; //en
	game->map.height = 0; //boy
	game->map.north_texture = NULL;
	game->map.south_texture = NULL;
	game->map.east_texture = NULL;
	game->map.west_texture = NULL;
	//texture duvar yüzeylerinde kullanılacak XPM dosyalarının yolları
}

static void	init_game_colors(t_game *game)
{
	game->colors.floor_red = 0; // floor zemin renkleri
	game->colors.floor_green = 0;
	game->colors.floor_blue = 0;
	game->colors.ceiling_red = 0; // ceiling tavan renkleri
	game->colors.ceiling_green = 0;
	game->colors.ceiling_blue = 0;
	game->colors.ceiling_color = 0;
	game->colors.floor_color = 0;
}

void	init_game(t_game *game)
{
	init_game_player(game);
	init_game_map(game);
	init_game_colors(game);
	printf("Oyun Yapısı Başlatıldı. \n");
}
