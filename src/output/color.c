/*
** EPITECH PROJECT, 2020
** norminette
** File description:
** color.c
*/

#include <stdio.h>
#include "color.h"

#ifndef _WIN32

void set_output_properties(unsigned bg, unsigned fg, unsigned properties)
{
	printf("\033[");
	if (!properties)
		printf("0;");
	for (unsigned i = 0; i < 9; i++)
		if ((1U << i) & properties)
			printf("%i;", i + 1);
	printf("%i;%im", bg + 10, fg);
}

#endif