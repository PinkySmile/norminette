/*
** EPITECH PROJECT, 2020
** norminette
** File description:
** style_errors.h
*/

#ifndef NORMINETTE_STYLE_ERRORS_H
#define NORMINETTE_STYLE_ERRORS_H

enum mistake_name_e {
	USELESS_FILE,
	TOO_MNY_FCT,
	INVALID_FILE_NAME,
	INVALID_HEADER,
	EMPTY_LINE_BETWEEN_FCTS,
	INVALID_FCT_NAME,
	TOO_LONG_LINE,
	TOO_LONG_FCT,
	TOO_MANY_ARGS,
	COMMENT_IN_FCT,
	MORE_THAN_ONE_ACT_BY_LINE,
	BAD_INDENTATION,
	SPACE_MISSING,
	BRACKET_MISPLACED,
	MULTIPLE_VARS_DECLARED,
	MISSING_LINE_BREAK_AFTER_VARS,
	INVALID_TYPE_NAME,
	POINTER_DECLARATION,
	IF_DEPTH,
	GOTO_USED,
	SEPARATION_SOURCE_HEADER,
	TRAILING_SPACE,
	TRAILING_EMPTY_LINE,
	SEMICOLON_ISOLATED,
	IDENTIFIER_L_O,
	FORBIDDEN_FCT_USED,
	TOO_LONG_FILE_NAME,
	NB_OF_MISTAKES
};

extern const char *mistake_names[];

typedef struct style_error_s {
	char *name;
	char *desc;
	int type;
} style_error_t;

extern const style_error_t coding_style[];

char const *mistake_name_to_string(enum mistake_name_e mistake);
enum mistake_name_e mistake_name_from_string(const char *name);

#endif //NORMINETTE_STYLE_ERRORS_H
