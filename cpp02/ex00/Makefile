NAME = ex00

SRC_FILES =	main.cpp \
			Fixed.cpp 
			
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
