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
#include "is_file_useless.h"
#include "../utils/concat.h"
#include "../utils/files.h"
#include "../utils/exceptions.h"
#include "../utils/regex.h"
#include "../output/error_reporting.h"
#include "../output/debug.h"

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
	try {
		if (is_dir(path))
			check_folder(state, path);
		else
			check_file(state, path, false);
	} catch(FileNotFoundException) {
		fprintf(stderr, "Error: %s\n", get_last_exception_desc());
		return;
	} end_try
}

void check_folder(checker_state_t *state, const char *path)
{
	struct dirent *file;
	DIR           *folder = opendir(path);
	char          *file_path;

	if (!folder)
		file_not_found(path);

	for (file = readdir(folder); file; file = readdir(folder)) {
		file_path = concat(3, path, "/", file->d_name);
		if (file->d_name[0] != '.')
			check_path(state, file_path);
		free(file_path);
	}
	closedir(folder);
}

void check_file(checker_state_t *state, const char *path, bool force)
{
	FILE *stream;

	if (state->args->useless_files && is_file_useless(path))
		add_error_no_line(state, path, USELESS_FILE, 0);

	if (force || match_regex("^.*[.](c|h)$", path)) {
		log_debug("Opening %s", path);
		stream = fopen(path, "rb");
		if (!stream)
			file_not_found(path);
		check_stream(state, stream);
		fclose(stream);
	} else
		log_debug("Skipping non source file %s", path);
}

void check_stream(checker_state_t *state, FILE *stream)
{
	(void)state;
	(void)stream;
}
