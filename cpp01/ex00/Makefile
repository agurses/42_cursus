NAME = brain

SRC_FILES = main.cpp \
			newZombie.cpp \
			randomChump.cpp \
			Zombie.cpp
CXXFLAGS = -Wall -Werror -Wextra -std=c++98
CXX = c++
OBJ = $(SRC_FILES:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(NAME)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all
