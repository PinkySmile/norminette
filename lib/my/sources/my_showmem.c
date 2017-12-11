/*
** EPITECH PROJECT, 2017
** my_showmem
** File description:
** Show a memory dump
*/

#include "my.h"

int     my_putnbr_base_long(long number, char const *base, int draw)
{
	int		base_size;
	int		nb_of_chars = 0;
	char		all_chars[32];

	base_size = my_strlen(base);
	for (int i = 0; number > 0; i++) {
		all_chars[i] = base[number % base_size];
		nb_of_chars++;
		number = number / base_size;
	}
	for (int i = nb_of_chars - 1; draw && i >= 0; i--)
		my_putchar(all_chars[i]);
	return (nb_of_chars);
}

void	show_address(char *address)
{
	int	add_size = 0;

	add_size = my_putnbr_base_long((long) address, "0123456789abcdef", 0);
	for (int i = add_size; i < 8; i++)
		my_putchar('0');
	my_putnbr_base_long((long) address, "0123456789abcdef", 1);
}

int	showmem_values(char const *str, int size, int buffer)
{
	int s;

	if (size > 16)
		size = 16;
	for (int i = 0; i < size; i++) {
		s = my_putnbr_base_long(str[i], "0123456789abcdef", 0);
		for (int i = s ; i < 2 ; i++)
			my_putchar('0');
		my_putnbr_base_long(str[i], "0123456789abcdef", 1);
		if (buffer) {
			buffer = 0;
			my_putchar(' ');
		} else
			buffer++;
	}
	return (buffer);
}

void	showmem_chars(char const *str, int size, int *sizes)
{
	int s;

	if (size > 16) {
		*sizes = 16;
	} else
		*sizes = size;
	for (int i = 0; i < *sizes; i++)
		if (str[i] >= 32 && str[i] <= 176)
			my_putchar(str[i]);
		else
			my_putchar('.');
}

int	my_showmem(char *str, int size)
{
	int	sizes = 0;
	int	buffer = 0;

	for (int i = 0; i < size; i += 16) {
		show_address(str + i);
		my_putstr(":   ");
		buffer = showmem_values(str + i, size - i, buffer);
		disp(sizes, buffer);
		buffer = 0;
		showmem_chars(str + i, size - i, &sizes);
		my_putchar('\n');
	}
	return (0);
}
