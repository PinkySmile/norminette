/*
** EPITECH PROJECT, 2020
** norminette
** File description:
** display_error_start.c
*/

#include <stdio.h>
#include "../color.h"
#include "../error_reporting.h"

void display_path(const char *path, bool color)
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
			change_output_properties(color, RESET, BLUE, BOLD);
		if (path[i] == '/')
			change_output_properties(color, RESET, LIGHTGRAY, BOLD);
		changed_color = path[i] == '/';
		printf("%c", path[i]);
	}
#endif
}

void show_line_nb(bool color, unsigned line, unsigned column)
{
	printf(" [");
	change_output_properties(color, RESET, GREEN, BOLD);
	printf("%i", line);
	change_output_properties(color, RESET, RESET, BOLD);
	printf(":");
	change_output_properties(color, RESET, GREEN, BOLD);
	printf("%i", column);
	change_output_properties(color, RESET, RESET, BOLD);
	printf("]");
}

void display_start(made_style_error_t error, bool color, bool has_line_no)
{
	display_path(error.file, color);
	change_output_properties(color, RESET, RESET, BOLD);
	if (has_line_no)
		show_line_nb(color, error.line, error.column);
	if (error.decl_type) {
		printf(" in %s '", error.decl_type);
		change_output_properties(color, RESET, RED, BOLD);
		printf("%s", error.decl_name);
		change_output_properties(color, RESET, RESET, BOLD);
		printf("'");
	}
	printf(": ");
}
