/*
** EPITECH PROJECT, 2020
** norminette
** File description:
** check_c_file.c
*/

#include <memory.h>
#include "check_c_file.h"

void reset_state(checker_state_t *state, FILE *stream)
{
	rewind(stream);
	memset(&state->src_state, 0, sizeof(state->src_state));
	state->src_state.line = 1;
}

void check_common_header_source(checker_state_t *state, FILE *stream,\
const char *path)
{

}

void check_code(checker_state_t *state, FILE *stream, const char *path,\
bool is_header)
{

}

void check_c_file(checker_state_t *state, FILE *stream, const char *path,\
bool is_header)
{
	reset_state(state, stream);
	check_common_header_source(state, stream, path);
	reset_state(state, stream);
	while (!feof(stream))
		check_code(state, stream, path, is_header);
}