##
## EPITECH PROJECT, 2023
## bootstrap
## File description:
## Makefile
##

NAME=raytracer

SRC=		main.cpp 			\
			Vector3D.cpp

OBJ=$(SRC:.cpp=.o)

CXXFLAGS= -Wall -Wextra -Werror -std=c++17

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) -o $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re