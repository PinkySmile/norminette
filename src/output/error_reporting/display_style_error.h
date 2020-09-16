/*
** EPITECH PROJECT, 2020
** norminette
** File description:
** display_style_error.h
*/

#ifndef NORMINETTE_DISPLAY_STYLE_ERROR_H
#define NORMINETTE_DISPLAY_STYLE_ERROR_H


#include <stdbool.h>

typedef struct style_error_part_s {
	const char *fmt;
	unsigned bg;
	unsigned fg;
	unsigned opts;
} style_error_part_t;

//typedef struct style_error_part_array_s {
//	style_error_part_s
//} style_error_part_array_t;

extern const style_error_part_t *style_error_output_options[];


#endif //NORMINETTE_DISPLAY_STYLE_ERROR_H
