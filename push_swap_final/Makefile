NAME = push_swap
LIBFT = libft/libft.a

SRC_FILES = main.c sort.c sort2.c push_rotate.c rrotate_atoi.c swap.c libftbonus.c utils.c create_lst.c
OBJ = $(SRC_FILES:.c=.o)
CC = gcc
CFLAGS = -Wall -Werror -Wextra
INCLUDE = -I.
RM = rm -f

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $@

$(LIBFT):
	@make -C libft

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
	@make clean -C libft
	$(RM) $(OBJ)

fclean: clean
	@make fclean -C libft
	$(RM) $(NAME)

re: fclean all
