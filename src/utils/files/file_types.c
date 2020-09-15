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
	char err[strlen(path) + 51];
	struct stat info;

#ifndef _WIN32
	if (lstat(path, &info) < 0) {
#else
	if (stat(path, &info) < 0) {
#endif
		strcpy(err, path);
		strcat(err, ": ");
		strcat(err, strerror(errno));
		throw(FileNotFoundException, err);
	}
	return (info.st_mode & S_IFMT) == type;
}