NAME = so_long
CC = cc
CFLAGS = -Wall -Wextra -Werror -I$(MLX_PATH)
# MiniLibX için gerekli bayraklar ve yol
MLX_PATH = minilibx-linux/
MLX_LIB = $(MLX_PATH)/libmlx.a
MLX_FLAGS = -L$(MLX_PATH) -lmlx -lXext -lX11 -lm
# Get Next Line klasörü
GNL_PATH = get_nextline
# Printf kütüphanesi
PRINTF_PATH = ft_printf
PRINTF_LIB = $(PRINTF_PATH)/libftprintf.a
# Kaynak dosyalar
SRCS = main.c \
		map_reader.c \
		moves_key.c \
		draw.c \
		checkers.c \
		checkers2.c \
		utils.c \
		map_reader_utils.c \
		$(GNL_PATH)/get_next_line.c \
		$(GNL_PATH)/get_next_line_utils.c
OBJS = $(SRCS:.c=.o)
all: $(NAME)
$(NAME): $(MLX_LIB) $(PRINTF_LIB) $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) -L$(PRINTF_PATH) -lftprintf $(MLX_FLAGS)
$(MLX_LIB):
	make -C $(MLX_PATH)
$(PRINTF_LIB):
	make -C $(PRINTF_PATH)
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	rm -f $(OBJS)
	make -C $(MLX_PATH) clean
	make -C $(PRINTF_PATH) clean
fclean: clean
	rm -f $(NAME)
	make -C $(PRINTF_PATH) fclean
re: fclean all
.PHONY: all clean fclean re