/*
** EPITECH PROJECT, 2020
** norminette
** File description:
** get_file_length.c
*/

#include <errno.h>
#include "../files.h"
#include "../exceptions.h"

#ifdef _WIN32
const char *get_file_name(const char *path)
{
	const char *slash = strrchr(path, '/');
	const char *bslash = strrchr(path, '\\');

	return ((slash > bslash ? slash : bslash) ?: path) + 1;
}
#endif

void file_not_found(const char *path)
{
	char err[strlen(path) + 51];

	strcpy(err, path);
	strcat(err, ": ");
	strcat(err, strerror(errno));
	throw(FileNotFoundException, err);
}

size_t get_file_size(const char *path)
{
	struct stat info;

#ifndef _WIN32
	if (lstat(path, &info) < 0)
#else
	if (stat(path, &info) < 0)
#endif
		file_not_found(path);
	return info.st_size;
}