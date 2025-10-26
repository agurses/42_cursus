#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <errno.h>
//# include "../minilibx-linux/mlx.h"
# include "../mlx_mac/mlx.h"
# include "../libft/libft.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10

# endif

# define WIN_WIDTH 1280
# define WIN_HEIGHT 720
# define MOVE_SPEED 0.05
# define ROT_SPEED 0.05

# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_ESC 65307
# define KEY_LEFT 65361
# define KEY_UP 65362
# define KEY_RIGHT 65363
# define KEY_DOWN 65364

typedef struct s_colors
{
	int	floor_red; //zemin
	int	floor_green;
	int	floor_blue;

	int	ceiling_red; //tavan
	int	ceiling_green;
	int	ceiling_blue;

	int	floor_color; //zeminin birleşik rengini alcağımız zaman
	int	ceiling_color;
}	t_colors;

//doku yapısı
typedef struct s_texture
{
	void	*img;
	char	*data; //Görüntünün ham piksel verisi
	int		width;
	int		height;
	int		bpp; // “Bits per pixel” — her pikselin kaç bit ile ifade edildiğini belirtir (genelde 32).
	int		line_len; // Görüntüde bir satırın (row) bellekte kapladığı byte uzunluğu.
	int		endian; // Sistem “endianness” türü (0: little endian, 1: big endian). Piksel byte sırası için kullanılır.
}	t_texture;

//dokular
typedef struct s_textures
{
	t_texture	north;
	t_texture	south;
	t_texture	east;
	t_texture	west;
}	t_textures;

//harita
typedef struct s_map
{
	char	**grid; // Haritanın 2D karakter dizisi (örnek: '1' = duvar, '0' = boşluk, 'P' = oyuncu).
	int		width;
	int		height;
	char	*north_texture; //Kuzey duvarı için doku (XPM) dosya yolu.
	char	*south_texture;
	char	*east_texture;
	char	*west_texture;
}	t_map;

//oyuncu yapısı
typedef struct s_player
{
	double	pos_x; // Oyuncunun X konumu (haritada)
	double	pos_y;
	double	dir_x; // Oyuncunun bakış yönü (X bileşeni)
	double	dir_y;
	double	plane_x;// Kamera düzlemi (X bileşeni)
	double	plane_y;
	double	move_speed; // Yürüme hızı
	double	rot_speed; // dönme hızı
}	t_player;

//ray yapısı
typedef struct s_ray
{
	double	camera_x; // -1 ile +1 arasında, ekranın sol–sağ konumunu temsil eder (kolon oranı).
	double	ray_dir_y; //Işının yön vektörü (oyuncunun bakış yönü + kamera düzlemi).
	double	ray_dir_x;
	double	side_dist_x; // Işının bir sonraki x veya y duvarına olan mesafesi.
	double	side_dist_y;
	double	delta_dist_x; // Işının bir kare ilerlediğinde ne kadar mesafe kat ettiğini gösterir.
	double	delta_dist_y;
	double	wall_dist; // Dikey olarak düzeltilmiş (perpendicular) duvar mesafesi. duvarın ekrandaki yüksekliği buna göre hesaplanır.
	double	wall_x;
	int		map_x; // Işının şu anda bulunduğu harita karesi (x,y).
	int		map_y;
	int		step_x; // Işının X ve Y yönünde ilerleme yönü (+1 veya -1).
	int		step_y;
	int		hit; // Işın bir duvara çarptı mı? (0 → hayır, 1 → evet).
	int		side; // Hangi yönde çarptı? (0 → X yönü, 1 → Y yönü).
	int		line_height; // Ekranda çizilecek duvarın yüksekliği (piksel cinsinden).
	int		draw_start; // Duvarın ekranda çizileceği dikey aralık (y başlangıç ve bitiş).
	int		draw_end;
	int		tex_x; // Duvardaki hangi doku sütununun (texture column) kullanılacağı.
}	t_ray;

// ana oyun yapısı
typedef struct s_mlx
{
	void	*mlx_ptr; // MinilibX kütüphanesinin ana bağlantısı mlx_init()
	void	*win_ptr; // Açılan pencereye işaretçi. mlx_new_window()
	void	*img_ptr; // Görüntü nesnesine işaretçi. mlx_new_image()
	char	*img_data; // Görüntünün ham piksel verisi (byte dizisi).
	int		bits_per_pixel; // Her pikselin kaç bit’le temsil edildiğini gösterir (32)
	int		line_length; // Görüntüde bir satırın (row) bellekte kaç byte tuttuğu.
	int		endian; // Byte sırası (0: little endian, 1: big endian).
	int		win_width;
	int		win_height;
}	t_mlx;

typedef struct s_game
{
	t_mlx		mlx; // Ekrana çizim yapabilmek için gerekli MLX context’leri içerir.
	t_map		map; // 2D grid, doku yolları (north_texture vs.), genişlik–yükseklik.
	t_player	player; // Pozisyon, yön, hız, dönüş açısı.
	t_ray		ray; // Her frame’de hesaplanan raycasting değişkenleri.
	t_textures	textures; // Yönlere göre XPM dosyalarından yüklenen duvar resimleri.
	t_colors	colors; // Zemin ve tavan renkleri (floor/ceiling RGB).
}	t_game;

typedef struct s_color_parse_result
{
    char	*trimed;
    char	*values;
    int		red;
    int		green;
    int		blue;
}	t_color_parse_result;

void	init_game(t_game *game);
void	clean_game(t_game *game);
void	print_error(char *message);
void	exit_error(char *message, t_game *game);
int		return_error(char *message);
void	free_map(t_map *map);
void	free_textures(t_textures *textures, void *mlx_ptr);
void	free_split(char **split);
int		init_mlx(t_game *game);
void	close_mlx(t_game *game);
int		parse_cub_file(char *file, t_game *game);
int		check_file_extension(char *filename);
char	**read_file_lines(int fd);
int		is_empty_line(char *line);
int		is_map_line(char *line);
int		parse_texture_line(char *line, t_map *map);
int		load_textures(t_game *game);
int		validate_texture_path(char *path);
int		load_single_texture(t_game *game, t_texture *texture, char *path);
int		parse_color_line(char *line, t_colors *colors);
int		parse_rgb_values(char *str, int *r, int *g, int *b); // bir rengin üç ana bileşenle ifade edilme biçimidir red green blue
int		create_color(int red, int green, int blue);
int		parse_map(char **lines, int start, t_game *game);
int		find_player_position(t_map *map, t_player *player);
void	init_player_direction(t_player *player, char direction);
int		get_map_width(char **grid);
int		validate_map(t_game *game);
int		check_walls_closed(t_map *map);
int		check_valid_characters(t_map *map);
int		flood_fill_check(t_map *map);
int		ft_isspace(char c);
int		ft_strcmp(const char *s1, const char *s2);
char	*get_next_line(int fd);
int		helper(char **temp, char *line, char **lines, int count);
char	*ft_strtrim_whitespace(char *str);
int		is_wall(t_map *map, int x, int y);


///
void	ray_cast(t_game *game, int i);
void	ray_pos(t_game *game);
int		render(void *param);
void	calculate_ray_steps(t_game *game);
void	draw_wall_column(t_game *game, int i);
void	wall_size(t_game *game);
void	wall_draw_height(t_game *game);
int		get_wall_color(t_game *game);

#endif