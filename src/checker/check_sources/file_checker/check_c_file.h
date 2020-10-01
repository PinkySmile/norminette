/*
** EPITECH PROJECT, 2020
** norminette
** File description:
** check_c_file.h
*/

#include "../../checker.h"

#ifndef NORMINETTE_CHECK_C_FILE_H
#define NORMINETTE_CHECK_C_FILE_H


void reset_state(checker_state_t *state, FILE *stream);
void check_c_file(checker_state_t *state, FILE *stream, const char *path,\
bool is_header);
void check_common_header_source(checker_state_t *state, FILE *stream,\
const char *path);

#endif //NORMINETTE_CHECK_C_FILE_H
