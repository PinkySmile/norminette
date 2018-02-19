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
#include "stacktrace.h"
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
	char    *file_path = my_malloc(total_length + 1);

	addStackTraceEntry("find_path", "pp", "path", path, "file_name", file_name);
	for (int i = 0; i < path_len; i++)
		file_path[i] = path[i];
	if (path[path_len - 1] != '/')
		file_path[path_len] = '/';
	for (int i = 0; i < name_len; i++)
		file_path[i + path_len + extra_len] = file_name[i];
	file_path[total_length] = 0;
	delStackTraceEntry();
	return (file_path);
}

int	is_file_useless(char *path, char *name, flag *flags)
{
	struct stat	info;
	int		cond = 1;
	int		cond2 = 1;

	addStackTraceEntry("is_file_useless", "ppp", "path", path, "name", name, "flags", flags);
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
	delStackTraceEntry();
	return (cond);
}

void	verify_name(char *file, char *name, int *mistakes, flag *flags)
{
	int	cond = 0;

	addStackTraceEntry("verify_name", "pppp", "file", file, "name", name, "mistakes", mistakes, "flags", flags);
	for (int i = 0; name[i]; i++) {
		cond = name[i] == '_' || name[i] == '.';
		cond = cond || compare_strings(name, "Makefile");
		if (!(((name[i] >= 'a' && name[i] <= 'z') || (name[i] >= '0' && name[i] <= '9')) || cond)) {
			mistakes[INVALID_FILE_NAME]++;
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
	delStackTraceEntry();
}

void	scan_folder(char *path, flag *flags, int *mistakes)
{
	struct dirent	*file;
	DIR		*folder;
	char		*file_path;

	addStackTraceEntry("scan_folder", "ppp", "path", path, "flags", flags, "mistakes", mistakes);
	folder = opendir(path);
	if (!folder) {
		if (!flags->c)
		        write(2, "\033[31;1m", 7);
		write(2, "Error : ", 8);
		perror(path);
		if (!flags->c)
			write(2, "\033[0m", 4);
		write(2, "\n", 1);
		delStackTraceEntry();
		return;
	}
        for (file = readdir(folder); file != 0; file = readdir(folder)) {
		file_path = find_path(path, file->d_name);
		if (flags->u)
			verify_name(file_path, file->d_name, mistakes, flags);
		if (flags->u && is_file_useless(file_path, file->d_name, flags)) {
			mistakes[GARBAGE]++;
			if (flags->c) {
				if (flags->f) {
					printf("Fichier inutile '%s", file_path);
					printf("' trouvé%s", flags->v ? "\n\n\n" : "\n");
				} else {
				        printf("Useless file '%s", file_path);
					printf("' found%s", flags->v ? "\n\n\n" : "\n");
				}
			} else {
				if (flags->f) {
					printf("\033[31m\033[1mFichier inutile '");
					display_path(file_path);
					printf("' trouvé%s", flags->v ? "\n\n\n" : "\n");
				} else {
					printf("\033[31m\033[1mUseless file '");
					display_path(file_path);
					printf("' found%s", flags->v ? "\n\n\n" : "\n");
				}
			}
			if (!flags->c)
				printf("\033[0m");
		}
	        if (file->d_name[0] != '.' && is_dir(file_path))
			scan_folder(file_path, flags, mistakes);
		else if(file->d_name[0] != '.')
			scan_file(file_path, flags, mistakes, 0);
		free(file_path);
	}
	closedir(folder);
	delStackTraceEntry();
}

int	is_file_c(char *path)
{
	int	cond = 0;

	addStackTraceEntry("is_file_c", "p", "path", path);
	if (strlen(path) >= 3) {
		cond = path[strlen(path) - 1] == 'c';
		cond = path[strlen(path) - 1] == 'h' || cond;
		cond = path[strlen(path) - 2] == '.' && cond;
	}
	delStackTraceEntry();
	return (cond);
}

void	scan_file(char *path, flag *flags, int *mistakes, int force)
{
	struct stat	info;
	char		answer[3] = "Y\n";

	addStackTraceEntry("scan_file", "pppb", "path", path, "flags", flags, "mistakes", mistakes, "force", force);
	if (stat(path, &info) < 0) {
		if (!flags->c)
		        write(2, "\033[31;1m", 7);
		write(2, "Error : ", 8);
		perror(path);
		if (!flags->c)
			write(2, "\033[0m", 4);
		write(2, "\n", 1);
		delStackTraceEntry();
		return;
	} else if (!is_file_c(path) && !force) {
		delStackTraceEntry();
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
	if (info.st_size >= 1000000) {
		if (!flags->c)
			printf("\033[0m");
		if (flags->f)
			printf("Fichier lourd trouvé (");
		else
			printf("Large file found (");
		if (flags->c)
			printf("%s", path);
		else
			display_path(path);
		printf(") : %s%.4lf%s MB\n", flags->c ? "" : "\033[31;1m", (double)info.st_size / 1000000, flags->c ? "" : "\033[0m");
		if (flags->f)
			printf("Êtes vous sûr de vouloir l'ouvrir ? [Y/n]\n");
		else
			printf("Do you really want to load it ? [Y/n]\n");
		answer[0] = 'a';
		if (flags->no_big_files) {
			answer[0] = 'n';
			printf("n\n");
		} else if (flags->big_files) {
			answer[0] = 'Y';
			printf("Y\n");
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
		if (path[strlen(path) - 1] == 'h')
			scan_h_file(path, mistakes, flags);
		else
			scan_c_file(path, mistakes, key_words, flags);
	} else
		printf("Skipped\n");
	delStackTraceEntry();
}

int	find_bigg(list_t *list)
{
	unsigned int	biggest = 0;

	for (; list->next; list = list->next)
		biggest = biggest < strlen(((b_fcts_t *)list->data)->name) ? strlen(((b_fcts_t *)list->data)->name) : biggest;
	return ((int)biggest);
}

int	find_big(list_t *list)
{
	int	biggest = 0;

	for (; list->next; list = list->next)
		biggest = biggest < get_nbrlen(((b_fcts_t *)list->data)->count) ? get_nbrlen(((b_fcts_t *)list->data)->count) : biggest;
	return ((int)biggest);
}

void	print_list(list_t *list, flag* flags)
{
	int	temp = 0;
	int	tmp = 0;

        addStackTraceEntry("print_list", "p", "list", list);
	temp = find_bigg(list);
	tmp = find_big(list);
        for (; list->next; list = list->next) {
		if (!flags->c) {
			printf("\033[1mUsed ");
			for (int i = (strlen(((b_fcts_t *)list->data)->name) + 1) / 2; i <= temp / 2; i++)
				printf(" ");
			printf("'\033[31m%s\033[0;1m'", ((b_fcts_t *)list->data)->name);
			for (int i = strlen(((b_fcts_t *)list->data)->name) / 2; i <= temp / 2; i++)
				printf(" ");
			printf("\033[31;1m %i", ((b_fcts_t *)list->data)->count);
			for (int i = get_nbrlen(((b_fcts_t *)list->data)->count); i <= tmp; i++)
				printf(" ");
			printf("\033[0;1mtime%s\033[0m\n", ((b_fcts_t *)list->data)->count > 1 ? "s" : "");
		} else {
			printf("Used ");
			for (int i = (strlen(((b_fcts_t *)list->data)->name) + 1) / 2; i <= temp / 2; i++)
				printf(" ");
			printf("'%s'", ((b_fcts_t *)list->data)->name);
			for (int i = strlen(((b_fcts_t *)list->data)->name) / 2; i <= temp / 2; i++)
				printf(" ");
			printf(" %i", ((b_fcts_t *)list->data)->count);
			for (int i = get_nbrlen(((b_fcts_t *)list->data)->count); i <= tmp; i++)
				printf(" ");
			printf("time%s\n", ((b_fcts_t *)list->data)->count > 1 ? "s" : "");
		}
	}
        delStackTraceEntry();
}

void	display_result(int *mistakes, flag *flags)
{
	int	type[3] = {0, 0, 0};
	int	style_mark = 0;

	addStackTraceEntry("display_result", "pp", "mistakes", mistakes, "flags", flags);
	if (flags->d)
		for (int i = 0; coding_style[i].name; i++)
			printf("%s : %i\n", coding_style[i].name, mistakes[i]);
	for (int i = 0; coding_style[i].name; i++)
		if (mistakes[i]) {
			if (flags->c) {
				printf("\n%s", coding_style[i].name);
				printf(" rule has been violated ");
				printf("%i", mistakes[i]);
				printf(" time%s ", mistakes[i] > 1 ? "s" : "");
				printf(": %s", coding_style[i].desc);
			} else {
				printf("\n\033[31;1m%s\033[0m", coding_style[i].name);
				printf("\033[1m rule has been violated \033[0m");
				printf("\033[31;1m%i\033[0m", mistakes[i]);
				printf("\033[1m time%s \033[0m", mistakes[i] > 1 ? "s" : "");
				printf(": \033[91m%s\033[0m", coding_style[i].desc);
			}
			type[coding_style[i].type] += mistakes[i];
		}
	if (type[0] != 0 || type[1] != 0 || type[2] != 0)
		printf("\n\n");
	else if (flags->n)
		printf("\n");
	if (mistakes[FORBIDDEN_FCT_USED] != 0) {
		if (flags->b) {
			printf("\nBanned functions used :\n");
			print_list(flags->b_fcts, flags);
			printf("\n\n");
		} else
			printf("Re-run with -b to see a detailed list of all forbidden functions found.\n\n");
	}
	style_mark = type[0] + type[1] + 5 * type[2];
	if(flags->c) {
		printf("info : ");
		printf("%i  ", type[0]);
		printf("minor : ");
		printf("%i  ", type[1]);
		printf("major : ");
		printf("%i", type[2]);
		if (mistakes[ETIENNE]) {
			printf("  etienne tier : ");
			printf("%i", mistakes[ETIENNE]);
		}
		printf("\nStyle mark : ");
		printf("%i\n", -style_mark);
	} else {
		printf("\033[96minfo\033[0m : ");
		printf("\033[%i;1m%i\033[0m  ", type[0]? 31 : 32, type[0]);
		printf("\033[33mminor\033[0m : ");
		printf("\033[%i;1m%i\033[0m  ", type[1] ? 31 : 32, type[1]);
		printf("\033[31mmajor\033[0m : ");
		printf("\033[%i;1m%i\033[0m", type[2] ? 31 : 32, type[2]);
		if (mistakes[ETIENNE]) {
			printf("  \033[93metienne tier\033[0m : ");
			printf("\033[31;1m%i\033[0m", mistakes[ETIENNE]);
		}
		printf("\033[1m\nStyle mark\033[0m : ");
		printf("\033[%im%i\033[0m\n", style_mark == 0 ? 32 : 31, -style_mark);
	}
	freeStackTrace();
	exit(style_mark != 0);
}
