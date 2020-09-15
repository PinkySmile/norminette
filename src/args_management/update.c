/*
** EPITECH PROJECT, 2020
** norminette
** File description:
** update.c
*/

#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include <stdio.h>
#include "update.h"
#include "../utils/exceptions.h"

void update(void)
{
	char path[PATH_MAX];
	char *arg[] = {
		"bash",
		path,
		"--force",
		NULL
	};

	snprintf(
		path,
		sizeof(path),
		"%s/norminette/update.sh",
		getenv("HOME")
	);

	printf("Running update script %s\n", path);
	execv("/bin/bash", arg);
	throw(UpdateFailedException, "Cannot run install script");
}