//
// Created by andgel on 04/09/2020
//

#ifndef NORMINETTE_ERROR_REPORTING_H
#define NORMINETTE_ERROR_REPORTING_H

#include "../args_management/args.h"
#include <stdbool.h>
#include "../data/style_errors.h"

typedef struct made_style_error_s {
	unsigned line;
	unsigned column;
	const char *file;
	const char *fct_name;
	enum mistake_name_e error;
} made_style_error_t;

void show_made_style_error(made_style_error_t error, bool color);
void display_errored_line(made_style_error_t error, char *line,\
unsigned error_len, bool color);

#define show_error(line_no, column_no, file_name, error, line, len, opts)\
show_made_style_error(\
	(made_style_error_t){line_no, column_no, file_name, error}\
, opts.has_colors);\
if (opts.verbose)\
	display_errored_line(\
		(made_style_error_t){line_no, column_no, file_name, error}\
	line, len, opts.has_colors)


#endif //NORMINETTE_ERROR_REPORTING_H
