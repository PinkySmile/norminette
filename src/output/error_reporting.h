/*
** EPITECH PROJECT, 2020
** norminette
** File description:
** error_reporting.h
*/

#ifndef NORMINETTE_ERROR_REPORTING_H
#define NORMINETTE_ERROR_REPORTING_H

#include "../args_management/args.h"
#include <stdbool.h>
#include "../data/style_errors.h"

typedef struct made_style_error_s {
	unsigned line;
	unsigned column;
	const char *decl_name;
	const char *decl_type;
	const char *file;
	enum mistake_name_e error;
	long specialValue;
} made_style_error_t;

void display_start(made_style_error_t error, bool color, bool has_line_no);
void display_path(const char *path, bool color);
void show_made_style_error_no_line(made_style_error_t error, bool color);
void show_made_style_error(made_style_error_t error, bool color);
void display_errored_line(made_style_error_t error, const char *line,\
unsigned error_len, bool color);

#define show_error(error, opts, line, len){\
	show_made_style_error(error, (opts).has_colors);\
	if (opts.verbose)\
		display_errored_line(error, line, len, (opts).has_colors);\
}

#define change_output_properties(color, bg, fg, prop){if (color){ \
set_output_properties(bg, fg, prop);}}

#endif //NORMINETTE_ERROR_REPORTING_H
