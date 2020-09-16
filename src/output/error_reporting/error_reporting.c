/*
** EPITECH PROJECT, 2020
** norminette
** File description:
** error_reporting.c
*/

#include <stdio.h>
#include "../color.h"
#include "../error_reporting.h"

static void show_whole_error(made_style_error_t *error, bool color, bool line)
{
	display_start(error, color, line);
	change_output_properties(color, RESET, RESET, BOLD);
	display_style_error(error, color);
	printf(".\n");
}

void show_made_style_error_no_line(made_style_error_t error, bool color)
{
	show_whole_error(&error, color, false);
}

void show_made_style_error(made_style_error_t error, bool color)
{
	show_whole_error(&error, color, true);
}

void display_errored_line(made_style_error_t error, const char *line,\
unsigned error_len, bool color)
{
	(void)error;
	(void)line;
	(void)error_len;
	(void)color;
}