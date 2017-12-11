NAME =	libmy.a

FILE =	convert_base.c \
	disp.c \
	my_compute_power_rec.c \
	my_compute_square_root.c \
	my_strdup.c \
	my_find_prime_supp.c \
	my_getnbr_base.c \
	my_getnbr.c \
	my_isneg.c \
	my_is_prime.c \
	my_putchar.c \
	my_put_nbr.c \
	my_putstr.c \
	my_revstr.c \
	my_showmem.c \
	my_showstr.c \
	my_sort_int_array.c \
	my_strcapitalize.c \
	my_strcat.c \
	my_strcmp.c \
	my_strcpy.c \
	my_str_isalpha.c \
	my_str_islower.c \
	my_str_isnum.c \
	my_str_isprintable.c \
	my_str_isupper.c \
	my_strlen.c \
	my_strlen_rec.c \
	my_strlowcase.c \
	my_strncat.c \
	my_strncmp.c \
	my_strncpy.c \
	my_strstr.c \
	my_strupcase.c \
	my_swap.c \
	show_str_array.c \
	show_int_array.c \
	my_putstr_stderr.c \
	my_putchar_stderr.c \
	my_printf.c \
	my_putfloat.c \
	my_put_nbr_unsigned.c \
	my_putnbr_base.c \
	my_putbase.c \
	str.c \
        my_showstr.c \
        my_compute_power_rec_long.c \
        my_putstar.c \

SRC =	$(FILE:%.c=sources/%.o)

OBJ =	$(SRC:.c=.o)

INC =	-Iincludes

CFLAGS=	$(INC)

CC =	gcc

all: $(NAME)

$(NAME):$(OBJ)
	$(AR) rc $(NAME) $(OBJ)

clean:
	$(RM) $(OBJ)

fclean:	clean
	$(RM) $(NAME)

re:	fclean all

dbg:	CFLAGS += -O0 -g
dbg:	re
