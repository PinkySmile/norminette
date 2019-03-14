/*
65;5401;1c** EPITECH PROJECT, 2017
** structs header
** File description:
** Contains all structures
*/

#ifndef _STRUCTS_H_
#define _STRUCTS_H_

#include <stdbool.h>

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
	ETIENNE = 29,
};

typedef struct list_s {
	void		*data;
	struct list_s	*next;
	struct list_s	*prev;
} list_t;

typedef struct {
	int	line;
	int	depth;
	int	if_nbr;
} if_branch;

typedef struct {
	char	*name;
	char	*desc;
	int	type;
} style_error;

typedef struct {
	char	*name;
	int	count;
} b_fcts_t;

typedef struct {
	bool	v;
	bool	f;
       	bool	n;
	bool	u;
	bool	d;
	bool	c;
	bool	b;
	bool	t;
	bool	i_caps;
	bool	big_files;
	bool	no_big_files;
	bool	cappuccino;
	bool	only_tab_indent;
	int	default_indent;
	int	tab_size;
	int	infos_points;
	int	minor_points;
	int	major_points;
	list_t	*fcts;
	list_t	*b_fcts;
} flag;

struct Test {

};

typedef struct Test Machin;

#endif
