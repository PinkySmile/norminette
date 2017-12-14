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

char    *find_path(char *path, char *file_name)
{
	int     path_len = my_strlen(path);
	int     name_len = my_strlen(file_name);
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
	cond = name[my_strlen(name) - 1] == '~';
	if (flags->d)
		my_printf("*~ : %s\n", cond ? "TRUE" : "FALSE");
        cond = (name[0] == '.' && name[1] == '#') || cond;
	if (flags->d)
		my_printf(".#* : %s\n", cond ? "TRUE" : "FALSE");
	cond = name[0] == '#' || cond;
	if (flags->d)
		my_printf("#* : %s\n", cond ? "TRUE" : "FALSE");
	cond = info.st_size == 0 || cond;
	if (flags->d)
		my_printf("size is null : %s\n", cond ? "TRUE" : "FALSE");
	cond = info.st_size >= 10000 || cond;
	if (flags->d)
		my_printf("size is too high : %s\n", cond ? "TRUE" : "FALSE");
	cond2 = name[my_strlen(name) - 1] == 'o';
	cond2 = name[my_strlen(name) - 1] == 'a' || cond2;
	cond = (name[my_strlen(name) - 2] == '.' && cond2) || cond;
	if (flags->d)
		my_printf("*.a/*.o : %s\n", cond ? "TRUE" : "FALSE");
	cond2 = (name[my_strlen(name) - 3] == 'c');
	cond2 = (name[my_strlen(name) - 4] == 'g' && cond2);
	cond = (name[my_strlen(name) - 5] == '.' && cond2) || cond;
	if (flags->d)
		my_printf("*.gcno/*.gcda : %s\n", cond ? "TRUE" : "FALSE");
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
			if (flags->f)
				my_printf("\033[31;1m%s: Nom invalide\n", file);
		        else
				my_printf("\033[31;1m%s: Invalid name\n", file);
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
		my_printf("%m%m", path, ": ");
		perror("");
		return;
	}
        for (file = readdir(folder); file != 0; file = readdir(folder)) {
		file_path = find_path(path, file->d_name);
		if (flags->f)
			verify_name(file_path, file->d_name, mistakes, flags);
		if (flags->f && is_file_useless(file_path, file->d_name, flags)) {
			mistakes[0]++;
			if (flags->f) {
				my_printf("\033[31m\033[1mFichier inutile ");
				my_printf("'%s' trouvé\033[0m\n", file_path);
			} else {
				my_printf("\033[31m\033[1mUseless file ");
				my_printf("'%s' found\033[0m\n", file_path);
			}
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

	cond = path[my_strlen(path) - 1] == 'c';
	cond = path[my_strlen(path) - 1] == 'h' || cond;
	cond = path[my_strlen(path) - 2] == '.' && cond;
	return (cond);
}

void	scan_file(char *path, flag *flags, int *mistakes)
{
	struct stat	info;

	if (!is_file_c(path)) {
	        return;
	} else if (stat(path, &info) < 0) {
		my_printf("%m%m", path, ": ");
		perror("");
		return;
	}
	if (flags->n)
		my_printf("\033[33;1mReading file %s\033[0m\n", path);
	if (path[my_strlen(path) - 1] == 'c')
		scan_c_file(path, mistakes, key_words, flags);
	else
		scan_h_file(path, mistakes, flags);
}

void	display_result(int *mistakes, flag *flags)
{
	int	type[3] = {0, 0, 0};
	int	style_mark = 0;

	if (flags->d)
		for (int i = 0; style_names[i]; i++)
			my_printf("%s : %i\n", style_names[i], mistakes[i]);
	for (int i = 0; style_names[i]; i++)
		if (mistakes[i]) {
		        my_printf("\n\033[31;1m%s\033[0m", style_names[i]);
			my_printf("\033[1m rule has been violated \033[0m");
			my_printf("\033[31;1m%i\033[0m", mistakes[i]);
			my_printf("\033[1m times \033[0m");
			my_printf(": \033[91m%s\033[0m", style_description[i]);
			type[style_type[i]] += mistakes[i];
		}
	if (type[0] != 0 || type[1] != 0 || type[2] != 0)
		my_putstr("\n\n");
	else if (flags->n)
		my_putchar('\n');
	my_printf("\033[96minfo\033[0m : ");
	my_printf("\033[%i;1m%i\033[0m  ", type[0]? 31 : 32, type[0]);
	my_printf("\033[33mminor\033[0m : ");
	my_printf("\033[%i;1m%i\033[0m  ", type[1] ? 31 : 32, type[1]);
	my_printf("\033[31mmajor\033[0m : ");
	my_printf("\033[%i;1m%i\033[0m\n", type[2] ? 31 : 32, type[2]);
	my_printf("\033[1mStyle mark\033[0m : ");
	style_mark = type[0] + type[1] + 5 * type[2];
	my_printf("\033[%im%i\033[0m\n", style_mark == 0 ? 32 : 31, -style_mark);
	exit(style_mark != 0);
}
