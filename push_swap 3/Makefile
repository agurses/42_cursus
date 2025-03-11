NAME = push_swap
LIBFT = libft/libft.a

SRC_FILES = main.c sort.c sort2.c p.c r.c rr.c s.c libftbonus.c
OBJ = $(SRC_FILES:.c=.o)
CC = gcc
CFLAGS = -Wall -Werror -Wextra -g
INCLUDE = -I include -I libft/include
RM = rm -rf

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
