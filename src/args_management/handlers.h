/*
** EPITECH PROJECT, 2020
** norminette
** File description:
** handlers.h
*/

#ifndef NORMINETTE_HANDLERS_H
#define NORMINETTE_HANDLERS_H


#include <stdlib.h>
#include <getopt.h>
#include "args.h"
#include "../utils/exceptions.h"

#define ARG_BOOL_TRUE_FCT(name, param, val)\
void name(args_t *args) {\
	args->param = val;\
}

#define ARG_INT_FCT(name, param)\
void name(args_t *args) {\
	char *endptr;\
	long val = strtol(optarg, &endptr, 0);\
\
	if (\
		(val < 0 || val > INT32_MAX) ||\
		(errno != 0 && val == 0) ||\
		endptr == optarg\
	)\
		throw(\
			InvalidArgumentFormatException,\
			"--"#name" expects a valid integer."\
		);\
	args->param = val;\
}

#define ERR_FMT "%s is not recognised as a valid mistake name."

void all(args_t *args);
void verbose(args_t *args);
void name(args_t *args);
void big(args_t *args);
void no_big(args_t *args);
void cappuccino(args_t *args);
void only_tabs(args_t *args);
void indent(args_t *args);
void tab_size(args_t *args);
void minor(args_t *args);
void info(args_t *args);
void major(args_t *args);
void exclude(args_t *args);
void ignore(args_t *args);

#endif //NORMINETTE_HANDLERS_H
