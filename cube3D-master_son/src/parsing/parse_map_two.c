#include "../include/cub3d.h"

int	get_map_width(char **grid) // harita ızgarasının genişliğini belirler.
{
	int	max_width; // max_width: haritanın en geniş satırının genişliğini tutacak.
	int	width; // width: her satırın genişliğini geçici olarak tutacak.
	int	y; // y: satır indeksini tutacak.

	max_width = 0; // başlangıçta en geniş genişlik 0.
	y = 0; // satır indeksini 0'dan başlat.
	while (grid[y]) // her satır için döngü
	{
		width = ft_strlen(grid[y]); // satırın uzunluğunu alır.
		if (width > max_width) // eğer bu satır en genişse
			max_width = width; // max_width'u günceller.
		y++; // sonraki satıra geçer.
	}
	return (max_width); // en geniş genişliği döner.
}

static int	count_map_height(char **lines, int start) // haritanın yüksekliğini belirler.
{
	int	i; // i: satır indeksini tutacak.
	int	map_height; // map_height: haritanın yüksekliğini tutacak.

	map_height = 0; // başlangıçta harita yüksekliği 0.
	i = start; // satır indeksini başlangıç satırına ayarlar.
	while (lines[i]) // satır sonuna kadar döngü
	{
		if (!is_empty_line(lines[i])) // eğer satır boş değilse
			map_height++; // harita yüksekliğini artırır.
		i++; // sonraki satıra geçer.
	}
	return (map_height); // harita yüksekliğini döner.
}

static char	**build_map_grid(char **lines, int start, int map_height) // harita ızgarasını oluşturur.
{
	char	**map_grid; // map_grid: harita ızgarasını tutacak.
	int		i; // i: satır indeksini tutacak.

	map_grid = malloc(sizeof(char *) * (map_height + 1)); // harita yüksekliğine göre bellek tahsisi yapar.
	if (!map_grid) // eğer tahsis başarısızsa
		return (NULL); // NULL döner.
	i = 0; // satır indeksini 0'dan başlat.
	while (i < map_height) // her satır için döngü
	{
		map_grid[i] = ft_strdup(lines[start + i]); // satırı kopyalar.
		if (!map_grid[i]) // eğer kopyalama başarısızsa
		{
			free_split(map_grid);
			return (NULL);
		}
		i++;
	}
	map_grid[map_height] = NULL; // sonlandırıcı NULL ekler.
	return (map_grid); // harita ızgarasını döner.
}

int	parse_map(char **lines, int start, t_game *game) // harita verilerini ayrıştırır ve t_game yapısına atar.
{
	int		map_height; // map_height: haritanın yüksekliğini tutacak.
	char	**map_grid; // map_grid: harita ızgarasını tutacak.

	map_height = count_map_height(lines, start); // harita yüksekliğini belirler.
	if (map_height == 0) // eğer harita yüksekliği 0 ise
		return (return_error("Empty Map")); // hata döner.
	map_grid = build_map_grid(lines, start, map_height); // harita ızgarasını oluşturur.
	if (!map_grid) // eğer oluşturma başarısızsa
		return (return_error("Memory allocation failed"));
	game->map.grid = map_grid; // harita ızgarasını t_game yapısına atar.
	game->map.height = map_height; // harita yüksekliğini t_game yapısına atar.
	game->map.width = get_map_width(map_grid); // harita genişliğini t_game yapısına atar.
	printf("✓ Map size: %dx%d\n", game->map.width, game->map.height); // konsola yazdırır.
	if (!find_player_position(&game->map, &game->player)) // oyuncu pozisyonunu bulur.
		return (0); // eğer bulunamazsa hata döner.
	printf("✓ player position: (%.1f, %.1f) Direction: (%.1f, %.1f)\n",
		game->player.pos_x, game->player.pos_y,
		game->player.dir_x, game->player.dir_y); // konsola yazdırır.
	return (1);
}
