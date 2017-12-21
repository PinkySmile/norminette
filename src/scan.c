/*
** EPITECH PROJECT, 2017
** scan
** File description:
** Scanning files and entire folders
*/

#include "my.h"
#include "global.h"
#include "structs.h"
#include "functions.h"
#include <sys/sysmacros.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

char    *find_path(char *path, char *file_name)
{
	int     path_len = strlen(path);
	int     name_len = strlen(file_name);
	int     extra_len = path[path_len - 1] == '/' ? 0 : 1;
	int     total_length = path_len + name_len + extra_len;
	char    *file_path = malloc(total_length + 1);

	for (int i = 0; i < path_len; i++)
		file_path[i] = path[i];
	if (path[path_len - 1] != '/')
		file_path[path_len] = '/';
	for (int i = 0; i < name_len; i++)
		file_path[i + path_len + extra_len] = file_name[i];
	file_path[total_length] = 0;
	return (file_path);
}

int	is_file_useless(char *path, char *name, flag *flags)
{
	struct stat	info;
	int		cond = 1;
	int		cond2 = 1;

	stat(path, &info);
	cond = name[strlen(name) - 1] == '~';
	if (flags->d)
		printf("\n%s:\n*~ : %s\n", path, name[strlen(name) - 1] == '~' ? "TRUE" : "FALSE");
        cond = (name[0] == '.' && name[1] == '#') || cond;
	if (flags->d)
		printf(".#* : %s\n", (name[0] == '.' && name[1] == '#') ? "TRUE" : "FALSE");
	cond = name[0] == '#' || cond;
	if (flags->d)
		printf("#* : %s\n", name[0] == '#' ? "TRUE" : "FALSE");
	cond = info.st_size == 0 || cond;
	if (flags->d)
		printf("size is null : %s\n", info.st_size == 0 ? "TRUE" : "FALSE");
	cond = info.st_size >= 10000 || cond;
	if (flags->d)
		printf("size is too high : %s\n", info.st_size >= 10000 ? "TRUE" : "FALSE");
	cond2 = name[strlen(name) - 1] == 'o';
	cond2 = name[strlen(name) - 1] == 'a' || cond2;
	cond = (name[strlen(name) - 2] == '.' && cond2) || cond;
	if (flags->d)
		printf("*.a/*.o : %s\n", name[strlen(name) - 2] == '.' && cond2 ? "TRUE" : "FALSE");
	cond2 = (name[strlen(name) - 3] == 'c');
	cond2 = (name[strlen(name) - 4] == 'g' && cond2);
	cond = (name[strlen(name) - 5] == '.' && cond2) || cond;
	if (flags->d)
		printf("*.gcno/*.gcda : %s\n", name[strlen(name) - 5] == '.' && cond2 ? "TRUE" : "FALSE");
	return (cond);
}

void	verify_name(char *file, char *name, int *mistakes, flag *flags)
{
	int	cond = 0;

	for (int i = 0; name[i]; i++) {
		cond = name[i] == '_' || name[i] == '.';
		cond = cond || compare_strings(name, "Makefile");
		if (!((name[i] >= 'a' && name[i] <= 'z') || cond)) {
			mistakes[2]++;
			if (flags->c)
				printf("%s", file);
			else
				display_path(file);
			if (flags->f)
				printf(": Nom invalide%s", flags->v ? "\n\n\n" : "\n");
		        else
				printf(": Invalid name%s", flags->v ? "\n\n\n" : "\n");
		        break;
		}
	}
}

void	scan_folder(char *path, flag *flags, int *mistakes)
{
	struct dirent	*file;
	DIR		*folder = opendir(path);
	char		*file_path;

	if (!folder) {
		write(2, path, strlen(path));
		perror(" ");
		return;
	}
        for (file = readdir(folder); file != 0; file = readdir(folder)) {
		file_path = find_path(path, file->d_name);
		if (flags->u)
			verify_name(file_path, file->d_name, mistakes, flags);
		if (flags->u && is_file_useless(file_path, file->d_name, flags)) {
			mistakes[0]++;
			if (!flags->c)
				printf("\033[31m\033[1m");
			if (flags->f) {
				printf("Fichier inutile '");
				display_path(file_path);
				printf("' trouvé%s", flags->v ? "\n\n\n" : "\n");
			} else {
				printf("Useless file '");
				display_path(file_path);
				printf("' found%s", flags->v ? "\n\n\n" : "\n");
			}
			if (!flags->c)
				printf("\033[0m");
		}
	        if (file->d_name[0] != '.' && is_dir(file_path))
			scan_folder(file_path, flags, mistakes);
		else if(file->d_name[0] != '.')
			scan_file(file_path, flags, mistakes);
		free(file_path);
	}
	closedir(folder);
}

int	is_file_c(char *path)
{
	int	cond = 1;

	cond = path[strlen(path) - 1] == 'c';
	cond = path[strlen(path) - 1] == 'h' || cond;
	cond = path[strlen(path) - 2] == '.' && cond;
	return (cond);
}

void	scan_file(char *path, flag *flags, int *mistakes)
{
	struct stat	info;
	char		answer[3] = "Y\n";

	if (flags->no_big_files)
		answer[0] = 'n';
	if (!is_file_c(path)) {
	        return;
	} else if (stat(path, &info) < 0) {
		write(2, path, strlen(path));
		perror(" ");
		return;
	}
	if (flags->n) {
		if (flags->c) {
			if (flags->f)
				printf("Lecture du fichier %s", path);
			else
				printf("Reading file %s", path);
		} else {
			if (flags->f)
				printf("\033[33;1mLecture du fichier \033[0m");
			else
				printf("\033[33;1mReading file \033[0m");
			display_path(path);
		}
		printf("\n");
	}
	if (info.st_size >= 500000) {
		if (!flags->c)
			printf("\033[0m");
	        printf("Large file found (");
		if (flags->c)
			printf("%s", path);
		else
			display_path(path);
		printf(") : %s%.4lf%s MB\n", flags->c ? "" : "\033[31;1m", (double)info.st_size / 1000000, flags->c ? "" : "\033[0m");
		if (flags->no_big_files)
			printf("Skipping\n");
		else {
			printf("Do you really want to load it ? [Y/n]\n");
			answer[0] = 'a';
		}
	}
	while (!compare_strings(answer, "Y\n") && !compare_strings(answer, "n\n") && !compare_strings(answer, "y\n") && !compare_strings(answer, "N\n")) {
		for (int i = 0; i < 3; i++)
			answer[i] = 0;
		read(0, answer, 2);
		if (!compare_strings(answer, "Y\n") && !compare_strings(answer, "n\n") && !compare_strings(answer, "y\n") && !compare_strings(answer, "n\n"))
			printf("Please answer 'Y' or 'n'\n");
	}
	if (compare_strings(answer, "Y\n") || compare_strings(answer, "y\n")) {
		if (path[strlen(path) - 1] == 'c')
			scan_c_file(path, mistakes, key_words, flags);
		else
			scan_h_file(path, mistakes, flags);
	}
}

void	display_result(int *mistakes, flag *flags)
{
	int	type[3] = {0, 0, 0};
	int	style_mark = 0;

	if (flags->d)
		for (int i = 0; style_names[i]; i++)
			printf("%s : %i\n", style_names[i], mistakes[i]);
	for (int i = 0; style_names[i]; i++)
		if (mistakes[i]) {
			if (flags->c) {
				printf("\n%s", style_names[i]);
				printf(" rule has been violated ");
				printf("%i", mistakes[i]);
				printf(" times ");
				printf(": %s", style_description[i]);
			} else {
				printf("\n\033[31;1m%s\033[0m", style_names[i]);
				printf("\033[1m rule has been violated \033[0m");
				printf("\033[31;1m%i\033[0m", mistakes[i]);
				printf("\033[1m times \033[0m");
				printf(": \033[91m%s\033[0m", style_description[i]);
			}
			type[style_type[i]] += mistakes[i];
		}
	if (type[0] != 0 || type[1] != 0 || type[2] != 0)
		printf("\n\n");
	else if (flags->n)
		printf("\n");
	style_mark = type[0] + type[1] + 5 * type[2];
	if(flags->c) {
		printf("info : ");
		printf("%i  ", type[0]);
		printf("minor : ");
		printf("%i ", type[1]);
		printf("major : ");
		printf("%i\n", type[2]);
		printf("Style mark : ");
		printf("%i\n", -style_mark);
	} else {
		printf("\033[96minfo\033[0m : ");
		printf("\033[%i;1m%i\033[0m  ", type[0]? 31 : 32, type[0]);
		printf("\033[33mminor\033[0m : ");
		printf("\033[%i;1m%i\033[0m  ", type[1] ? 31 : 32, type[1]);
		printf("\033[31mmajor\033[0m : ");
		printf("\033[%i;1m%i\033[0m\n", type[2] ? 31 : 32, type[2]);
		printf("\033[1mStyle mark\033[0m : ");
		printf("\033[%im%i\033[0m\n", style_mark == 0 ? 32 : 31, -style_mark);
	}
	exit(style_mark != 0);
}
