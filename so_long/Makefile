NAME = so_long

CC = gcc
CFLAGS = -Wall -Wextra -Werror

# MiniLibX için gerekli bayraklar ve yol
MLX_PATH = mlx_mac
MLX_LIB = $(MLX_PATH)/libmlx.a
MLX_FLAGS = -L$(MLX_PATH) -lmlx -framework OpenGL -framework AppKit

# Get Next Line klasörü
GNL_PATH = get_nextline
PRINTF_PATH = ft_printf

# Kaynak dosyalar
SRCS =	main.c \
		map_reader.c \
		moves_key.c \
		draw.c \
		checkers.c \
		checkers2.c \
		utils.c \
		map_reader_utils.c \
		$(GNL_PATH)/get_next_line.c \
		$(GNL_PATH)/get_next_line_utils.c \
		$(PRINTF_PATH)/ft_printf.c \
		$(PRINTF_PATH)/ft_printf_utils.c


OBJS = $(SRCS:.c=.o)

all: $(MLX_LIB) $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(MLX_FLAGS)

$(MLX_LIB):
	make -C $(MLX_PATH)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)
	make -C $(MLX_PATH) clean

fclean: clean
	rm -f $(NAME)

re: fclean all
