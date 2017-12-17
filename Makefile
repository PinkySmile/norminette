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
	src/sub_strings.c \
	src/compare_strings.c \
	src/my_showstr.c \
	src/my_putnbr_base.c \
	src/catch_sig.c \

OBJ =	$(SRC:.c=.o)

INC =	-Iinclude \

LDFLAGS = 

CFLAGS= $(INC) \
	-W \
	-Wall \
	-Wextra \
	-Werror

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

dbg:	CFLAGS += -O0 -g
dbg:	RULE = dbg
dbg:	re
