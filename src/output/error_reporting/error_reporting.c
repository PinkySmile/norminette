/*
** EPITECH PROJECT, 2020
** norminette
** File description:
** error_reporting.c
*/

#include <stdio.h>
#include "../error_reporting.h"

void show_made_style_error_no_line(made_style_error_t error, bool color)
{
	display_start(error, color, false);
	printf("\n");
}

void show_made_style_error(made_style_error_t error, bool color)
{
	display_start(error, color, true);
	printf("\n");
}

void display_errored_line(made_style_error_t error, const char *line,\
unsigned error_len, bool color)
{
	(void)error;
	(void)line;
	(void)error_len;
	(void)color;
}