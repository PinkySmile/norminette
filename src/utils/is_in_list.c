/*
** EPITECH PROJECT, 2020
** norminette
** File description:
** is_in_list.c
*/

#include <string.h>
#include "is_in_list.h"

bool is_in_list(const char **list, const char *value)
{
	if (!list)
		return false;
	for (int i = 0; list[i]; i++) {
		if (
			(value && list[i] && strcmp(list[i], value) == 0) ||
			value == list[i]
		)
			return true;
	}
	return false;
}

bool is_mistake_ignored(const enum mistake_name_e *list,\
enum mistake_name_e value)
{
	if (!list)
		return false;
	for (int i = 0; list[i] != NB_OF_MISTAKES; i++)
		if (value == list[i])
			return true;
	return false;
}