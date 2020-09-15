/*
** EPITECH PROJECT, 2020
** norminette
** File description:
** args.h
*/

#ifndef NORMINETTE_ARGS_H
#define NORMINETTE_ARGS_H

#include <stdbool.h>

typedef struct args_s {
	bool has_colors;
	bool verbose;
	bool name;
	bool useless_files;
	bool debug;
	bool big_files;
	bool no_big_files;
	bool cappuccino;
	bool only_tab_indent;
	int  default_indent;
	int  tab_size;
	int  infos_points;
	int  minor_points;
	int  major_points;
	char **paths;
	char **excluded;
} args_t;

args_t parse_args(int argc, char **argv);

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

#endif //NORMINETTE_ARGS_H
