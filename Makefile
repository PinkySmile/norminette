##
## EPITECH PROJECT, 2017
## Makefile
## File description:
## Makefile of the project
##

NAME =	norminette

SRC =	src/main.c		\
	src/scan.c		\
	src/flags.c		\
	src/scan_file.c		\
	src/sub_strings.c	\
	src/compare_strings.c	\
	src/my_showstr.c	\
	src/my_putnbr_base.c	\
	src/catch_sig.c		\
	src/load_functions.c	\
	src/free_list.c		\
	src/int_to_str.c	\
	src/long_to_str.c	\
	src/double_to_str.c	\
	src/concat.c		\
	src/get_nbrlen.c	\
	src/stacktrace.c	\
	src/my_malloc.c		\
	src/get_env_vars.c	\
	src/display_cappuccino.c\

OBJ =	$(SRC:.c=.o)

INC =	-Iinclude \

LDFLAGS = -lm

CFLAGS= $(INC)	\
	-W	\
	-Wall	\
	-Wextra	\

CC =	gcc

RULE =	all

all:    $(NAME)


$(NAME):$(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(LDFLAGS)

clean:
	$(RM) $(OBJ)

fclean:	clean
	$(RM) $(NAME)

re:	fclean all

fast:	CFLAGS += -Ofast
fast:	re

dbg:	CFLAGS += -O0 -g
dbg:	RULE = dbg
dbg:	re
