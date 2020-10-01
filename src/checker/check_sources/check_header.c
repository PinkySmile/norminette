/*
** EPITECH PROJECT, 2020
** norminette
** File description:
** check_header.c
*/

#include "check_header.h"
#include "file_checker/check_c_file.h"

void check_header(checker_state_t *state, FILE *stream, const char *path)
{
	check_c_file(state, stream, path, true);
}