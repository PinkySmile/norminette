/*
** EPITECH PROJECT, 2020
** norminette
** File description:
** check_source.c
*/

#include "check_source.h"
#include "file_checker/check_c_file.h"

void check_source(checker_state_t *state, FILE *stream, const char *path)
{
	check_c_file(state, stream, path, false);
}