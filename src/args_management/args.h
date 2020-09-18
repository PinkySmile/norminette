/*
** EPITECH PROJECT, 2020
** norminette
** File description:
** args.h
*/

#ifndef NORMINETTE_ARGS_H
#define NORMINETTE_ARGS_H

#include <stdint.h>
#include <errno.h>
#include <stdbool.h>

typedef struct args_s {
	bool has_colors;
	bool verbose;
	bool name;
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
	enum mistake_name_e *ignored_mistakes;
} args_t;

args_t parse_args(int argc, char **argv);
void free_args(args_t *args);

#endif //NORMINETTE_ARGS_H
