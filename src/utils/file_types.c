/*
** EPITECH PROJECT, 2020
** norminette
** File description:
** file_types.c
*/

#include "file_types.h"

bool is_type(const char *path, unsigned type)
{
	struct stat info;

#ifndef _WIN32
	return lstat(path, &info) >= 0 && (info.st_mode & S_IFMT) == type;
#else
	return stat(path, &info) >= 0 && (info.st_mode & S_IFMT) == type;
#endif
}