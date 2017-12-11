##
## EPITECH PROJECT, 2017
## Makefile
## File description:
## Makefile of the project
##

NAME =	norminette

SRC =	src/main.c \
	src/scan.c \
	src/flags.c \
	src/scan_file.c \

OBJ =	$(SRC:.c=.o)

INC =	-Iinclude \
	-Ilib/my/includes

LIB =	./lib/my/libmy.a

LDFLAGS = -Llib/my\
	  -lmy

CFLAGS= $(INC) \
	-W \
	-Wall \
	-Wextra \
	-Werror

CC =	gcc

RULE =	all

all:    $(NAME)

$(LIB):
	$(MAKE) -C lib/my $(RULE)

$(NAME):$(OBJ) $(LIB)
	$(CC) -o $(NAME) $(OBJ) $(LDFLAGS)

clean:
	$(MAKE) -C lib/my clean
	$(RM) $(OBJ)

fclean:	clean
	$(MAKE) -C lib/my fclean
	$(RM) $(NAME)

re:	fclean all

dbg:	CFLAGS += -O0 -g
dbg:	RULE = dbg
dbg:	re
