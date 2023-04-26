##
## EPITECH PROJECT, 2023
## bootstrap
## File description:
## Makefile
##

NAME=raytracer

SRC=		main.cpp 				\
			Shapes/Triangle.cpp 	\
			Shapes/Rectangle.cpp	\
			Shapes/Sphere.cpp 		\
			Lights/Ambiant.cpp 		\
			Maths/Vector3D.cpp 		\
			Scene.cpp				\
			Object.cpp				\
			Maths/Point3D.cpp

OBJ=$(SRC:.cpp=.o)

CXXFLAGS= -Wall -Wextra -Werror -std=c++17

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) -o $(NAME) $(OBJ)

debug: CXXFLAGS += -g
debug: re

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
