/*
** EPITECH PROJECT, 2017
** flags
** File description:
** flags
*/

#include <getopt.h>
#include <stdlib.h>
#include "stacktrace.h"
#include "functions.h"
#include "structs.h"
#include "my.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <ctype.h>


void	disp_en_help(char **env)
{
	char	*path;
	char	*arg[] = {
		"man",
	        "./manpage.1.gz",
		NULL
	};

	path = get_env_var(env, "HOME");
	path = concat(path, "/norminette");
	printf("Searching manpages in %s\n", path);
	chdir(path);
	free(path);
	if (execve("/bin/man", arg, env))
		perror("/bin/man");
	exit(EXIT_FAILURE);
}

void	disp_fr_help(char **env)
{
	char	*path;
	char	*arg[] = {
		"man",
	        "./manpage.1f.gz",
		NULL
	};

	path = get_env_var(env, "HOME");
	path = concat(path, "/norminette");
	printf("Searching manpages in %s\n", path);
	chdir(path);
	free(path);
	if (execve("/bin/man", arg, env))
		perror("/bin/man");
	exit(EXIT_FAILURE);
}

void	display_help(char **env, bool fr)
{
	addStackTraceEntry("display_help", "pb", "env", env, "fr", fr);
	if (fr)
		disp_fr_help(env);
	else
		disp_en_help(env);
	freeStackTrace();
	exit(0);
}

void	disp_list(list_t *list)
{
	addStackTraceEntry("disp_list", "p", "list", list);
	for (; list->next; list = list->next)
		printf("  -  '%s'\n", (char *)list->data);
	delStackTraceEntry();
}

flag get_flags(int argc, char **args, char **env, char ***dirs)
{
	int c;
	flag flags;
	bool disp = false;
	char *dir = NULL;
	int nb = 0;
	int option_index = 0;
	char *arg[] = {
		"bash",
		"./update.sh",
		"--force",
		NULL
	};
	char *path;

	addStackTraceEntry("get_flags", "ipp", "argc", argc, "args", args, "env", env);
	memset(&flags, 0, sizeof(flag));
	flags.default_indent = 8;
	flags.tab_size = 8;
	flags.only_tab_indent = true;
	flags.infos_points = 0;
	flags.minor_points = 1;
	flags.major_points = 5;
	while (true) {
		struct option long_options[] = {
			{"all",			no_argument,       0, 'a'},
			{"banned-fct-list",	no_argument,       0, 'b'},
			{"colorless",		no_argument,       0, 'c'},
			{"debug",		no_argument,       0, 'd'},
			{"french",		no_argument,       0, 'f'},
			{"large",		no_argument,       0, 'l'},
			{"help",		no_argument,       0, 'h'},
			{"indent",		required_argument, 0, 'i'},
			{"name",		no_argument,       0, 'n'},
			{"small",		no_argument,       0, 's'},
			{"traceback",		no_argument,       0, 't'},
			{"useless-file",	no_argument,       0, 'u'},
			{"verbose",		no_argument,       0, 'v'},
			{"accept-space-indent",	no_argument,       0, 'A'},
			{"cappuccino",		no_argument,       0, 'C'},
			{"include",		required_argument, 0, 'I'},
			{"tab_size",		required_argument, 0, 'T'},
			{"update",		no_argument,       0, 'U'},
			{"minor",	        required_argument, 0,  2 },
			{"info",	        required_argument, 0,  1 },
			{"major",		required_argument, 0,  3 },
			{0,			0,                 0,  0 }
		};

		c = getopt_long(argc, args, "abcdflhnstuvI:UCi:T:A",
				long_options, &option_index);
		if (c == -1)
			break;
		switch (c) {
		case 1:
			for (int i = optarg[0] == '+' || optarg[0] == '-'; optarg[i]; i++)
				if (!isdigit(optarg[i])) {
					printf("Invalid argument for flag --major: %s is not a valid number\n", optarg);
					exit(EXIT_FAILURE);
				}
			flags.infos_points = atoi(optarg);
			break;
		case 2:
			for (int i = optarg[0] == '+' || optarg[0] == '-'; optarg[i]; i++)
				if (!isdigit(optarg[i])) {
					printf("Invalid argument for flag --major: %s is not a valid number\n", optarg);
					exit(EXIT_FAILURE);
				}
			flags.minor_points = atoi(optarg);
			break;
		case 3:
			for (int i = optarg[0] == '+' || optarg[0] == '-'; optarg[i]; i++)
				if (!isdigit(optarg[i])) {
					printf("Invalid argument for flag --major: %s is not a valid number\n", optarg);
					exit(EXIT_FAILURE);
				}
			flags.major_points = atoi(optarg);
			break;
		case 'a':
			flags.u = true;
			flags.v = true;
			flags.i_caps = true;
			flags.big_files = true;
			load_functions(".", &flags);
			flags.b = true;
			if (!flags.b_fcts) {
				flags.b_fcts = my_malloc(sizeof(*flags.b_fcts));
				flags.b_fcts->next = NULL;
				flags.b_fcts->prev = NULL;
				flags.b_fcts->data = NULL;
			}
			break;
		case 'b':
			flags.b = true;
			if (!flags.b_fcts) {
				flags.b_fcts = my_malloc(sizeof(*flags.b_fcts));
				flags.b_fcts->next = NULL;
				flags.b_fcts->prev = NULL;
				flags.b_fcts->data = NULL;
			}
			break;

		case 'c':
			flags.c = true;
			break;
		case 'd':
			flags.d = true;
			flags.n = true;
			flags.t = true;
			break;
		case 'f':
			flags.f = true;
			break;
		case 'l':
			flags.big_files = true;
			break;
		case 'i':
			if (atoi(optarg) <= 0) {
				printf("Invalid argument for flag -i: Expected positive number\n");
				free_list(flags.fcts);
				freeStackTrace();
				exit(EXIT_FAILURE);
			}
			flags.default_indent = atoi(optarg);
			break;
		case 'h':
			disp = true;
			break;
		case 'n':
			flags.n = true;
			break;
		case 's':
			flags.no_big_files = true;
			break;
		case 't':
			flags.t = true;
			break;
		case 'u':
			flags.u = true;
			break;
		case 'v':
			flags.v = true;
			break;
		case 'A':
			flags.only_tab_indent = false;
			break;
		case 'T':
			if (atoi(optarg) <= 0) {
				printf("Invalid argument for flag -T: Expected positive number\n");
				free_list(flags.fcts);
				freeStackTrace();
				exit(EXIT_FAILURE);
			}
			flags.tab_size = atoi(optarg);
			break;
		case 'I':
			dir = optarg;
			flags.i_caps = true;
			load_functions(dir ? dir : "", &flags);
			if (flags.d)
				printf("%i functions are present in the list\n", list_len(flags.fcts));
			if (flags.d) {
				printf("All functions found in directory %s : \n", dir);
				disp_list(flags.fcts);
			}
			break;
		case 'U':
			path = get_env_var(env, "HOME");
			path = concat(path, "/norminette");
			printf("Updating from repository in %s\n", path);
			chdir(path);
			free(path);
			if (execve("/bin/bash", arg, env))
				perror("/bin/bash");
			exit(EXIT_FAILURE);
		case 'C':
			flags.cappuccino = true;
			break;
		case '?':
			printf("Use « %s -h » for more information\n", args[0]);
			free_list(flags.fcts);
			freeStackTrace();
			exit(EXIT_FAILURE);
		}
	}
	if (flags.d) {
		printf("Infos: -%ipts\n", flags.infos_points);
		printf("Minor: -%ipts\n", flags.minor_points);
		printf("Major: -%ipts\n", flags.major_points);
	}
	while (optind < argc) {
		*dirs = realloc(*dirs, (++nb + 1) * sizeof(**dirs));
		(*dirs)[nb - 1] = args[optind++];
		(*dirs)[nb] = NULL;
	}
	if (disp)
		display_help(env, flags.f);
	delStackTraceEntry();
	return (flags);
}
