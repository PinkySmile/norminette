/*
** EPITECH PROJECT, 2017
** main
** File description:
** Main function for the project
*/

#include "functions.h"
#include "my.h"
#include "global2.h"
#include "stacktrace.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <dirent.h>
#include <signal.h>
#include <string.h>
#include <stdio.h>

int     find_type(mode_t mode)
{
	switch ((int)(mode & S_IFMT)) {
	case S_IFSOCK:
		return ('s');
	case S_IFLNK:
		return ('l');
	case S_IFREG:
		return ('-');
	case S_IFBLK:
		return ('b');
	case S_IFDIR:
		return ('d');
	case S_IFCHR:
		return ('c');
	case S_IFIFO:
		return ('p');
	}
	return ('?');
}

bool	is_dir(char *path)
{
	struct stat	info;

	if (lstat(path, &info) >= 0 && find_type(info.st_mode) == 'd')
		return (true);
	return (false);
}

void	set_sigaction(void)
{
	struct sigaction	action;

	memset(&action, '\0', sizeof(action));
        action.sa_sigaction = &catch_sig;
	action.sa_flags = SA_SIGINFO;
	sigaction(SIGINT, &action, 0);
	sigaction(SIGILL, &action, 0);
	sigaction(SIGTRAP, &action, 0);
	sigaction(SIGABRT, &action, 0);
	sigaction(SIGSEGV, &action, 0);
	sigaction(SIGTERM, &action, 0);
	sigaction(SIGFPE, &action, 0);
	sigaction(SIGBUS, &action, 0);
	sigaction(SIGSYS, &action, 0);
	sigaction(SIGPIPE, &action, 0);
}

int	main(int argc, char **args, char **env)
{
	char	**dirs = NULL;

	name = args[0];
	set_sigaction();
	initStackTrace();
	flags.t = 1;
        addStackTraceEntry("main", "ipp", "argc", argc, "args", args, "env", env);
	flags = get_flags(argc, args, env, &dirs);
	memset(mistakes, 0, 40 * sizeof(int));
	if (!dirs)
		dirs = (char *[]){".", NULL};
	for (int i = 0; dirs[i] != 0; i++) {
		if (flags.d)
			printf("Entering %s\n", dirs[i]);
		if (is_dir(dirs[i]))
			scan_folder(dirs[i], &flags, mistakes);
		else
			scan_file(dirs[i], &flags, mistakes, 1);
	}
        free(dirs);
	if (flags.d)
		printf("Displaying result\n");
	display_result(mistakes, &flags);
	freeStackTrace();
	return (0);
}

char	*get_prog_name()
{
	return (name);
}

int	*get_mistakes()
{
	return (mistakes);
}

flag	*get_flags_var()
{
	return (&flags);
}
