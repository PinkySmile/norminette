/*
** EPITECH PROJECT, 2020
** norminette
** File description:
** checker.c
*/

#include <memory.h>
#include <dirent.h>
#include <malloc.h>
#include "checker.h"
#include "../utils/concat.h"
#include "../utils/file_types.h"
#include "is_file_useless.h"
#include "../output/error_reporting.h"

void check_paths(const args_t *args, char **paths)
{
	checker_state_t state;

	memset(&state, 0, sizeof(state));
	state.args = args;
	for (int i = 0; paths[i]; i++)
		check_path(&state, paths[i]);
}

void check_path(checker_state_t *state, const char *path)
{
	if (is_dir(path))
		check_folder(state, path);
	else
		check_file(state, path, false);
}

void check_folder(checker_state_t *state, const char *path)
{
	struct dirent *file;
	DIR           *folder = opendir(path);
	char          *file_path;

	if (!folder)
		return perror(path);

	for (file = readdir(folder); file; file = readdir(folder)) {
		file_path = concat(3, path, "/", file->d_name);
		if (file->d_name[0] != '.')
			check_path(state, file_path);
		free(file_path);
	}
}

void check_file(checker_state_t *state, const char *path, bool force)
{
	if (state->args->useless_files && is_file_useless(path))
		add_error_no_line(*state, path, USELESS_FILE);
}

void check_stream(checker_state_t *state, FILE *stream)
{

}
