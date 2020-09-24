/*
** EPITECH PROJECT, 2020
** norminette
** File description:
** is_file_useless.h
*/

#ifndef NORMINETTE_IS_FILE_USELESS_H
#define NORMINETTE_IS_FILE_USELESS_H


#include <stdbool.h>

bool is_file_useless(const char *path, const char **reason);

typedef struct file_info_s {
	size_t size;
	const char *path;
} file_info_t;

#define RESULT_FCT(name, cond, str)\
static bool name(const file_info_t *infos, const char **reason)\
{\
	bool result = cond;\
\
	if (result && reason)\
		*reason = str;\
\
	return result;\
}

#endif //NORMINETTE_IS_FILE_USELESS_H
