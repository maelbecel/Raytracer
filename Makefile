##
## EPITECH PROJECT, 2023
## bootstrap
## File description:
## Makefile
##

NAME=raytracer

SRC=		main.cpp 					\
			Ray.cpp	  		  			\
			Camera.cpp	  		  		\
			Scene.cpp	    			\
			Maths/Vector3D.cpp	    	\
			Parser/Parser.cpp			\
			Texture/Perlin.cpp	    	\
			Object/HitRecord.cpp

OBJ=$(SRC:.cpp=.o)

CXXFLAGS= -Wall -Wextra -Werror -std=c++17

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) -o $(NAME) $(OBJ) -lconfig++

debug: CXXFLAGS += -g
debug: re

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re