##
## EPITECH PROJECT, 2018
## NWP_myftp_2018
## File description:
## CCP_plazza_2018/Makefile
##

CC	=	g++

CXXFLAGS	=	-g3 -pthread -std=c++11 -Wall -Wextra -I ./include -lsfml-graphics -lsfml-window -lsfml-system

SRC	=	./main.cpp	\
		./mainGraphic.cpp	\
		./src/Error.cpp \
		./src/Plazza.cpp	\
		./src/Kitchen.cpp

tools	=	./tools/stringToWordArray.cpp	\
			./tools/trim.cpp	\
			./tools/word_array.cpp	\
			./tools/my_getline.cpp	\


OBJ	=	$(SRC:.cpp=.o) $(tools:.cpp=.o)

NAME	=	plazza

all:	$(NAME)

$(NAME):	$(OBJ)
		$(CC) -o $(NAME) $(OBJ) $(CXXFLAGS)

clean:
		rm -f $(OBJ)

fclean: clean
		rm -f $(NAME)

re:	fclean all