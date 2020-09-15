/*
** EPITECH PROJECT, 2020
** norminette
** File description:
** args.c
*/

#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include "../utils/exceptions.h"
#include "args.h"
#include "help.h"
#include "update.h"

void all(args_t *args) {
	args->verbose = true;
	args->useless_files = true;
	args->no_big_files = true;
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
	(void *)update,
	minor,
	info,
	major
};
static const char *opts = "ac:dfi:lhnstuvACT:U";

args_t parse_args(int argc, char **argv)
{
	args_t args;
	int c;

	memset(&args, 0, sizeof(args));
	args.default_indent = 8;
	args.tab_size = 8;
	args.only_tab_indent = true;
	args.minor_points = 1;
	args.major_points = 5;
	while (true) {
		c = getopt_long(argc, argv, opts, long_options, NULL);
		if (c == '?')
			throw(InvalidArgumentException, "");
		else if (c == -1)
			break;
		for (int i = 0; long_options[i].name; i++)
			if (long_options[i].val == c)
				handlers[i](&args);
	}
	return args;
}