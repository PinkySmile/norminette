//
// Created by andgel on 04/09/2020
//

#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <getopt.h>
#include <limits.h>
#include "../utils/exceptions.h"
#include "args.h"

#define ARG_BOOL_TRUE_FCT(name, param, val)\
static void name(args_t *args) {\
	args->param = val;\
}
#define ARG_INT_FCT(name, param)\
static void name(args_t *args) {\
	for (int i = optarg[0] == '+' || optarg[0] == '-'; optarg[i]; i++)\
	if (!isdigit(optarg[i]))\
		throw(\
			InvalidArgumentFormatException,\
			#name" expects a valid integer."\
		);\
	args->param = atoi(optarg);\
}

void all(args_t *args) {
	args->verbose = true;
	args->useless_files = true;
	args->no_big_files = true;
}

void	disp_help()
{
	char	path[PATH_MAX];
	char	*arg[] = {
		"man",
		path,
		NULL
	};

	snprintf(
		path,
		sizeof(path),
		"%s/norminette/manpage.1.gz",
		getenv("HOME")
	);
	printf("Searching manpages in %s\n", path);
	execv("/bin/man", arg);
	throw(HelpNotFound, strerror(errno));
}
ARG_BOOL_TRUE_FCT(verbose, verbose, true)
ARG_BOOL_TRUE_FCT(name, name, true)
ARG_BOOL_TRUE_FCT(useless, useless_files, true)
ARG_BOOL_TRUE_FCT(debug, debug, true)
ARG_BOOL_TRUE_FCT(big, big_files, true)
ARG_BOOL_TRUE_FCT(no_big, no_big_files, true)
ARG_BOOL_TRUE_FCT(cappuccino, cappuccino, true)
ARG_BOOL_TRUE_FCT(only_tabs, only_tab_indent, false)

ARG_INT_FCT(indent, default_indent)
ARG_INT_FCT(tab_size, tab_size)
ARG_INT_FCT(minor, infos_points)
ARG_INT_FCT(info, minor_points)
ARG_INT_FCT(major, major_points)

static const struct option long_options[] = {
	{"all",                  no_argument,       0, 'a'},
	{"color",                required_argument, 0, 'c'},
	{"debug",                no_argument,       0, 'd'},
	{"large",                no_argument,       0, 'l'},
	{"help",                 no_argument,       0, 'h'},
	{"indent",               required_argument, 0, 'i'},
	{"name",                 no_argument,       0, 'n'},
	{"small",                no_argument,       0, 's'},
	{"useless-file",         no_argument,       0, 'u'},
	{"verbose",              no_argument,       0, 'v'},
	{"accept-space-indent",  no_argument,       0, 'A'},
	{"cappuccino",           no_argument,       0, 'C'},
	{"tab_size",             required_argument, 0, 'T'},
	{"update",               no_argument,       0, 'U'},
	{"minor",                required_argument, 0,  2 },
	{"info",                 required_argument, 0,  1 },
	{"major",                required_argument, 0,  3 },
	{0,                      0,                 0,  0 }
};
static void (* const handlers[])(args_t *args) = {
	all,
	NULL,
	debug,
	big,
	disp_help,
	indent,
	name,
	no_big,
	useless,
	verbose,
	only_tabs,
	cappuccino,
	tab_size,
	NULL,
	minor,
	info,
	major
};
//static const char *opts = "acdflhnstuvUCi:T:A";

args_t parse_args(int argc, char **argv)
{
	args_t args;
	int c;
	int i;

	memset(&args, 0, sizeof(args));
	args.default_indent = 8;
	args.tab_size = 8;
	args.only_tab_indent = true;
	args.minor_points = 1;
	args.major_points = 5;
	while (true) {
		c = getopt_long(argc, argv, "", long_options, &i);
		if (c == '?')
			throw(InvalidArgumentException, "");
		else if (c == -1)
			break;
		handlers[i](&args);
	}
	return args;
}