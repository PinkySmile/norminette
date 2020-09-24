/*
** EPITECH PROJECT, 2020
** norminette
** File description:
** file_types.c
*/

#include <errno.h>
#include "../files.h"
#include "../exceptions.h"

bool is_type(const char *path, unsigned type)
{
	struct stat info;

#ifndef _WIN32
	if (lstat(path, &info) < 0)
#else
	if (stat(path, &info) < 0)
#endif
		throw_file_not_found(path);
	return (info.st_mode & S_IFMT) == type;
}