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

RESULT_FCT(
	is_binary_file,
	match_regex(
		"^.*[.](o|a|so|exe|out|dll|lib|gch|gcda|gcno)$",
		get_file_name(infos->path)
	),
	"Binary file"
)

RESULT_FCT(
	is_temp_file,
	match_regex(
		"^.*~|#.*#|.*[.]d$",
		get_file_name(infos->path)
	),
	"Temporary file"
)

RESULT_FCT(
	is_debug_file,
	match_regex(
		"vgcore[.][0-9]*$",
		get_file_name(infos->path)
	),
	"Debugger file"
)

RESULT_FCT(
	is_empty,
	infos->size == 0,
	"Empty file"
)

RESULT_FCT(
	is_too_big,
	infos->size >= 1024 * 1024 * 4,
	"Really big file"
)

RESULT_FCT(
	is_not_regular_file,
	!is_reg_file(infos->path),
	"Not a regular file"
)

static bool (* const handlers[])(const file_info_t *, const char **reason) = {
	is_not_regular_file,
	is_empty,
	is_temp_file,
	is_debug_file,
	is_binary_file,
	is_too_big,
	NULL
};

bool is_file_useless(const char *path, const char **reason)
{
	file_info_t infos = {
		get_file_size(path),
		path
	};

	for (int i = 0; handlers[i]; i++)
		if (handlers[i](&infos, reason))
			return true;
	return false;
}