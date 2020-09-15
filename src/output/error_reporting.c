/*
** EPITECH PROJECT, 2020
** norminette
** File description:
** error_reporting.c
*/

#include <stdio.h>
#include "color.h"
#include "error_reporting.h"

static inline void display_path(const char *path, bool color)
{
	bool changed_color = false;

#ifdef _WIN32
	for (int i = 0; path[i]; i++) {
		if (changed_color && path[i] != '/' && path[i] != '\\' && color)
			set_output_properties(BLACK, BLUE, BOLD);
		if (path[i] == '/' || path[i] == '\\')
			set_output_properties(BLACK, LIGHTGRAY, BOLD);
		changed_color = path[i] == '/' || path[i] != '\\';
		printf("%c", path[i]);
	}
#else
	for (int i = 0; path[i]; i++) {
		if (changed_color && path[i] != '/')
			change_output_properties(color, BLACK, BLUE, BOLD);
		if (path[i] == '/')
			change_output_properties(color, BLACK, LIGHTGRAY, BOLD);
		changed_color = path[i] == '/';
		printf("%c", path[i]);
	}
#endif
}

static inline void display_start(made_style_error_t error, bool color)
{
	display_path(error.file, color);
	change_output_properties(color, BLACK, WHITE, BOLD);
	printf(" [");
	change_output_properties(color, BLACK, GREEN, BOLD);
	printf("%i", error.line);
	change_output_properties(color, BLACK, WHITE, BOLD);
	printf(":");
	change_output_properties(color, BLACK, GREEN, BOLD);
	printf("%i", error.column);
	change_output_properties(color, BLACK, WHITE, BOLD);
	printf("]");
	if (error.fct_name) {
		printf(" in function '");
		change_output_properties(color, BLACK, RED, BOLD);
		printf("%s", error.fct_name);
		change_output_properties(color, BLACK, WHITE, BOLD);
		printf("'");
	}
	printf(": ");
}

void show_made_style_error(made_style_error_t error, bool color)
{
	display_start(error, color);
}

void display_errored_line(made_style_error_t error, char *line,\
unsigned error_len, bool color)
{

}