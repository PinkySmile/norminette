/*
** EPITECH PROJECT, 2020
** norminette
** File description:
** checker.h
*/

#ifndef NORMINETTE_CHECKER_H
#define NORMINETTE_CHECKER_H


#include <stdio.h>
#include "convert_state.h"
#include "../utils/is_in_list.h"
#include "../args_management/args.h"
#include "../data/style_errors.h"
#include "../output/error_reporting.h"
#include "check_sources/file_checker/checkers/state.h"

enum source_type_e {
	UNKNOWN_FILE,
	MAKEFILE,
	HEADER_FILE,
	SOURCE_FILE,
};

typedef struct checker_state_s {
	const args_t *args;
	source_checker_state_t src_state;
	unsigned lines_scanned;
	unsigned mistakes_counts[NB_OF_MISTAKES];
} checker_state_t;

int check_paths(const args_t *args, char **paths);
void check_path(checker_state_t *state, const char *path);
void check_folder(checker_state_t *state, const char *path);
void check_file(checker_state_t *state, const char *path, bool force);
void check_stream(checker_state_t *state, FILE *stream, const char *path,\
enum source_type_e type);

#define add_error(state, file, err, line, len, val)\
{(state)->mistakes_counts[err]++;\
if (!is_mistake_ignored(state->args->ignored_mistakes, err))\
show_error(\
convert_state(state, file, err, val), (state)->args->has_colors, line, len);}do\
{while(0)

#define add_error_no_line(state_ptr, file, err, val)\
{(state_ptr)->mistakes_counts[err]++;\
if (!is_mistake_ignored(state->args->ignored_mistakes, err))\
show_made_style_error_no_line(\
convert_state(state_ptr, file, err, val), (state_ptr)->args->has_colors);}do{}\
while(0)


#endif //NORMINETTE_CHECKER_H
