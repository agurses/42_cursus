NAME = cub3D

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
INCLUDES = -I./include -I./libft -I./mlx

# MLX_FLAGS = -L./minilibx-linux -lmlx -lXext -lX11 -lm
# macOS için (yukarıdaki satırı yorum yap, bunu aç)
MLX_FLAGS = -L./mlx_mac -lmlx -framework OpenGL -framework AppKit

LIBFT = ./libft/libft.a

SRC_DIR = src
OBJ_DIR = obj

SOURCES = main.c \
			utils/error.c \
			utils/memory.c \
			utils/mlx_utils.c \
			utils/init.c \
			utils/clean.c \
			utils/get_next_line.c \
			utils/utils.c \
			parsing/cub_file.c \
			parsing/parse_file_helper.c \
			parsing/parse_file.c \
			parsing/tissue.c \
			parsing/parse_color.c \
			parsing/parse_map.c \
			parsing/parse_map_two.c \
			parsing/validate_map.c \
			parsing/validate_map_utils.c

OBJECTS = $(SOURCES:%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(LIBFT) $(OBJECTS)
	$(CC) $(OBJECTS) $(LIBFT) $(MLX_FLAGS) -o $(NAME)
	@echo "✅ cub3D compiled successfully!"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	@make -C libft

clean:
	rm -rf $(OBJ_DIR)
	@make -C libft clean
	@echo "🧹 Object files cleaned"

fclean: clean
	rm -f $(NAME)
	@make -C libft fclean
	@echo "🧹 Executable removed"

re: fclean all

.PHONY: all clean fclean re
