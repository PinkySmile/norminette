/*
** EPITECH PROJECT, 2020
** norminette
** File description:
** handlers.c
*/

#include <stdio.h>
#include "handlers.h"
#include "../data/style_errors.h"
#include "../utils/alloc.h"

void all(args_t *args)
{
	args->verbose = true;
	args->no_big_files = true;
}

void exclude(args_t *args)
{
	unsigned length = 1;
	char ***excluded = &args->excluded;

	while (*excluded && (*excluded)[++length]);
	length++;
	*excluded = alloc_again(*excluded, length * sizeof(**excluded));
	(*excluded)[length - 2] = optarg;
	(*excluded)[length - 1] = NULL;
}

void ignore(args_t *args)
{
	unsigned length = 0;
	enum mistake_name_e **ignored = &args->ignored_mistakes;
	char err[strlen(optarg) + strlen(ERR_FMT) - 1];

	while (*ignored && (*ignored)[length] != NB_OF_MISTAKES)
		length++;
	length++;
	*ignored = alloc_again(*ignored, (length + 1) * sizeof(**ignored));
	(*ignored)[length - 1] = mistake_name_from_string(optarg);
	(*ignored)[length] = NB_OF_MISTAKES;
	if ((*ignored)[length - 1] != NB_OF_MISTAKES)
		return;
	for (int i = 0; coding_style[i].name; i++)
		if (strcmp(coding_style[i].name, optarg) == 0) {
			(*ignored)[length - 1] = i;
			return;
		}
	sprintf(err, ERR_FMT, optarg);
	throw(InvalidArgumentFormatException, err);
}

ARG_BOOL_TRUE_FCT(verbose, verbose, true)
ARG_BOOL_TRUE_FCT(name, name, true)
ARG_BOOL_TRUE_FCT(big, big_files, true)
ARG_BOOL_TRUE_FCT(no_big, no_big_files, true)
ARG_BOOL_TRUE_FCT(cappuccino, cappuccino, true)
ARG_BOOL_TRUE_FCT(only_tabs, only_tab_indent, false)

ARG_INT_FCT(indent, default_indent)
ARG_INT_FCT(tab_size, tab_size)
ARG_INT_FCT(minor, infos_points)
ARG_INT_FCT(info, minor_points)
ARG_INT_FCT(major, major_points)