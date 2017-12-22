/*
** EPITECH PROJECT, 2017
** load_functions
** File description:
** Load authorized functions in memory
*/

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "my.h"
#include "structs.h"
#include "functions.h"

int	char_valid(char c)
{
	if (c <= 'Z' && c >= 'A')
		return (1);
	if (c <= 'z' && c >= 'a')
		return (1);
	if (c <= '9' && c >= '0')
		return (1);
	if (c == '_')
		return (1);
        return (0);
}

char	*get_name(char *file, flag *flags, int *col, char **end_ptr)
{
        int     i = 0;
        int     beg = 0;
        char    *name = 0;

        file++;
        if (*file == '#') {
                if (flags->d)
                        printf("Found #\n\n");
		for (int i = 0; file[i] && file[i] != '\n'; i++)
			*end_ptr = &file[i];
                return (0);
        }
        if (flags->d) {
                printf("Getting function name for line : ");
                for (int j = 0; file[j] && file[j] != '\n'; j++)
                        printf("%c", file[j]);
		printf("\n");
        }
        for (; file[beg] && file[beg] != '(' && file[beg] != ';' && file[beg] != '\n'; beg++) {
                if (flags->d)
                        printf("Skipping %c\n", file[beg]);
		if (file[beg] == '\t')
			*col += 8 - (*col % 8);
		else
			(*col)++;
        }
	if (file[beg] == 0 || file[beg] == ';' || file[beg] == '\n') {
		*end_ptr = &file[beg];
                return (0);
	}
	for (; file[beg + i] && space(file[beg + i]); i--)
		if (file[beg] == '\t')
			*col -= 8 + (*col % 8);
		else
			(*col)--;
	i--;
	if (file[beg] == '\t')
		*col -= 8 + (*col % 8);
	else
		(*col)--;
        for (; file[beg + i] && char_valid(file[beg + i]); i--)
	        (*col)--;
	name = malloc(1 - i);
        sub_strings(file, beg + i + 1, beg, name);
        for (int j = 0; name[j]; j++)
                if (name[j] <= 32)
                        for (int k = j; name[k]; k++)
				name[k] = name[k + 1];
	*end_ptr = &file[beg];
	if (compare_strings(name, ""))
		return (0);
        return (name);
}

int	put_function_names_in_list(char *file, list_t *list, flag *flags)
{
	int	q = 0;
	int	s_q = 0;
	int	cond3 = 0;
	char	*bu = 0;;
	int	comment = 0;
	int	bracket = 0;
	int	ln = 1;
	list_t	*begin = list;
	int	nbr = 0;

	for (int i = 0; file[i]; i++) {
                if (flags->d)
                        printf("[line %i:char %i]:Loop start '%c' (%i)\n", ln, i, file[i] > 31 ? file[i] : 0, file[i]);
		if (file[i] == '\n') {
			ln++;
			comment = comment == 1 ? 0 : comment;
		}
		cond3 = !q && !s_q && comment == 0;
		if (cond3 && bracket == 0 && file[i] == '\n') {
                        if (flags->d)
                                printf("[line %i]:Trying to find function's name\n", ln);
                        bu = get_name(file + i, flags, (int *)&bu, &bu);
                        if (flags->d)
                                printf("Got %p (%s)\n", bu, bu == 0 ? "?" : bu);
                        if (bu != 0) {
				if (flags->d)
					printf("Found %s at line %i\n", bu, ln);
				list->data = bu;
				list->next = malloc(sizeof(*list->next));
				list->next->prev = list;
				list = list->next;
				list->data = 0;
				list->next = 0;
				nbr++;
			}
                } else if (file[i] == '\n' && flags->d){
			printf("Didn't try to find name :\t Base condition : %s\n", cond3 ? "TRUE" : "FALSE");
			printf("\t\t\t\t------->Simple quote : %s\n", s_q ? "TRUE" : "FALSE");
			printf("\t\t\t\t------->Double quote : %s\n", q ? "TRUE" : "FALSE");
			printf("\t\t\t\t------->Comments : %i\n", comment);
			printf("\t\t\t\tBrackets : %i\n", bracket);
		}
                if (cond3 && file[i] == '/' && file[i + 1] == '/') {
                        comment = 1;
                        if (flags->d)
                                printf("[%i]:Start simple comments\n", ln);
                } else if (cond3 && file[i] == '/' && file[i + 1] == '*') {
                        comment += 2;
                        if (flags->d)
                                printf("[%i]:Start of multilines comments\n", ln);
                }
                if (!q && !s_q && !(comment % 2) && file[i] == '*' && file[i + 1] == '/') {
                        comment -= 2;
                        if (flags->d)
                                printf("[%i]:End of multilines comments\n", ln);
	        }
		if (!s_q && !q && file[i] == '{')
                        bracket++;
                if (!s_q && !q && file[i] == '}')
                        bracket--;
	}
	if (flags->d) {
		printf("Functions found in %s\n", "'file'");
		for (list = begin; list->next; list = list->next)
			printf("   -   %s\n", (char *)list->data);
		printf("   -   %s\n", (char *)list->data);
	}
	return (nbr);
}

int	load_function_file(char *path, list_t *list, flag *flags)
{
	char	*file_content;
	int	nbr = 0;

	if (!is_file_c(path))
		return (0);
	file_content = load_file(path);
	if (flags->d) {
		printf("Loading functions in file ");
		display_path(path);
		printf("\n");
	}
	if (file_content)
	        nbr += put_function_names_in_list(file_content, list, flags);
	free(file_content);
	if (flags->d) {
		printf("Functions found in ");
		display_path(path);
		printf("\n");
		for (; list->next; list = list->next)
			printf("   -   %s\n", (char *)list->data);
		printf("   -   %s\n", (char *)list->data);
	}
	return (nbr);
}

int	load_function_folder(char *path, list_t *list, flag *flags)
{
	struct dirent	*file;
        DIR		*folder = opendir(path);
	char		*file_path;
	list_t		*begin = list;
	int		nbr = 0;

	if (!folder) {
		write(2, path, strlen(path));
		perror(" ");
		return (0);
	}
	for (file = readdir(folder); file != 0; file = readdir(folder)) {
		list = begin;
		for (; list->next; list = list->next);
		file_path = find_path(path, file->d_name);
		if (file->d_name[0] != '.' && is_dir(file_path))
			nbr += load_function_folder(file_path, list, flags);
		else if(file->d_name[0] != '.')
			nbr += load_function_file(file_path, list, flags);
		free(file_path);
		if (flags->d) {
			for (list = begin; list->next; list = list->next)
				printf("   -   %s\n", (char *)list->data);
			printf("   -   %s\n", (char *)list->data);
		}
	}
	closedir(folder);
	return (nbr);
}

int	list_len(list_t *list)
{
	int	size = 0;

	for (; list && list->data; list = list->next)
		size++;
	return (size);
}

void	load_functions(char *path, flag *flags)
{
	list_t	*list = 0;

	if (!flags->fcts) {
		flags->fcts = malloc(sizeof(*flags->fcts));
		flags->fcts->next = 0;
		flags->fcts->prev = 0;
		flags->fcts->data = 0;
	}
	list = flags->fcts;
	for (; list->next; list = list->next);
	if (is_dir(path)) {
		if (flags->d)
			printf("Found %i functions\n", load_function_folder(path, list, flags));
		else 
			load_function_folder(path, list, flags);
	} else {
		if (flags->d)
			printf("Found %i functions\n", load_function_file(path, list, flags));
		else
			load_function_file(path, list, flags);
	}
	if (flags->d)
		printf("%i functions are present in the list\n", list_len(flags->fcts));
}
