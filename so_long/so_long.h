/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agurses <agurses@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 05:59:38 by agurses           #+#    #+#             */
/*   Updated: 2025/04/08 14:19:06 by agurses          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <fcntl.h>

# include "get_nextline/get_next_line.h"
# include "ft_printf/ft_printf.h"
# include "minilibx-linux/mlx.h"

typedef struct s_img
{
	void	*player;
	void	*wall;
	void	*collectible;
	void	*exit;
	void	*floor;
	int		width;
	int		height;
}		t_img;

typedef struct s_game
{
	int		player_x;
	int		player_y;
	int		map_height;
	int		map_width;
	int		door_x;
	int		door_y;
	int		moment_count;
	int		player_count;
	int		collectible_count;
	int		door_count;
	char	**map;
	void	*win;
	void	*mlx;
	t_img	*img;
}		t_game;

int		key_input(int keycode, t_game *game);
int		move_down(t_game *game);
int		move_up(t_game *game);
int		move_left(t_game *game);
int		move_right(t_game *game);

int		close_window(t_game *game);
int		ft_map_reader(const char *filename, t_game *game);
int		line_counter(int fd);
int		ft_map_checker(char **map, t_game *game);
int		path_find(char **tmp_map, int x, int y, t_game *game);

int		render_map(t_game *game, int i, int j);
void	*render_for_img(t_game *game, int i, int j);
void	load_image(t_game *game);
int		read_map_lines(int fd, char **map, char **tmp_map);
int		allocate_maps(char ***map, char ***tmp_map, int line_count, int fd);
int		open_map_file(const char *filename, int *fd, int *line_count);

int		check_move_for_door(t_game *game, int x, int y);
int		ft_strcspn(const char *s, const char *charset);
int		ft_strlen_for_int(char *str);
char	*ft_strdup(const char *s);
int		ft_free_map(t_game *game);
int		ft_free_for_img(t_game *game);
int		free_both_maps(char **map, char **tmp_map, int line_count);
int		free_tmp_map(char **tmp_map, int line_count);
int		check_map_borders(char **map, t_game *game);
void	*ft_memset(void *s, int c, size_t n);

void	mark_cell_and_update(char **tmp_map, int x, int y, int *counters);
int		ft_map_checker(char **map, t_game *game);
void	count_map_elements(char **map, t_game *game, int col, int row);
int		line_counter(int fd);
int		arg_check(int ac, char **arg);
int		img_none(t_game *game);
int		check_map_character(char **map, t_game *game);
int		check_max_size(t_game *game);

#endif