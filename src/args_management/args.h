//
// Created by andgel on 04/09/2020
//

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

#endif //NORMINETTE_ARGS_H
