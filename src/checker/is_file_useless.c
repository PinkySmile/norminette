/*
** EPITECH PROJECT, 2020
** norminette
** File description:
** is_file_useless.c
*/

#include <string.h>
#include "is_file_useless.h"
#include "../utils/file_types.h"
#include "../utils/regex.h"

#ifdef _WIN32
static const char *get_file_name(const char *path)
{
	const char *slash = strrchr(path, '/');
	const char *bslash = strrchr(path, '\\');

	return slash > bslash ? slash : bslash;
}
#else
#define get_file_name(path) strrchr(path, '/')
#endif

bool is_file_useless(const char *path)
{
	const char *name = get_file_name(path) ?: path;
	bool useless = match_regex("^(.*[.]o|.*[.]a|~.*|#.*#)$", name);

	return !is_reg_file(path) || useless;
}