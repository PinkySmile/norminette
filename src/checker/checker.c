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
#include "../output/debug.h"
#include "get_source_type.h"
#include "check_makefile/check_makefile.h"
#include "check_sources/check_header.h"
#include "check_sources/check_source.h"
#include "recap.h"

int check_paths(const args_t *args, char **paths)
{
	checker_state_t state;

	memset(&state, 0, sizeof(state));
	state.args = args;
	for (int i = 0; paths[i]; i++)
		check_path(&state, paths[i]);
	return make_scan_recap(&state);
}

void check_path(checker_state_t *state, const char *path)
{
	const char *name = get_file_name(path);

	for (int i = 0; state->args->excluded && state->args->excluded[i]; i++)
		if (match_regex(state->args->excluded[i], name))
			return;

	try {
		if (is_dir(path))
			check_folder(state, path);
		else
			check_file(state, path, false);
	} catch(FileNotFoundException) {
		fprintf(stderr, "Error: %s\n", get_last_exception_desc());
	} end_try
}

void check_folder(checker_state_t *state, const char *path)
{
	struct dirent *file;
	DIR           *folder = opendir(path);
	char          *file_path;

	if (!folder)
		throw_file_not_found(path);

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
	const char *reason = NULL;
	enum source_type_e type = get_source_type(path);

	if (is_file_useless(path, &reason))
		add_error_no_line(state, path, USELESS_FILE, (long)reason);

	if (force || type) {
		log_debug("Opening %s", path);
		stream = fopen(path, "rb");
		if (!stream)
			throw_file_not_found(path);
		check_stream(state, stream, path, type);
		fclose(stream);
	} else
		log_debug("Skipping non source file %s", path);
}

void check_stream(checker_state_t *state, FILE *stream, const char *path,\
enum source_type_e type)
{
	switch (type) {
	case MAKEFILE:
		return check_makefile(state, stream, path);
	case SOURCE_FILE:
		return check_source(state, stream, path);
	case HEADER_FILE:
		return check_header(state, stream, path);
	default:
		return;
	}
}
