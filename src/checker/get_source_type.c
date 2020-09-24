/*
** EPITECH PROJECT, 2020
** norminette
** File description:
** get_source_type.c
*/

#include "get_source_type.h"
#include "../utils/regex.h"

enum source_type_e get_source_type(const char *path)
{
	if (match_regex("(^|\\/).*[.]h$", path))
		return HEADER_FILE;
	if (match_regex("(^|\\/)?.*[.]c$", path))
		return SOURCE_FILE;
	if (match_regex("(^|\\/)Makefile$", path))
		return MAKEFILE;
	return UNKNOWN_FILE;
}