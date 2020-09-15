/*
** EPITECH PROJECT, 2020
** norminette
** File description:
** is_file_useless.c
*/

#include <string.h>
#include "is_file_useless.h"
#include "../utils/files.h"
#include "../utils/regex.h"

bool is_file_useless(const char *path)
{
	const char *name = get_file_name(path);
	bool useless = match_regex("^(.*[.]o|.*[.]a|~.*|#.*#)$", name);
	size_t size = get_file_size(path);

	useless |= size == 0 || size >= 1024 * 1024 * 4;
	return !is_reg_file(path) || useless;
}