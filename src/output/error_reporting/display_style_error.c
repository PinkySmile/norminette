/*
** EPITECH PROJECT, 2false2false
** norminette
** File description:
** display_style_error.c
*/

#include <stdio.h>
#include <stddef.h>
#include "display_style_error.h"
#include "../color.h"
#include "../error_reporting.h"

static const style_error_part_t useless_file[] = {
	{"Useless file found", RESET, RESET, BOLD},
	{NULL, RESET, RESET, NORMAL}
};

static const style_error_part_t too_mny_fct[] = {
	{"File contain too many functions (", RESET, RESET, BOLD},
	{"%i", RESET, RED, BOLD},
	{")", RESET, RESET, BOLD},
	{NULL, RESET, RESET, NORMAL}
};

static const style_error_part_t invalid_file_name[] = {
	{"The file name is invalid", RESET, RESET, BOLD},
	{NULL, RESET, RESET, NORMAL}
};

static const style_error_part_t invalid_header[] = {
	{"Invalid EPITECH header", RESET, RESET, BOLD},
	{NULL, RESET, RESET, NORMAL}
};

static const style_error_part_t empty_line_between_fcts[] = {
	{"Bad function separator", RESET, RESET, BOLD},
	{NULL, RESET, RESET, NORMAL}
};

static const style_error_part_t invalid_fct_name[] = {
	{"Invalid function name", RESET, RESET, BOLD},
	{NULL, RESET, RESET, NORMAL}
};

static const style_error_part_t too_long_line[] = {
	{"Too long line (", RESET, RESET, BOLD},
	{"%i", RESET, RED, BOLD},
	{" columns)", RESET, RESET, BOLD},
	{NULL, RESET, RESET, NORMAL}
};

static const style_error_part_t too_long_fct[] = {
	{"Too long function (", RESET, RESET, BOLD},
	{"%i", RESET, RED, BOLD},
	{" lines)", RESET, RESET, BOLD},
	{NULL, RESET, RESET, NORMAL}
};

static const style_error_part_t too_many_args[] = {
	{"Function should not take more than 4 arguments and take"
	"void if none (", RESET, RESET, BOLD},
	{"%i", RESET, RED, BOLD},
	{" arguments)", RESET, RESET, BOLD},
	{NULL, RESET, RESET, NORMAL}
};

static const style_error_part_t comment_in_fct[] = {
	{"Comment inside a function", RESET, RESET, BOLD},
	{NULL, RESET, RESET, NORMAL}
};

static const style_error_part_t more_than_one_act_by_line[] = {
	{"More than a single action on a line (", RESET, RESET, BOLD},
	{"%i", RESET, RED, BOLD},
	{" actions)", RESET, RESET, BOLD},
	{NULL, RESET, RESET, NORMAL}
};

static const style_error_part_t bad_indentation[] = {
	{"Bad indentation (", RESET, RESET, BOLD},
	{"%s", RESET, RED, BOLD},
	{")", RESET, RESET, BOLD},
	{NULL, RESET, RESET, NORMAL}
};

static const style_error_part_t space_missing[] = {
	{"Space missing after keyword '", RESET, RESET, BOLD},
	{"%s", RESET, RED, BOLD},
	{"'", RESET, RESET, BOLD},
	{NULL, RESET, RESET, NORMAL}
};

static const style_error_part_t bracket_misplaced[] = {
	{"Bracket misplaced", RESET, RESET, BOLD},
	{NULL, RESET, RESET, NORMAL}
};

static const style_error_part_t multiple_vars_declared[] = {
	{"Multiple variables declared on the same line (",
	RESET, RESET, BOLD},
	{"%i", RESET, RED, BOLD},
	{")", RESET, RESET, BOLD},
	{NULL, RESET, RESET, NORMAL}
};

static const style_error_part_t missing_line_break_after_vars[] = {
	{"Line break after variable declaration is missing",
	RESET, RESET, BOLD},
	{NULL, RESET, RESET, NORMAL}
};

static const style_error_part_t invalid_type_name[] = {
	{"Invalid type name '", RESET, RESET, BOLD},
	{"%s", RESET, RED, BOLD},
	{"'", RESET, RESET, BOLD},
	{NULL, RESET, RESET, NORMAL}
};

static const style_error_part_t pointer_declaration[] = {
	{"Pointer symbol detached from variable name", RESET, RESET, NORMAL},
	{NULL, RESET, RESET, NORMAL}
};

static const style_error_part_t if_depth[] = {
	{"Conditional branching to deep or too many branching for an if (",
	RESET, RESET, BOLD},
	{"%s", RESET, RED, BOLD},
	{")", RESET, RESET, BOLD},
	{NULL, RESET, RESET, NORMAL}
};

static const style_error_part_t goto_used[] = {
	{"Goto keyword used", RESET, RESET, NORMAL},
	{NULL, RESET, RESET, NORMAL}
};

static const style_error_part_t separation_source_header[] = {
	{"Bad separation between header and source file: %s",
	RESET, RESET, NORMAL},
	{NULL, RESET, RESET, NORMAL}
};

static const style_error_part_t trailing_space[] = {
	{"Trailing %s found", RESET, RESET, BOLD},
	{NULL, RESET, RESET, NORMAL}
};

static const style_error_part_t trailing_empty_line[] = {
	{"Trailing empty line found", RESET, RESET, BOLD},
	{NULL, RESET, RESET, NORMAL}
};

static const style_error_part_t semicolon_isolated[] = {
	{"Semicolon isolated from other tokens", RESET, RESET, BOLD},
	{NULL, RESET, RESET, NORMAL}
};

static const style_error_part_t identifier_l_o[] = {
	{"Identifiers should not be composed of only l and o (",
	RESET, RESET, BOLD},
	{"%s", RESET, RED, BOLD},
	{")", RESET, RESET, BOLD},
	{NULL, RESET, RESET, NORMAL}
};

static const style_error_part_t forbidden_fct_used[] = {
	{"Forbidden function '", RESET, RESET, BOLD},
	{"%s", RESET, RED, BOLD},
	{"' used", RESET, RESET, BOLD},
	{NULL, RESET, RESET, NORMAL}
};

static const style_error_part_t too_long_file_name[] = {
	{"Too long file name (", RESET, RESET, BOLD},
	{"%i", RESET, RED, BOLD},
	{" characters)", RESET, RESET, BOLD},
	{NULL, RESET, RESET, NORMAL}
};


const style_error_part_t *style_error_output_options[] = {
	useless_file,
	too_mny_fct,
	invalid_file_name,
	invalid_header,
	empty_line_between_fcts,
	invalid_fct_name,
	too_long_line,
	too_long_fct,
	too_many_args,
	comment_in_fct,
	more_than_one_act_by_line,
	bad_indentation,
	space_missing,
	bracket_misplaced,
	multiple_vars_declared,
	missing_line_break_after_vars,
	invalid_type_name,
	pointer_declaration,
	if_depth,
	goto_used,
	separation_source_header,
	trailing_space,
	trailing_empty_line,
	semicolon_isolated,
	identifier_l_o,
	forbidden_fct_used,
	too_long_file_name
};

void display_style_error(const made_style_error_t *error, bool color)
{
	const style_error_part_t *output_options;

	output_options = style_error_output_options[error->error];
	while (output_options->fmt) {
		change_output_properties(
			color,
			output_options->bg,
			output_options->fg,
			output_options->opts
		);
		printf(output_options->fmt, error->specialValue);
		output_options++;
	}
}