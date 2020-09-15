/*
** EPITECH PROJECT, 2020
** norminette
** File description:
** concat.c
*/

#include <string.h>
#include <stddef.h>
#include "concat.h"
#include "alloc.h"

char *concat(unsigned nbStrings, ...)
{
	size_t length = 0;
	char *str_list[nbStrings];
	char *str = NULL;
	va_list list;

	if (!nbStrings)
		return NULL;

	va_start(list, nbStrings);
	for (unsigned i = 0; i < nbStrings; i++) {
		str_list[i] = va_arg(list, char *);
		length += strlen(str_list[i]);
	}
	va_end(list);

	str = alloc(length);
	strcpy(str, str_list[0]);
	for (unsigned i = 1; i < nbStrings; i++)
		strcat(str, str_list[i]);
	return str;
}