/*
** EPITECH PROJECT, 2020
** norminette
** File description:
** convert_state.c
*/

#include "convert_state.h"
#include "checker.h"

made_style_error_t convert_state(const checker_state_t *state,\
const char *file, enum mistake_name_e error, long long special_value)
{
	made_style_error_t err;

	err.line = state->src_state.line;
	err.column = state->src_state.column;
	err.decl_name = state->src_state.decl_name;
	err.decl_type = state->src_state.decl_type;
	err.file = file;
	err.error = error;
	err.specialValue = special_value;
	return err;
}