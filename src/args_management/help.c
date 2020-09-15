/*
** EPITECH PROJECT, 2020
** norminette
** File description:
** help.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <unistd.h>
#include "help.h"
#include "../utils/exceptions.h"

void	disp_help(args_t *args)
{
	char	path[PATH_MAX];
	char	*arg[] = {
		"/bin/man",
		path,
		NULL
	};

	(void)args;
	snprintf(
		path,
		sizeof(path),
		"%s/norminette/manpage.1.gz",
		getenv("HOME")
	);
	printf("Searching manpages in %s\n", path);
	execv(arg[0], arg);
	throw(HelpNotFound, strerror(errno));
}