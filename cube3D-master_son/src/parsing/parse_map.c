#include "../include/cub3d.h"

static void	set_player_direction_vector(t_player *player, char direction) // oyuncunun yön vektörünü ayarlar.
{
	if (direction == 'N') // kuzey yönü için
	{
		player->dir_x = 0; // dikey bileşen
		player->dir_y = -1; // yatay bileşen
	}
	else if (direction == 'S') // güney yönü için
	{
		player->dir_x = 0; // dikey bileşen
		player->dir_y = 1; // yatay bileşen
	}
	else if (direction == 'E') // doğu yönü için
	{
		player->dir_x = 1;
		player->dir_y = 0;
	}
	else if (direction == 'W') // batı yönü için
	{
		player->dir_x = -1;
		player->dir_y = 0;
	}
}

////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////
/// player->plane_x ve player->plane_y değerleri güncellenebilir olmalı
////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////


static void	set_player_plane_vector(t_player *player, char direction) // oyuncunun kamera düzlemi vektörünü ayarlar.
{
	if (direction == 'N')
	{
		player->plane_x = 0.66; // dikey bileşen
		player->plane_y = 0; // yatay bileşen
	}
	else if (direction == 'S')
	{
		player->plane_x = -0.66;
		player->plane_y = 0;
	}
	else if (direction == 'E')
	{
		player->plane_x = 0;
		player->plane_y = 0.66;
	}
	else if (direction == 'W')
	{
		player->plane_x = 0;
		player->plane_y = -0.66;
	}
}

void	init_player_direction(t_player *player, char direction) // oyuncunun yön ve kamera düzlemi vektörlerini başlatır.
{
	set_player_direction_vector(player, direction); // yön vektörünü ayarlar
	set_player_plane_vector(player, direction); // kamera düzlemi vektörünü ayarlar
}

static int	process_player_at(t_map *map, t_player *player, int x, int y, int *found) // belirli bir konumda oyuncu başlangıç pozisyonunu işler.
{
	char	direction;

	direction = map->grid[y][x]; // konumdaki karakteri alır (N, S, E, W)
	if (*found)
		return (return_error("Multiple player starting positions")); // zaten bir başlangıç pozisyonu bulunduysa hata döner
	player->pos_x = x + 0.5; // oyuncunun x pozisyonunu ayarlar (merkeze yerleştirmek için 0.5 ekler)
	player->pos_y = y + 0.5; // oyuncunun y pozisyonunu ayarlar
	map->grid[y][x] = '0'; // harita ızgarasında bu konumu boş alan olarak işaretler
	init_player_direction(player, direction); // oyuncunun yönünü başlatır
	*found = 1; // oyuncu başlangıç pozisyonunun bulunduğunu işaretler
	return (1);
}

int	find_player_position(t_map *map, t_player *player) // harita üzerinde oyuncu başlangıç pozisyonunu bulur ve işler.
{
	int	x; // x koordinatı
	int	y; // y koordinatı
	int	found; // oyuncu başlangıç pozisyonunun bulunup bulunmadığını izler

	found = 0; // başlangıçta bulunmadı olarak ayarlanır
	y = 0; // y koordinatını başlatır
	while (y < map->height) // harita yüksekliği boyunca döner
	{
		x = 0; // x koordinatını başlatır
		while (map->grid[y][x]) // satır sonuna kadar döner
		{
			if (map->grid[y][x] == 'N' || map->grid[y][x] == 'S' // oyuncu başlangıç pozisyonu karakterlerini kontrol eder
				|| map->grid[y][x] == 'E' || map->grid[y][x] == 'W') // oyuncu başlangıç pozisyonu karakterlerini kontrol eder
			{
				if (!process_player_at(map, player, x, y, &found)) // oyuncu pozisyonunu işler
					return (0);
			}
			x++; // x koordinatını artırır
		}
		y++; // y koordinatını artırır
	}
	if (!found)
		return (return_error("Player starting position not found")); // oyuncu başlangıç pozisyonu bulunamadıysa hata döner
	return (1);
}
