/*
** EPITECH PROJECT, 2017
** my_printf
** File description:
** My version of the printf function
*/

#include <stdarg.h>
#include "my.h"
#include "flags.h"

int	display_arg(va_list args, int i)
{
	double	nbrd;
	int	nbri;

	switch (all_flags[i].type) {
	case 0:
		nbri = va_arg(args, int);
		return (all_flags[i].fct(&nbri));
	case 1:
		nbrd = va_arg(args, double);
		return (all_flags[i].fct(&nbrd));
	case 2:
		return (all_flags[i].fct(va_arg(args, char *)));
	default:
		nbri = all_flags[i].type;
		return (all_flags[i].fct(&nbri));
	}
}

int	find_flag(char *str, va_list args_list)
{
	for (int i = 0; all_flags[i].flag != 0; i++) {
		if (all_flags[i].flag == *str)
			return (display_arg(args_list, i));
	}
	return (0);
}

int	my_printf(char *str, ...)
{
	va_list	args_list;
	int	chars_displayed = 0;

	va_start(args_list, str);
	for (int i = 0; str[i] != 0; i++)
		if (str[i] == '%') {
			i++;
			chars_displayed += find_flag(&str[i], args_list);
		} else
			chars_displayed += my_putchar(str[i]);
	va_end(args_list);
	return (chars_displayed);
}
