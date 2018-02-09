/*
** EPITECH PROJECT, 2017
** structs header
** File description:
** Contains all structures
*/

#ifndef _STRUCTS_H_
#define _STRUCTS_H_

enum    mistake_name {
        GARBAGE,
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
        MULTPLE_VARS_DECLARED,
        MISSING_LINE_BREAK_AFTER_VARS,
        POINTER_DECLARATION,
        IF_DEPTH,
        GOTO_USED,
        INVALID_TYPE_NAME,
        SEPARATION_SOURCE_HEADER,
        TRAILING_SPACE,
        TRAILING_EMPTY_LINE,
        SEMICOLON_ISOLATED,
        IDENTIFIER_L_O,
        FORBIDDEN_FCT_USED,
        TOO_LONG_FILE_NAME,
};

typedef struct list_s {
	void		*data;
	struct list_s	*next;
	struct list_s	*prev;
} list_t;

typedef struct {
	char	*name;
	int	count;
} b_fcts_t;

typedef struct {
	int	v;
	int	f;
	int	n;
	int	u;
	int	d;
	int	c;
	int	b;
	int	i_caps;
	int	big_files;
	int	no_big_files;
	list_t	*fcts;
	list_t	*b_fcts;
} flag;

#endif
