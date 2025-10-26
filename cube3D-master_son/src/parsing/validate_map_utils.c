#include "../include/cub3d.h"

int	check_valid_characters(t_map *map) // harita karakterlerinin geçerliliğini kontrol eder.
{
	int	x;
	int	y;

	y = 0;
	while (y < map->height) // her satır için döngü
	{
		x = 0;
		while (map->grid[y][x]) // her karakter için döngü
		{
			if (map->grid[y][x] != '0' && map->grid[y][x] != '1'
				&& !ft_isspace(map->grid[y][x])) // geçersiz karakter kontrolü
				return (return_error("Invalid map character"));
			x++;
		}
		y++;
	}
	return (1);
}

static int	check_top_bottom_walls(t_map *map) // haritanın üst ve alt duvarlarının kapalı olduğunu kontrol eder.
{
	int	x;
	int	y;

	y = 0;
	while (y < map->height) // her satır için döngü
	{
		if (y == 0 || y == map->height - 1) // sadece ilk ve son satır için
		{
			x = 0;
			while (map->grid[y][x]) // her karakter için döngü
			{
				if (map->grid[y][x] == '0') // eğer boşluk varsa
					return (return_error("The map is not surrounded by walls"));
				x++;
			}
		}
		y++;
	}
	return (1);
}

static int	check_side_walls(t_map *map) // haritanın yan duvarlarının kapalı olduğunu kontrol eder.
{
	int	x;
	int	y;

	y = 0;
	while (y < map->height) // her satır için döngü
	{
		x = 0;
		while (map->grid[y][x] && ft_isspace(map->grid[y][x])) // satırın başındaki boşlukları atlar
			x++;
		if (map->grid[y][x] && map->grid[y][x] != '1') // ilk karakter duvar değilse
			return (return_error("The map is not surrounded by walls"));
		x = ft_strlen(map->grid[y]) - 1; // satırın sonuna gider
		while (x >= 0 && ft_isspace(map->grid[y][x])) // sondaki boşlukları atlar
			x--;
		if (x >= 0 && map->grid[y][x] != '1') // son karakter duvar değilse
			return (return_error("The map is not surrounded by walls"));
		y++;
	}
	return (1);
}

static int	check_interior_walls(t_map *map) // haritanın iç duvarlarının kapalı olduğunu kontrol eder.
{
	int	x;
	int	y;

	y = 0;
	while (y < map->height) // her satır için döngü
	{
		x = 0;
		while (map->grid[y][x]) // her karakter için döngü
		{
			if (map->grid[y][x] == '0') // boşluk karakteri ise
			{
				if (!is_wall(map, x - 1, y) || !is_wall(map, x + 1, y)
					|| !is_wall(map, x, y - 1) || !is_wall(map, x, y + 1)) // çevresinde duvar yoksa
				{
					if (x == 0 || y == 0 || y == map->height - 1
						|| x >= (int)ft_strlen(map->grid[y]) - 1) // kenarda ise
						return (return_error("The map is not surrounded by walls"));
				}
			}
			x++;
		}
		y++;
	}
	return (1);
}

int	check_walls_closed(t_map *map) // haritanın duvarlarla kapalı olduğunu kontrol eder.
{
	if (!check_top_bottom_walls(map)) // üst ve alt duvarları kontrol eder
		return (0);
	if (!check_side_walls(map)) // yan duvarları kontrol eder
		return (0);
	if (!check_interior_walls(map)) // iç duvarları kontrol eder
		return (0);
	return (1);
}
