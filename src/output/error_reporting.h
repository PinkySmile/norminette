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
	const char *file;
	const char *decl_name;
	const char *decl_type;
	enum mistake_name_e error;
} made_style_error_t;

void display_start(made_style_error_t error, bool color, bool has_line_no);
void display_path(const char *path, bool color);
void show_made_style_error_no_line(made_style_error_t error, bool color);
void show_made_style_error(made_style_error_t error, bool color);
void display_errored_line(made_style_error_t error, const char *line,\
unsigned error_len, bool color);

#define add_error(state, line_nb, col, file, error, line, len)\
(state).mistakes_counts[error]++,\
show_error(line_nb, col, file, error, (state).decl_name, (state).decl_type\
line, len, *(state).context *(state).args)

#define show_error(line_no, col_no, file_name, error, decl_name, decl_type,\
line, len) if(true){ show_made_style_error(\
(made_style_error_t){line_no, col_no, file_name, decl_name, decl_type, error}\
, (opts).has_colors);\
if (opts.verbose) display_errored_line(\
(made_style_error_t){line_no, col_no, file_name, decl_name, decl_type, error}\
line, len, (opts).has_colors);}else{}

#define add_error_no_line(state, file_name, error)\
(state).mistakes_counts[error]++,\
show_error_no_line(file_name, error, (state).decl_name, (state).decl_type,\
*(state).args)

#define show_error_no_line(file_name, error, decl_name, decl_type, opts)\
show_made_style_error_no_line(\
(made_style_error_t){0, 0, file_name, decl_name, decl_type, error},\
(opts).has_colors)

#define change_output_properties(color, bg, fg, prop){if (color){ \
set_output_properties(bg, fg, prop);}}

#endif //NORMINETTE_ERROR_REPORTING_H
