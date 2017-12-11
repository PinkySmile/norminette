##
## EPITECH PROJECT, 2017
## Test Makefile
## File description:
## Makefile for unit tests
##

NAME =	units

SRC =	../src/

UT_SRC = test_sum_stdarg.c

OBJ =	$(SRC:.c=.o) $(UT_SRC:.c=.o)

INC =	-I ../include

LIB =	

LIBS =	-lcriterion -lgcov

CFLAGS= $(INC) --coverage

all:	$(LIB) $(NAME)

$(LIB):
	make -C ../lib/my

$(NAME):$(OBJ)
	gcc -o $(NAME) $(OBJ) $(LIBS)

clean:
	rm -f $(OBJ)

fclean:	clean
	make -C ../lib/my fclean
	rm -f $(NAME)

re:	fclean all
