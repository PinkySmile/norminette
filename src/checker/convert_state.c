/*
** EPITECH PROJECT, 2020
** norminette
** File description:
** convert_state.c
*/

#include "convert_state.h"
#include "checker.h"

made_style_error_t convert_state(const checker_state_t *state,\
const char *file, enum mistake_name_e error, long specialValue)
{
	made_style_error_t err;

	err.line = state->line;
	err.column = state->column;
	err.decl_name = state->decl_name;
	err.decl_type = state->decl_name;
	err.file = file;
	err.error = error;
	err.specialValue = specialValue;
	return err;
}