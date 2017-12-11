/*
** EPITECH PROJECT, 2017
** flags
** File description:
** all flags for my_printf
*/

#ifndef __FLAGS_H_
#define __FLAGS_H_

#include "my.h"

flags   all_flags[] = {
{'f', 1, (int (*)(void *))&my_putstarfloat},		\
{'d', 0, (int (*)(void *))&my_putstarint},		\
{'i', 0, (int (*)(void *))&my_putstarint},		\
{'u', 0, (int (*)(void *))&my_putnbr_unsigned},		\
{'c', 0, (int (*)(void *))&my_putstarchar},		\
{'s', 2, (int (*)(void *))&my_put_str},			\
{'o', 0, (int (*)(void *))&my_putoctal},		\
{'%', '%', (int (*)(void *))&my_putstarchar},		\
{'S', 2, (int (*)(void *))&my_show_str},		\
{'b', 0, (int (*)(void *))&my_putbinary},		\
{'m', 2, (int (*)(void *))&my_put_str_stderr},		\
{'p', 2, (int (*)(void *))&my_putpointer},		\
{'x', 0, (int (*)(void *))&my_puthexa},			\
{'X', 0, (int (*)(void *))&my_puthexa_cap},		\
{0, 0, 0}						\
};

#endif
