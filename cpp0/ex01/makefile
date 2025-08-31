NAME = phonebook

SRC_FILES = contact.cpp \
			phonebook.cpp
CFLAGS = -Wall -Werror -Wextra -std=c++98
CPP = c++
OBJ = $(SRC_FILES:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CPP) $(CFLAGS) $(OBJ) -o $(NAME)

.o:.cpp
	$(CPP) $(CFLAGS)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all
