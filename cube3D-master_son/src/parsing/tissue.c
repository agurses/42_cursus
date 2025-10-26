#include "../include/cub3d.h"

static char	*extract_path(char *line) // line: .cub dosyasından okunan satırdır (örneğin "NO ./textures/wall.xpm").
{
	char	*trimmed; // trimmed: satırın başındaki ve sonundaki boşlukları temizler.
	char	*path; //path: texture dosyasının yolunu tutacak.

	trimmed = ft_strtrim_whitespace(line); // ft_strtrim_whitespace → " NO ./xpm/file.xpm" gibi satırdan baş/son boşlukları kaldırır.
	if (!trimmed)
		return (0); // 
	if (ft_strncmp(trimmed, "NO ", 3) == 0) // .cub dosyasında 4 yön için texture tanımları vardır: Satırın başı "NO ", "SO ", "WE ", "EA " ile başlıyorsa "NO " kısmını atlayıp kalan kısmı ("./textures/...") alır.
		path = ft_strtrim_whitespace(trimmed + 3);
	else if (ft_strncmp(trimmed, "SO ", 3) == 0)
		path = ft_strtrim_whitespace(trimmed + 3);
	else if (ft_strncmp(trimmed, "WE ", 3) == 0)
		path = ft_strtrim_whitespace(trimmed + 3);
	else if (ft_strncmp(trimmed, "EA ", 3) == 0)
		path = ft_strtrim_whitespace(trimmed + 3);
	else
		path = NULL;
	free(trimmed);
	return (path); // Texture yolunu ("./textures/north.xpm") döndürür.
}

///////////////////////////
/////////BURAYA BAK////////
///////////////////////////
int	validate_texture_path(char *path)
{
	int	len;

	if (!path)
		return (0);
	len = ft_strlen(path);
	// .xpm uzantısı kontrolü
	if (len < 4 || ft_strcmp(path + len - 4, ".xpm") != 0)
		return (0);
	// Dosyanın gerçekten var olup olmadığını kontrol et
	int fd = open(path, O_RDONLY);
	if (fd < 0)
		return (0);
	close(fd);
	return (1);
}

static char	*extract_and_validate_path(char *line) // Texture yolunu çıkarır ve geçerli olup olmadığını kontrol eder.
{
	char	*path;

	path = extract_path(line); // extract_path ile dosya yolunu alır.
	if (!path || !validate_texture_path(path)) // validate_texture_path(path) → Dosya gerçekten mevcut mu veya .xpm uzantılı mı diye kontrol eder.
	{
		free(path); // Eğer geçersizse path serbest bırakılır (free) ve NULL döner.
		return (NULL);
	}
	return (path); // Geçerliyse dosya yolu geri döner.
}

int	parse_texture_line(char *line, t_map *map) // .cub dosyasından gelen bir satırı (örneğin "NO ./textures/north.xpm") alır.
{
	char	*path;

	path = extract_and_validate_path(line); // extract_and_validate_path ile yolu doğrular.
	if (!path)
		return (0);
	if (ft_strncmp(line, "NO ", 3) == 0) // Hangi yönün texture’ü olduğu belirlenir ve t_map yapısına kaydedilir.
		map->north_texture = path;
	else if (ft_strncmp(line, "SO ", 3) == 0)
		map->south_texture = path;
	else if (ft_strncmp(line, "WE ", 3) == 0)
		map->west_texture = path;
	else if (ft_strncmp(line, "EA ", 3) == 0)
		map->east_texture = path;
	return (1);
}

int	load_single_texture(t_game *game, t_texture *texture, char *path)
{
	texture->img = mlx_xpm_file_to_image(game->mlx.mlx_ptr, path, &texture->width, &texture->height); // mlx_xpm_file_to_image → pathteki .xpm dosyasını yükler.
	if (!texture->img)
	{
		printf("Texture Failed to Load: %s\n", path);
		return (0);
	}
	texture->data = mlx_get_data_addr(texture->img, &texture->bpp, &texture->line_len, &texture->endian); // Texture verisinin bellekteki adresini alır. Bu veriden piksel renkleri okunabilir. bpp: bit-per-pixel (her pikselin bit değeri) line_len: her satırın bayt cinsinden uzunluğu endian: byte sırası bilgisi
	return (1);
}
