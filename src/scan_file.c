/*
** EPITECH PROJECT, 2017
** scan_file
** File description:
** Scan a file to detect styles errors
*/

#include <stdlib.h>
#include <stdio.h>
#include <sys/sysmacros.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include "my.h"
#include "structs.h"
#include "functions.h"
#include "stacktrace.h"

char	*load_file(char *path)
{
	int		fd = 0;
	char		*buffer;
	struct stat	info;

	addStackTraceEntry("load_file", "p", "path", path);
	if (stat(path, &info) < 0) {
		perror(path);
		delStackTraceEntry();
		return (0);
	}
	fd = open(path, O_RDONLY);
	if (fd <= 0) {
		perror(path);
		delStackTraceEntry();
		return (0);
	}
	buffer = my_malloc(info.st_size + 1);
	read(fd, buffer, info.st_size);
	buffer[info.st_size] = 0;
	close(fd);
	delStackTraceEntry();
	return (buffer);
}


void	mistake_line(int size, char *line, int col, int ln, flag *flags, int q, int s_q, int comment, int alt)
{
	int	col_c = 0;
	int	chars = 0;
	int	arrow_displayed = 0;
	int	buffer = 0;

	addStackTraceEntry("mistake_line", "ipiipbbi", "size", size, "line", line, "col", col, "ln", ln, "flags", flags, "q", q, "s_q", s_q, "comment", comment, "alt", alt);
	if (alt) {
		if (!flags->c)
			printf("\033[0m\033[32m");
		chars = printf("[%i:%i]", ln, col);
		if (!flags->c)
			printf("\033[93m");
		for (int i = 0; i < 8 - chars % 8 + 7; i++)
			printf("-");
		printf(">");
	}
	if (!flags->c)
		printf("\033[0m");
	for (int i = 0; line[i]; i++) {
		if (buffer > 0)
			buffer--;
		if (line[i] == '\t')
			col_c = (col_c + 8) - (col_c % 8);
		else if (line[i] >= 32)
			col_c++;
	        if (comment == 0 && !q && line[i] == '\'')
			s_q = !s_q;
		else if (comment == 0 && !s_q && line[i] == '"')
			q = !q;
		else if (line[i] == '/' && line[i + 1] == '/' && !q && !s_q && comment == 0)
			comment = 1;
		else if (line[i] == '/' && line[i + 1] == '*' && !q && !s_q && comment == 0)
			comment = 2;
		else if (line[i] == '*' && line[i + 1] == '/' && comment == 2) {
			comment = 0;
			buffer = 2;
		}
		if (!flags->c && ((col_c > col && col_c <= col + size) || !alt))
			printf("\033[95;1m");	
		else if (!flags->c && (buffer > 0 || comment != 0))
			printf("\033[0m\033[31m");
		else if (!flags->c && (q || s_q || line[i] == '"' || line[i] == '\''))
			printf("\033[0m\033[35m");
		else if (!flags->c)
			printf("\033[0m");
		printf("%c", line[i]);
	}
	if (alt) {
		col_c = 0;
		printf("%s\n", !flags->c ? "\033[0m" : "");
		for (int i = 0; i < chars; i++)
			printf(" ");
		printf("\t\t");
		for (int i = 0; line[i]; i++) {
			if (line[i] == '\t') {
				if (col_c >= col && col_c < col + size && !arrow_displayed) {
					arrow_displayed = 1;
					printf("%s^", !flags->c ? "\033[95;1m" : "");
					for (int i = 0; i < 7 - col_c % 8; i++)
						printf("%s~", !flags->c ? "\033[95;1m" : "");
				} else if (col_c >= col && col_c < col + size)
					for (int i = 0; i < 8 - col_c % 8; i++)
						printf("%s~", !flags->c ? "\033[95;1m" : "");
				else 
					printf("%s\t", !flags->c ? "\033[0m" : "");
				col_c = (col_c + 8) - (col_c % 8);
			} else if (line[i] >= 32) {
				if (col_c >= col && col_c < col + size && !arrow_displayed) {
					arrow_displayed = 1;
					printf("%s^", !flags->c ? "\033[95;1m" : "");
				} else if (col_c >= col && col_c < col + size)
					printf("%s~", !flags->c ? "\033[95;1m" : "");
				else
					printf("%s ", !flags->c ? "\033[0m" : "");
				col_c++;
			} else {
				if (col_c >= col && col_c < col + size && !arrow_displayed) {
					arrow_displayed = 1;
					printf("%s^", !flags->c ? "\033[95;1m" : "");
				} else if (col_c >= col && col_c < col + size)
					printf("%s~", !flags->c ? "\033[95;1m" : "");
				else
					printf("%s ", !flags->c ? "\033[0m" : "");
			}
		}
	} else {
		if (!flags->c)
			printf("\033[95;1m");
		printf("^");
		for (int i = 0; i < col - 1; i++)
			printf("~");
		if (!flags->c)
			printf("\033[0m");
		printf("\n");
	}
	printf("\n");
	delStackTraceEntry();
}
void	display_path(char *path)
{
	int	slash = 0;
	int	max_slash = 0;

	addStackTraceEntry("display_path", "p", "path", path);
	for (int i = 0; path[i]; i++)
		if (path[i] == '/')
			max_slash++;
	for (int i = 0; path[i]; i++)
		if (path[i] == '/') {
			printf("\033[0m\033[37m%c", path[i]);
			slash++;
		} else if (slash == max_slash)
			printf("\033[36;1m%c", path[i]);
		else
			printf("\033[34;1m%c", path[i]);
	printf("\033[0m");
	delStackTraceEntry();
}

list_t	*in_list(list_t *list, char *str)
{
	addStackTraceEntry("in_list", "pp", "list", list, "str", str);
	for (; list->next; list = list->next)
		if (compare_strings(str, ((b_fcts_t *)list->data)->name)) {
			delStackTraceEntry();
			return (list);
		}
	delStackTraceEntry();
	return (0);
}

int	is_in_list(list_t *list, char *str)
{
	addStackTraceEntry("is_in_list", "pp", "list", list, "str", str);
	for (; list->next; list = list->next)
		if (compare_strings(str, (char *)list->data)) {
			delStackTraceEntry();
			return (1);
		}
	delStackTraceEntry();
	return (0);
}

int	match(char *str1, char *str2)
{
	addStackTraceEntry("match", "pp", "str1", str1, "str2", str2);
	if (strlen(str1) > strlen(str2)) {
		delStackTraceEntry();
		return (0);
	}
	for (int i = 0; str1[i] && str2[i]; i++)
		if (str1[i] != str2[i]) {
			delStackTraceEntry();
			return (0);
		}
	delStackTraceEntry();
	return (1);
}

void	check_header(char *file, flag *flags, int *mistakes, char *file_name)
{
	int	end = 0;
	int	line = 0;
	int	first_line = 0;
	int	epi_proj = 0;
	int	desc = 0;
	int	oui = 0;
	int	is_valid = 1;
	char	buffer[40];
	char	*buff = 0;
	int	cols = 0;
	int	max_cols = 0;
	int	i = 0;

	addStackTraceEntry("check_header", "pp", "file", file, "flags", flags, "mistakes", mistakes, "file_name", file_name);
	if (match("/*", file))
		first_line = 1;
	strncpy(buffer, file, 2);
	buffer[2] = 0;
	if (flags->d) {
		if (first_line == 1) {
			printf("First line OK\n");
		} else
			printf("Invalid first line : got '%s' expected '/*'\n", buffer);
	}
	for (i = 0; !end && file[i]; i++) {
		if (file[i] == '\n') {
			line++;
			max_cols = cols > max_cols ? cols : max_cols;
			cols = -1;
			if (oui == 0 && match("** EPITECH PROJECT,", &file[i + 1])) {
				oui = 1;
				if (flags->d)
					printf("Found \"** EPITECH PROJECT,\"\n");
			}
			if (oui == 1 && match("** File description:", &file[1 + i])) {
				oui = 2;
				if (flags->d)
					printf("Found \"** File description:\"\n");
			}
			if (oui == 0)
				first_line++;
			else if (oui == 1)
				epi_proj++;
			else
				desc++;
			if (line == 20 || match("*/", &file[i + 1]))
				end = 1;
			if (end == 0 && !match("**", &file[i + 1]))
				is_valid = 0;
		}
		cols++;
	}
	if (!(is_valid && desc > 1 && epi_proj > 1 && first_line == 1)) {
		if (flags->d) {
			printf("Header info :\n\tis_valid : %i", is_valid);
			printf("\n\tdesc : %i", desc);
			printf("\n\tepi_proj : %i", epi_proj);
			printf("\n\tfirst_line : %i\n", first_line);
		}
		if (flags->c)
			printf("%s", file_name);
	        else
			display_path(file_name);
		if (flags->f)
			printf(": Header invalide\n");
		else
			printf(": Invalid header\n");
		mistakes[INVALID_HEADER]++;
		if (flags->v) {
			if (first_line != 1) {
				for (i = 0; file[i] != '\n' && file[i]; i++);
				buff = sub_strings(file, 0, i + 1, my_malloc(i + 2));
				max_cols = i;
			} else
				buff = sub_strings(file, 0, i + 3, my_malloc(i + 4));
			mistake_line(i, buff, max_cols, 0, flags, 0, 0, 0, 0);
			free(buff);
		}
	}
	delStackTraceEntry();
}

int	is_in_array(char const **array, char *str)
{
	addStackTraceEntry("is_in_array", "pp", "array", array, "str", str);
	for (int i = 0; array[i]; i++)
		if (compare_strings(str, array[i])) {
			delStackTraceEntry();
			return (1);
		}
	delStackTraceEntry();
	return (0);
}

int	whitelisted(char *fct)
{
	addStackTraceEntry("whitelisted", "p", "fct", fct);
        if (compare_strings(fct, "sizeof")) {
		delStackTraceEntry();
		return (1);
	} else if (compare_strings(fct, "")) {
		delStackTraceEntry();
		return (1);
	}
	delStackTraceEntry();
	return (0);
}

void	verif_fct_used(char *name, flag *flags, char *file_name, int *mistakes, char const **words, char *fct, int ln, char *fct_name, int col, char *file)
{
	char	*buffer;
	int	end = 0;
	list_t	*list = flags->b_fcts;

	addStackTraceEntry("verif_fct_used", "ppppppipip", "name", name, "flags", flags, "file_name", file_name, "mistakes", mistakes, \
			   "words", words, "fct", fct, "ln", ln, "fct_name", fct_name, "col", col, "file", file);
	if (!is_in_list(flags->fcts, name) && !is_in_array(words, name) && !whitelisted(name)) {
		mistakes[FORBIDDEN_FCT_USED]++;
		if (flags->c) {
			printf("%s [%i:%i]", file_name, ln, col);
			printf(" %s%s%s",  fct_name ? fct : "", fct_name ? fct_name : "", fct_name ? "'" : "");
			if (flags->f)
				printf(": fonction interdite utilisée (%s)\n", name);
			else
				printf(": forbidden function used (%s)\n", name);
		} else {
			display_path(file_name);
			printf(" [\033[32;1m%i\033[0m:\033[32;1m%i\033[0m]", ln, col);
			printf(" \033[0m%s\033[31;1m%s\033[0m%s",  fct_name ? fct : "", fct_name ? fct_name : "", fct_name ? "'" : "");
			if (flags->f)
				printf(": fonction interdite utilisée (\033[31;1m%s\033[0m)\n", name);
			else
				printf(": forbidden function used (\033[31;1m%s\033[0m)\n", name);
		}
		if (flags->b) {
			for (; list->next; list = list->next);
			if (in_list(flags->b_fcts, name) == 0) {
				list->next = my_malloc(sizeof(*list->next));
				list->data = my_malloc(sizeof(b_fcts_t));
				((b_fcts_t *)list->data)->name = strdup(name);
				((b_fcts_t *)list->data)->count = 0;
				list->next->next = 0;
				list->next->data = 0;
				list->next->prev = list;
			}
			list = in_list(flags->b_fcts, name);
			((b_fcts_t *)list->data)->count++;
		}
		if (flags->v) {
			for (; file[end] && file[end] != '\n'; end++);
			buffer = my_malloc(end + 2);
			sub_strings(file, 0, end, buffer);
			mistake_line(strlen(name), buffer, col - strlen(name), ln, flags, 0, 0, 0, 1);
			free(buffer);
		}
	}
	delStackTraceEntry();
}

void	check_ind(char *file, int *mistakes, char *path, int ln, int i, flag *flags, char *fct_name, char *fct, int q, int s_q, int comment)
{
	int	col = 0;
	int	c = 0;
	char	*bu = 0;
	int	spaces = 0;
	int	backslash_t = 0;

	addStackTraceEntry("check_ind", "pppiipppbbi", "file", file, "mistakes", mistakes, "path", path, "ln", ln, "i", i, \
			   "flags", flags, "fct_name", fct_name, "fct", fct, "q", q, "s_q", s_q, "comment", comment);
	if (flags->d)
		printf("[%i]:Checking ind\n", col);
        for (int jl = i + 1; jl != -1 && file[jl]; jl++) {
		if (flags->d)
			printf("[%i]:Loop start '%c' (%i)\n", col, file[jl] > 31 ? file[jl] : 0, file[jl]);
		if (file[jl] == ' ') {
			if (flags->d)
				printf("[%i]:Found a space\n", col);
			mistakes[BAD_INDENTATION]++;
			if (flags->c) {
				printf("%s [%i:%i]", path, ln, col + 1);
				printf(" %s%s%s",  fct_name ? fct : "", fct_name ? fct_name : "", fct_name ? "'" : "");
				if (flags->f)
					printf(": erreur d'indentation\n");
				else
					printf(": bad indentation\n");
			} else {
				display_path(path);
				printf(" [\033[32;1m%i\033[0m:\033[32;1m%i\033[0m]", ln, col + 1);
				printf(" \033[0m%s\033[31;1m%s\033[0m%s",  fct_name ? fct : "", fct_name ? fct_name : "", fct_name ? "'" : "");
				if (flags->f)
					printf("\033[0m: erreur d'indentation\n");
				else
					printf("\033[0m: bad indentation\n");
			}
			for (c = i + 1; file[c] != '\n' && file[c]; c++);
			if (flags->v) {
				bu = my_malloc(c - i + 2);
				sub_strings(file, i + 1, c, bu);
				for (spaces = 0; file[jl + spaces] == ' '; spaces++);
				mistake_line(spaces, bu, col, ln, flags, q, s_q, comment, 1);
				free(bu);
			}
			jl = -2;
		} else if (file[jl] == '\t') {
			backslash_t++;
			if (flags->d)
				printf("[%i]:New \\t\n", col);
		} else if (file[jl] == '\n' && backslash_t > 0) {
			if (flags->d)
				printf("[%i]:Found end of line !\n", col);
			mistakes[BAD_INDENTATION]++;
			if (flags->c){
				printf("%s [%i:%i]", path, ln, col + 1);
				printf(" %s%s%s",  fct_name ? fct : "", fct_name ? fct_name : "", fct_name ? "'" : "");
				if (flags->f)
					printf(": erreur d'indentation (ligne vide)\n");
				else
					printf(": bad indentation (empty line)\n");
			} else {
				display_path(path);
				printf(" [\033[32;1m%i\033[0m:\033[32;1m%i\033[0m]", ln, col + 1);
				printf(" \033[0m%s\033[31;1m%s\033[0m%s",  fct_name ? fct : "", fct_name ? fct_name : "", fct_name ? "'" : "");
				if (flags->f)
					printf("\033[0m: erreur d'indentation (ligne vide)\n");
				else
					printf("\033[0m: bad indentation (empty line)\n");
			}
			if (flags->v) {
				bu = my_malloc(i + 1);
				sub_strings(file, i + 1, i - jl, bu);
			        mistake_line((jl - i - 1) * 8, bu, 0, ln, flags, 0, 0, 0, 1);
				free(bu);
			}
			jl = -2;
		} else if(file[jl] != '\t') {
			if (flags->d)
				printf("[%i]:Found a character\n", col);
			jl = -2;
		}
		col += 8;
	}
	delStackTraceEntry();
}

int	space(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

char	*get_function_name(char *file, flag *flags, int *mistakes, int ln, char *path)
{
	int	i = -1;
	int	beg = 0;
	char	*name = 0;
	int	end = 0;
	int	args_nbr = 1;
	char	*void_ = "void";
	int	col = 0;
	int     cond = 0;

	addStackTraceEntry("get_function_name", "pppip", "file", file, "flags", flags, "mistakes", mistakes, "ln", ln, "path", path);
	file++;
	if (*file == '#') {
		if (flags->d)
			printf("Found #\n\n");
		delStackTraceEntry();
		return (0);
	}
	if (flags->d) {
		printf("Getting function name for line : '");
		for (int j = 0; file[j] && file[j] != '\n'; j++)
			printf("%c", file[j]);
		printf("'\n");
	}
	for (; file[beg] && file[beg] != '(' && file[beg] != ';' && file[beg] != '\n'; beg++) {
		if (file[beg] == '\t')
			col += 8 - col % 8;
		else if (file[beg] >= 32 || (unsigned char)file[beg] == 195)
			col++;
		if (flags->d)
			printf("Skipping %c\n", file[beg]);
	}
	if (file[beg] == ';' || file[beg] == '\n') {
		delStackTraceEntry();
		return (0);
	}
	for (; file[beg + i] && char_valid(file[beg + i]); i--) {
		if (file[beg + i] == '\t')
			col -= 8 + col % 8;
		else if (file[beg + i] >= 32 || (unsigned char)file[beg + i] == 195)
			col--;
	}
	for (int j = 0; file[beg + j] && file[beg + j] != ')'; j++)
		if (file[beg + j] == ',')
			args_nbr++;
	if (file[beg] && file[beg + 1] == ')')
		args_nbr = 0;
	name = my_malloc(1 - i);
	sub_strings(file, beg + i + 1, beg, name);
	for (int j = 0; name[j]; j++)
		if (name[j] <= 32)
			for (int k = j; name[k]; k++)
				name[k] = name[k + 1];
	if (args_nbr == 0) {
	        if (flags->c) {
			printf("%s [%i:%i]", path, ln, col);
			printf("%s%s'",  flags->f ? " dans la fonction '" : " in function '", name);
			if (flags->f) {
				printf(": 'void' attendu pour une fonction");
				printf(" ne prenant aucun argument\n");
			} else {
				printf(": 'void' expected ");
				printf("for a function that takes no argument\n");
			}
		} else {
			display_path(path);
			printf(" [\033[32;1m%i\033[0m:\033[32;1m%i\033[0m]", ln, col);
			printf("\033[1m%s\033[31;1m%s\033[0m'",  flags->f ? " dans la fonction '" : " in function '", name);
			if (flags->f) {
				printf("\033[0m: 'void' attendu pour une fonction");
				printf(" ne prenant aucun argument\n");
			} else {
				printf("\033[0m: 'void' expected ");
				printf("for a function that takes no argument\n");
			}
		}
		for (end = 0; file[end] != '\n' && file[end]; end++);
		if (flags->v) {
			void_ = my_malloc(end + 10);
			sub_strings(file, 0, end, void_);
			mistake_line(strlen(name), void_, col, ln, flags, 0, 0, 0, 1);
			free(void_);
		}
		mistakes[TOO_MANY_ARGS]++;
	} else if (args_nbr > 4) {
		if (flags->c) {
			printf("%s [%i:%i]", path, ln, col + 1);
			if (flags->f) {
				printf(": trop d'arguments pour la fonction '%s'", name);
				printf(" (4 maximum mais %i trouvés)\n", args_nbr);
			} else {
				printf(": too many arguments for function '%s'", name);
				printf(" (4 max but %i found)\n", args_nbr);
			}
		} else {
			display_path(path);
			printf(" [\033[32;1m%i\033[0m:\033[32;1m%i\033[0m]", ln, col + 1);
			if (flags->f) {
				printf(": trop d'arguments pour la fonction '\033[31;1m%s\033[0m'", name);
				printf(" (4 maximum mais \033[31;1m%i\033[0m trouvés)\n", args_nbr);
			} else {
				printf(": too many arguments for function '\033[31;1m%s\033[0m'", name);
				printf(" (4 max but \033[31;1m%i\033[0m found)\n", args_nbr);
			}
		}
		for (end = 0; file[end] != '\n' && file[end]; end++);
		if (flags->v) {
			void_ = my_malloc(end + 10);
			sub_strings(file, 0, end, void_);
			mistake_line(strlen(name), void_, col, ln, flags, 0, 0, 0, 1);
			free(void_);
		}
		mistakes[TOO_MANY_ARGS]++;
	}
        for (int i = 0; name[i]; i++) {
                cond = name[i] == '_' || name[i] == '.';
		cond = cond || (name[i] >= '0' && name[i] <= '9');
		if (compare_strings("Test", name))
			break;
                if (!((name[i] >= 'a' && name[i] <= 'z') || cond)) {
                        mistakes[24]++;
			if (flags->c)
				printf("%s [%i:%i] ", path, col, ln);
			else {
				display_path(path);
				printf(" [\033[32;1m%i\033[0m:\033[32;1m%i\033[0m]", col, ln);
			}
			if (flags->c) {
				if (flags->f)
					printf(" dans la fonction '%s': Nom invalide\n", name);
				else
					printf(" in function '%s': Invalid name\n", name);
			} else {
				if (flags->f)
					printf(" \033[1mdans la fonction\033[0m '\033[31;1m%s\033[0m': Nom invalide\n", name);
				else
					printf(" \033[1min function\033[0m '\033[31;1m%s\033[0m': Invalid name\n", name);
			}
			for (end = 0; file[end] != '\n' && file[end]; end++);
			if (flags->v) {
				void_ = my_malloc(end + 10);
				sub_strings(file, 0, end, void_);
				mistake_line(strlen(name), void_, col, ln, flags, 0, 0, 0, 1);
				free(void_);
			}
			break;
                }
        }
	if (flags->d)
		printf("Found %i arguments for function %s\n\n", args_nbr, name);
	if (compare_strings(name, "")) {
		free(name);
		delStackTraceEntry();
		return (0);
	}
	delStackTraceEntry();
	return (name);
}

int	nobackslash(char *file)
{
	int	i = 0;

	for (; space(file[i]); i++);
	return (file[i] != '\\');
}

void	verif_bracket_pos(char *file, int pos, char const **words, int *mistakes, flag *flags, int ln, int col, char **fct_name, char *fct, char *path)
{
	int	i = pos;
	int	j = pos;
	char	*buffer = 0;
	int	lines = 0;
	int	start = 0;
	int	end = 0;
	char	*bu = 0;
	int	par = 0;

	addStackTraceEntry("find_long_fct", "pipppiipp", "file", file, "pos", pos, "mistakes", mistakes, "words", words,
			   "flags", flags, "ln", ln, "col", col, "fct_name", fct_name, "fct", fct, "path", path);
	for (i--; i > 0 && (space(file[i]) || file[i] == '\\'); i--)
		lines += file[i] == '\n';
	if (file[i] != ')') {
		delStackTraceEntry();
		return;
	}
	for (i--; i > 0 && (par > 0 || file[i] != '('); i--)
		par += (file[i] == ')') - (file[i] == '(');
	if (file[i] != '(') {
		delStackTraceEntry();
		return;
	}
	for (i--; i > 0 && space(file[i]); i--);
	if (space(file[i])) {
		delStackTraceEntry();
		return;
	}
	j = i;
	for (; i > 0 && char_valid(file[i]); i--);
	buffer = sub_strings(file, i + (i > 0), j + 1, my_malloc(j - i + 2));
	if (((is_in_array(words, buffer) && lines != 0) || (lines != 1 && !is_in_array(words, buffer))) && !compare_strings("", buffer)) {
		mistakes[BRACKET_MISPLACED]++;
		if (flags->c) {
			printf("%s [%i:%i]", path, ln, col);
			printf(" %s%s%s",  *fct_name ? fct : "", *fct_name ? *fct_name : "", *fct_name ? "'" : "");
			if (flags->f)
				printf(": Accolade mal placée après '%s'\n", buffer);
			else
				printf(": Bracket misplaced after '%s'\n", buffer);
		} else {
			display_path(path);
			printf(" [\033[32;1m%i\033[0m:\033[32;1m%i\033[0m]", ln, col);
			printf(" \033[0m%s\033[31;1m%s\033[0m%s", *fct_name ? fct : "", *fct_name ? *fct_name : "", *fct_name ? "'" : "");
			if (flags->f)
				printf(": Accolade mal placée après '\033[31;1m%s\033[0m'\n", buffer);
			else
				printf(": Bracket misplaced after '\033[31;1m%s\033[0m'\n", buffer);
		}
		for (start = pos; start > 0 && file[start] != '\n'; start--);
		for (end = pos; file[end] != '\n' && file[end]; end++);
		if (flags->v) {
			bu = my_malloc(end - start + 10);
			sub_strings(file, start + 1, end, bu);
			mistake_line(1, bu, col, ln, flags, 0, 0, 0, 1);
			free(bu);
		}
	}
	if (!is_in_array(words, buffer) && !compare_strings("", buffer)) {
		free(*fct_name);
		*fct_name = buffer;
	} else
		free(buffer);
	delStackTraceEntry();
}

int	get_indent_expected(char *file, int bracket, list_t *expected_indentlvl, int comment)
{
	int	level = bracket;
	int	s_q = 0;
	int	q = 0;
	int	i = 1;

	addStackTraceEntry("get_indent_expected", "pipi", "file", file, "bracket", bracket, "expected_indentlvl", expected_indentlvl, "comment", comment);
	if (get_flags_var()->d)
		printf("Bracket level : %i\n", level);
	for (; expected_indentlvl && expected_indentlvl->prev; expected_indentlvl = expected_indentlvl->prev);
	for (; expected_indentlvl && expected_indentlvl->next; expected_indentlvl = expected_indentlvl->next)
		level++;
	if (get_flags_var()->d)
		printf("List size : %i\n", -bracket + level);
	for (; file[i] && file[i] != '\n'; i++) {
		if (!s_q && comment == 0 && file[i] == '"')
			q = !q;
		if (!q && comment == 0 && file[i] == '\'')
			s_q = !s_q;
		if (!q && !s_q && file[i] == '/' && file[i + 1] == '/')
			comment = 1;
		if (!q && !s_q && file[i] == '/' && file[i + 1] == '*')
			comment = 2;
		if (!q && !s_q && file[i] == '*' && file[i + 1] == '/' && comment == 2)
			comment = 0;
	}
	if (file[i - 1] == ':' && !q && !s_q && comment == 0) {
		level--;
		if (get_flags_var()->d)
			printf("Found ':' : %i\n", level);
	}
	delStackTraceEntry();
	return (level);
}

int	need_to_indent(char *file, int comment)
{
	int	parenthesis = 0;
	int	found_it = 0;
	int	s_q = 0;
	int	q = 0;
	int	i = 0;

	addStackTraceEntry("need_to_indent", "pi", "file", file, "comment", comment);
	for (; file[i] && !space(file[i]) && file[i] != ')' && file[i] != ';' && file[i] != '(' && file[i] != ']' && file[i] != '['; i++);
	if (file[i] == ')' || file[i] == ';' || file[i] == ']' || file[i] == '[') {
		
		delStackTraceEntry();
		return (0);
	}
	for (; file[i] && space(file[i]); i++);
	for (; file[i] && (parenthesis || !found_it) && (parenthesis || file[i] != '{'); i++) {
		found_it = 1;
		parenthesis += ((file[i] == '(') - (file[i] == ')')) * (!s_q && !q && comment == 0);
		if (!s_q && comment == 0 && file[i] == '"' && (i == 0 || (file[i - 1] != '\\' && (i <= 1 || file[i - 2] == '\\'))))
			q = !q;
		if (!q && comment == 0 && file[i] == '\'' && (i == 0 || (file[i - 1] != '\\' || (i <= 1 || file[i - 2] == '\\'))))
			s_q = !s_q;
		if (!q && !s_q && file[i] == '/' && file[i + 1] == '/')
			comment = 1;
		if (!q && !s_q && file[i] == '/' && file[i + 1] == '*')
			comment = 2;
		if (!q && !s_q && file[i] == '*' && file[i + 1] == '/' && comment == 2)
			comment = 0;
		if (file[i] == '\n' && comment == 1)
			comment = 0;
	}
	for (; file[i] && space(file[i]); i++);
	if (get_flags_var()->d) {
		printf("Char : '%c'\n", file[i]);
		printf("Stopped loop because ");
		if (!file[i])
			printf("reached end of buffer\n");
		if (!(parenthesis || !found_it))
			printf("went out of parenthesis\n");
		if (file[i] == '{')
			printf("found a openned bracket\n");
		printf("Need to indent : %s\n", file[i] && file[i] != ';' && file[i] != '{' ? "TRUE" : "FALSE");
	}
	delStackTraceEntry();
	return (file[i] && file[i] != ';' && file[i] != '{');
}

float	get_indent_lvl(char *file)
{
	float	level = 0;
	int	i = 0;

	addStackTraceEntry("get_indent_lvl", "p", "file", file);
	for (; file[i] == ' ' || file[i] == '\t'; i++) {
	        if (file[i] == '\t')
			level = (int)(level + 1);
		if (file[i] == ' ')
			level += 1.0 / 8.0;
	}
	if (file[i] == '\n') {
		delStackTraceEntry();
		return (-1);
	}
	delStackTraceEntry();
	return (level);
}

void	find_long_fct(char *file, int *mistakes, char *path, char const **words, flag *flags)
{
	int	q = 0;
	int	s_q = 0;
	int	function = 0;
	int	line = 0;
	int	ln = 1;
	int	bracket = 0;
	int	col = 1;
	char	buffer[7] = {0, 0, 0, 0, 0, 0, 0};
	char	*bu;
	char	*fct_name = 0;
	char	*fct = flags->f ? (flags->c ? "dans la fonction '" : "\033[1mdans la fonction '") : (flags->c ? "in function '" : "\033[1min function '");
        int	cond = 0;
	int	cond2 = 0;
	int	act = 0;
	int	cond3 = 0;
	int	start = 0;
	int	end = 0;
	int	comment = 0;
	int	begin_of_line = 1;
	int	declaring_var = 0;
	char	*ptr = file;
	int	l_o = 0;
	int	fine = 0;
	int	parenthesis = 0;
	int	indentBuffer = 0;
	list_t	*expected_indentlvl = my_malloc(sizeof(*expected_indentlvl));
	float	current_indent_lvl = 0;

	memset(expected_indentlvl, 0, sizeof(*expected_indentlvl));
	addStackTraceEntry("find_long_fct", "ppppp", "file", file, "mistakes", mistakes, "path", path, "words", words, "flags", flags);
	if (flags->d)
		printf("Beggining of buffer\n");
	for (int i = 0 ; file[i] ; i++) {
		cond3 = !q && !s_q && comment == 0;
		indentBuffer = 0;
		if (flags->d) {
			printf("[%i, %i]:Loop start '%c' (%i)\n", ln, col, file[i] > 31 ? file[i] : 0, file[i]);
			printf("Global conditions :\tcond3        : %s\n", cond3 ? "TRUE" : "FALSE");
			printf("\t\t\ts_quote      : %s\n", q ? "TRUE" : "FALSE");
			printf("\t\t\td_quote      : %s\n", s_q ? "TRUE" : "FALSE");
			printf("\t\t\tcomment      : %i\n", comment);
			printf("\t\t\tbracket      : %i\n", bracket);
			printf("\t\t\tparenthesis  : %i\n", parenthesis);
			printf("\t\t\tindent lvl   : %f\n", current_indent_lvl);
			printf("\t\t\texpected ind : %i\n", get_indent_expected(&file[i], bracket, expected_indentlvl, comment));
		}
		if (cond3 && file[i] == '(')
			parenthesis++;
		if (cond3 && file[i] == ')')
			parenthesis--;
		if (cond3 && bracket == 0 && file[i] == '\n') {
			if (flags->d)
				printf("[%i, %i]:Trying to find function's name\n", ln, col);
			bu = get_function_name(file + i, flags, mistakes, ln + 1, path);
			if (flags->d)
				printf("Got %p (%s)\n", bu, bu == 0 ? "?" : bu);
			if (bu != 0) {
				free(fct_name);
				fct_name = bu;
			}
		}
		if (cond3 && file[i] == '\n' && flags->i_caps) {
		        ptr = &file[i + 1];
			while (*ptr && *ptr != '\n') {
				if (flags->d)
					printf("[%i, %i]:Trying to find used function name\n", ln, col);
				bu = get_name(ptr, flags, &col, &ptr);
				if (flags->d)
					printf("Got %p (%s)\n", bu, bu == 0 ? "?" : bu);
				if (bu != 0) {
					col = 0;
					for (char *tmp = &file[i + 1]; tmp < ptr; tmp++) {
						if (*tmp == '\t')
							col += 8 - (col % 8);
						else if (*tmp >= 32 || (unsigned char)*tmp == 195)
							col++;
					}
					verif_fct_used(bu, flags, path, mistakes, words, fct, ln, fct_name, col, &file[i + 1]);
					free(bu);
				}
			}
			col = 0;
		}
		if (cond3 && l_o != -1 && (file[i] == 'o' || file[i] == 'l'))
			l_o++;
		else if (char_valid(file[i]))
			l_o = -1;
		else {
			if (cond3 && l_o != -1 && l_o != 0) {
				if (flags->c) {
					printf("%s [%i:%i]", path, ln, col - l_o);
					printf(" %s%s%s",  fct_name ? fct : "", fct_name ? fct_name : "", fct_name ? "'" : "");
					if (flags->f) {
						printf(": identifieur seulement ");
						printf("composé de 'l' et de 'o'\n");
					} else {
						printf(": identifier only ");
						printf("composed of 'l' and 'o'\n");
					}
				} else {
					display_path(path);
					printf(" [\033[32;1m%i\033[0m:\033[32;1m%i\033[0m]", ln, col - l_o);
					printf(" \033[0m%s\033[31;1m%s\033[0m%s",  fct_name ? fct : "", fct_name ? fct_name : "", fct_name ? "'" : "");
					if (flags->f) {
						printf(": identifieur seulement composé de ");
						printf("'\033[31;1ml\033[0m' and '\033[31;1mo\033[0m'\n");
					} else {
						printf(": identifier only composed of ");
						printf("'\033[31;1ml\033[0m' and '\033[31;1mo\033[0m'\n");
					}
				}
				for (start = i; start > 0 && file[start] != '\n'; start--);
				for (end = start + 1; file[end] != '\n' && file[end]; end++);
				if (flags->v) {
					bu = my_malloc(end - start + 10);
					sub_strings(file, start + 1, end, bu);
					mistake_line(l_o, bu, col - l_o, ln, flags, q, s_q, comment, 1);
					free(bu);
				}
				mistakes[IDENTIFIER_L_O]++;
			}
			l_o = 0;
		}
		if (cond3 && file[i] == '/' && file[i + 1] == '/') {
			comment = 1;
			if (flags->d)
				printf("[%i, %i]:Start simple comments\n", ln, col);
		} else if (cond3 && file[i] == '/' && file[i + 1] == '*') {
			comment = 2;
			if (flags->d)
				printf("[%i, %i]:Start of multilines comments\n", ln, col);
		}
		if (!q && !s_q && comment == 2 && file[i] == '*' && file[i + 1] == '/') {
			comment = 0;
			if (flags->d)
				printf("[%i, %i]:End of multilines comments\n", ln, col);
		}
		sub_strings(file, i, i + 4, buffer);
		if (cond3 && compare_strings(buffer, "goto")) {
			if (flags->c) {
				printf("%s [%i:%i]", path, ln, col + 1);
				printf(" %s%s%s",  fct_name ? fct : "", fct_name ? fct_name : "", fct_name ? "'" : "");
				if (flags->f)
					printf(": Utilisation de goto interdit\n");
				else
					printf(": The use of goto is forbidden\n");
			} else {
				display_path(path);
				printf(" [\033[32;1m%i\033[0m:\033[32;1m%i\033[0m]", ln, col + 1);
				printf(" \033[0m%s\033[31;1m%s\033[0m%s",  fct_name ? fct : "", fct_name ? fct_name : "", fct_name ? "'" : "");
				if (flags->f)
					printf("\033[0m: Utilisation de goto interdit\n");
				else
					printf("\033[0m: The use of goto is forbidden\n");
			}
			for (start = i; file[start] != '\n'; start--);
			for (end = start + 1; file[end] != '\n' && file[end]; end++);
			if (flags->v) {
				bu = my_malloc(end - start + 10);
				sub_strings(file, start + 1, end, bu);
				mistake_line(4, bu, col, ln, flags, q, s_q, comment, 1);
				free(bu);
			}
			mistakes[GOTO_USED]++;
		
		}
		if (file[i] == ';' && parenthesis == 0)
			act++;
		if (bracket == 1 && parenthesis == 0 && act >= 5 && file[i] == ';' && cond3) {
			if (flags->c) {
				printf("%s [%i:%i]", path, ln, col + 1);
				printf(" %s%s%s",  fct_name ? fct : "", fct_name ? fct_name : "", fct_name ? "'" : "");
		        } else {
				display_path(path);
				printf(" [\033[32;1m%i\033[0m:\033[32;1m%i\033[0m]", ln, col + 1);
				printf(" \033[0m%s\033[31;1m%s\033[0m%s\033[0m",  fct_name ? fct : "", fct_name ? fct_name : "", fct_name ? "'" : "");
			}
			printf(": Alors, tu vas rire, mas ça c'est pas à la norme\n");
			for (start = i; start > 0 && file[start] != '\n'; start--);
			for (end = start + 1; file[end] != '\n' && file[end]; end++);
			bu = my_malloc(end - start + 10);
			sub_strings(file, start + 1, end, bu);
			mistake_line(1, bu, col, ln, flags, q, s_q, comment, 1);
			free(bu);
			mistakes[ETIENNE]++;
			mistakes[MORE_THAN_ONE_ACT_BY_LINE]++;
		} else if (bracket == 1 && parenthesis == 0 && act > 1 && file[i] == ';' && cond3) {
			if (flags->c) {
				printf("%s [%i:%i]", path, ln, col + 1);
				printf(" %s%s%s",  fct_name ? fct : "", fct_name ? fct_name : "", fct_name ? "'" : "");
				if (flags->f) {
					printf(": Plus d'une action par ligne\n");
				} else
					printf(": A line corresponds to more than one statement\n");
			} else {
				display_path(path);
				printf(" [\033[32;1m%i\033[0m:\033[32;1m%i\033[0m]", ln, col + 1);
				printf(" \033[0m%s\033[31;1m%s\033[0m%s",  fct_name ? fct : "", fct_name ? fct_name : "", fct_name ? "'" : "");
				if (flags->f) {
					printf("\033[0m: Plus d'une action par ligne\n");
				} else
					printf("\033[0m: A line corresponds to more than one statement\n");
			}
			for (start = i; start > 0 && file[start] != '\n'; start--);
			for (end = start + 1; file[end] != '\n' && file[end]; end++);
			if (flags->v) {
				bu = my_malloc(end - start + 10);
				sub_strings(file, start + 1, end, bu);
				mistake_line(1, bu, col, ln, flags, q, s_q, comment, 1);
				free(bu);
			}
			mistakes[MORE_THAN_ONE_ACT_BY_LINE]++;
		}
/*		if (bracket == 1 && parenthesis == 0 && file[i] == ',' && cond3) {
			
		}
*/		if (cond3 && file[i] == ',' && !space(file[i + 1])) {
			if (flags->c) {
				printf("%s [%i:%i]", path, ln, col + 1);
				printf(" %s%s%s",  fct_name ? fct : "", fct_name ? fct_name : "", fct_name ? "'" : "");
				if (flags->f) {
					printf(": espace manquant ");
					printf("après une virgule\n");
				} else {
					printf(": space missing after ");
					printf("a comma\n");
				}
			} else {
				display_path(path);
				printf(" [\033[32;1m%i\033[0m:\033[32;1m%i\033[0m]", ln, col + 1);
				printf(" \033[0m%s\033[31;1m%s\033[0m%s",  fct_name ? fct : "", fct_name ? fct_name : "", fct_name ? "'" : "");
				if (flags->f) {
					printf("\033[0m: espace manquant ");
					printf("après une virgule\n");
				} else {
					printf("\033[0m: space missing after ");
					printf("a comma\n");
				}
			}
			for (start = i; start > 0 && file[start] != '\n'; start--);
			for (end = start + 1; file[end] != '\n' && file[end]; end++);
			if (flags->v) {
				bu = my_malloc(end - start + 10);
				sub_strings(file, start + 1, end, bu);
				mistake_line(1, bu, col, ln, flags, q, s_q, comment, 1);
				free(bu);
			}
			mistakes[SPACE_MISSING]++;
		}
		for (int k = 0; words[k] && cond3; k++) {
			sub_strings(file, i, i + strlen(words[k]), buffer);
			cond = (i + strlen(words[k])) < strlen(file);
		        cond = cond && file[i + strlen(words[k])] == '(';
			if (flags->d) {
				printf("[%i, %i]:Searching for '%s' ", ln, col, words[k]);
				printf("and got '");
				my_showstr(buffer);
				printf("' with");
				printf("%s after", !cond ? "out any '('" : " a '('");
			}
		        cond2 = i > 0 && file[i - 1] == '\n';
			cond2 = i > 0 && (cond2 || file[i - 1] == '\t');
			cond2 = i > 0 && (cond2 || file[i - 1] == ' ');
			if (flags->d) {
				printf(" and with");
				printf("%s before\n", cond ? "out any spaces" : " a space");
			}
		        if (compare_strings(buffer, "else")) {
				for (fine = i + 4; file[fine] && space(file[fine]); fine++);
				if (flags->d)
					printf("After else : %c\n", file[fine]);
				if (match("if", &file[fine]))
					break;
			}
			if (compare_strings(buffer, words[k]) && need_to_indent(&file[i], comment)) {
				expected_indentlvl->next = my_malloc(sizeof(*expected_indentlvl->next));
				expected_indentlvl->next->prev = expected_indentlvl;
				expected_indentlvl->next->next = 0;
				expected_indentlvl = expected_indentlvl->next;
				expected_indentlvl->data = my_malloc(sizeof(int));
				*(int *)expected_indentlvl->data = bracket;
			        if (flags->d)
					printf("[%i:%i]:Added list entry ! (%i)\n", ln, col, *(int *)expected_indentlvl->data);
			}
			cond = cond && cond2;
			if(compare_strings(buffer, words[k]) && cond) {
				if (flags->c) {
					printf("%s [%i:%i]", path, ln, col + 1);
					printf(" %s%s%s",  fct_name ? fct : "", fct_name ? fct_name : "", fct_name ? "'" : "");
					if (flags->f) {
						printf(": espace manquant ");
						printf("après le mot clé '%s'\n", words[k]);
					} else {
						printf(": space missing after ");
						printf("key word '%s'\n", words[k]);
					}
				} else {
					display_path(path);
					printf(" [\033[32;1m%i\033[0m:\033[32;1m%i\033[0m]", ln, col + 1);
					printf(" \033[0m%s\033[31;1m%s\033[0m%s",  fct_name ? fct : "", fct_name ? fct_name : "", fct_name ? "'" : "");
					if (flags->f) {
						printf("\033[0m: espace manquant ");
						printf("après le mot clé '\033[31;1m%s\033[0m'\n", words[k]);
					} else {
						printf("\033[0m: space missing after ");
						printf("key word '\033[31;1m%s\033[0m'\n", words[k]);
					}
				}
				for (start = i; file[start] != '\n'; start--);
				for (end = start + 1; file[end] != '\n' && file[end]; end++);
				if (flags->v) {
					bu = my_malloc(end - start + 10);
					sub_strings(file, start + 1, end, bu);
					mistake_line(strlen(words[k]), bu, col, ln, flags, q, s_q, comment, 1);
					free(bu);
				}
				mistakes[SPACE_MISSING]++;
			}
			if (compare_strings(words[k], buffer))
				break;
		}
		if ((cond3 && file[i] < 32 && !space(file[i])) || file[i] == 127) {
		        cond = file[i] == '\t' ? 8 - col % 8 : 1;
			for (int i = 0; i < 7; i++)
				buffer[i] = 0;
			if (file[i] == 5) {
				buffer[0] = 'E';
				buffer[1] = 'N';
				buffer[2] = 'Q';
			} else if (file[i] == 7) {
				buffer[0] = '\\';
				buffer[1] = 'a';
			} else if (file[i] == 8) {
				buffer[0] = '\\';
				buffer[1] = 'b';
			} else if (file[i] == 11) {
				buffer[0] = '\\';
				buffer[1] = 'v';
			} else if (file[i] == 12) {
				buffer[0] = '\\';
				buffer[1] = 'f';
			} else if (file[i] == 13) {
				buffer[0] = '\\';
				buffer[1] = 'r';
			} else if (file[i] == 14) {
				buffer[0] = 'S';
				buffer[1] = 'O';
			} else if (file[i] == 15) {
				buffer[0] = 'S';
				buffer[1] = 'I';
			} else if (file[i] == 127) {
				buffer[0] = 'D';
				buffer[1] = 'E';
				buffer[2] = 'L';
			} else if (file[i] > 0) {
				buffer[0] = file[i];
				buffer[1] = ' ';
			} else
				buffer[0] = file[i];
			if (flags->c) {
				printf("%s [%i:%i]", path, ln, col - cond);
				printf(" %s%s%s",  fct_name ? fct : "", fct_name ? fct_name : "", fct_name ? "'" : "");
				if (flags->f) {
					printf(": '%s' ", buffer);
					printf("(ASCII %i) égaré dans le programme \n", (unsigned char)file[i]);
				} else {
					printf(": Trailing '%s' (ASCII %i)\n", buffer, (unsigned char)file[i]);
				}
			} else {
				display_path(path);
				printf(" [\033[32;1m%i\033[0m:\033[32;1m%i\033[0m]", ln, col - cond);
				printf(" \033[0m%s\033[31;1m%s\033[0m%s",  fct_name ? fct : "", fct_name ? fct_name : "", fct_name ? "'" : "");
				if (flags->f) {
					printf("\033[0m: '\033[31;1m%s\033[0m' ", buffer);
					printf("(ASCII \033[31;1m%i\033[0m) égaré dans le programme\n", (unsigned char)file[i]);
				} else {
					printf("\033[0m: Trailing '\033[31;1m%s\033[0m' (ASCII \033[31;1m%i\033[0m)\n", buffer, (unsigned char)file[i]);
				}
			}
			for (start = i; start >= 0 && file[start] != '\n'; start--);
			for (end = start + 1; file[end] != '\n' && file[end]; end++);
			if (flags->v) {
				bu = my_malloc(end - start + 10);
				sub_strings(file, start + 1, end, bu);
				mistake_line(cond, bu,  col, ln, flags, q, s_q, comment, 1);
				free(bu);
			}
			mistakes[TRAILING_SPACE]++;
		}
		if (cond3 && file[i] == ';' && file[i - 1] == ' ') {
			if (flags->c) {
				printf("%s [%i:%i]", path, ln, col + 1);
				printf(" %s%sm%s",  fct_name ? fct : "", fct_name ? fct_name : "", fct_name ? "'" : "");
				if (flags->f) {
					printf(": Point virgule isolé ");
					printf("des autres éléments\n");
				} else {
					printf(": Semicolon isolated from ");
					printf("other tokens\n");
				}
			} else {
				display_path(path);
				printf(" [\033[32;1m%i\033[0m:\033[32;1m%i\033[0m]", ln, col + 1);
				printf(" \033[0m%s\033[31;1m%s\033[0m%s",  fct_name ? fct : "", fct_name ? fct_name : "", fct_name ? "'" : "");
				if (flags->f) {
					printf("\033[0m: Point virgule isolé ");
					printf("des autres éléments\n");
				} else {
					printf("\033[0m: Semicolon isolated from ");
					printf("other tokens\n");
				}
			}
			for (start = i; start > 0 && file[start] != '\n'; start--);
			for (end = start + 1; file[end] != '\n' && file[end]; end++);
			if (flags->v) {
				bu = my_malloc(end - start + 10);
				sub_strings(file, start + 1, end, bu);
				mistake_line(2, bu, col - 1, ln, flags, q, s_q, comment, 1);
				free(bu);
			}
			mistakes[SEMICOLON_ISOLATED]++;
		}
		if (bracket > 0 && fct_name && cond3) {
			if (flags->d) {
				printf("[%i, %i]:Searching for comments.", ln, col);
				printf(" Found '");
				sub_strings(file, i, i + 2, buffer);
				my_showstr(buffer);
				printf("'\n");
			}
			if (file[i] == '/' && (file[i + 1] == '/' || file[i + 1] == '*')) {
				if (flags->c) {
					printf("%s [%i:%i]", path, ln, col);
					printf(" %s%s%s",  fct_name ? fct : "", fct_name ? fct_name : "", fct_name ? "'" : "");
					if (flags->f) {
						printf(": commentaire dans une ");
						printf(" fonction\n");
					} else
						printf(": comment in a function\n");
				} else {
					display_path(path);
					printf(" [\033[32;1m%i\033[0m:\033[32;1m%i\033[0m]", ln, col);
					printf(" \033[0m%s\033[31;1m%s\033[0m%s",  fct_name ? fct : "", fct_name ? fct_name : "", fct_name ? "'" : "");
					if (flags->f) {
						printf("\033[0m: commentaire dans une ");
						printf(" fonction\n");
					} else
						printf("\033[0m: comment in a function\n");
				}
				mistakes[COMMENT_IN_FCT]++;
				for (start = i; file[start] != '\n'; start--);
				for (end = start + 1; file[end] != '\n' && file[end]; end++);
				if (flags->v) {
					bu = my_malloc(end - start + 10);
					sub_strings(file, start + 1, end, bu);
					mistake_line(2, bu, col, ln, flags, q, s_q, 0, 1);
					free(bu);
				}
			}
		}
		cond = i > 0 && (file[i - 1] != '\\' || file[i - 2] == '\\');
		if (comment == 0 && !q && file[i] == '\'' && cond)
			s_q = !s_q;
		if (comment == 0 && !s_q && file[i] == '"' && cond)
			q = !q;
		if (!s_q && !q && file[i] == '{') {
			bracket++;
			verif_bracket_pos(file, i, words, mistakes, flags, ln, col, &fct_name, fct, path);
		}
		if (!s_q && !q && file[i] == '}') {
			bracket--;
			if (!bracket && fct_name) {
				if (flags->d)
					printf("[%i, %i]:New function found\n", ln, col);
				function++;
				line--;
				if (line > 20) {
					if (flags->c) {
				        	printf("%s [%i:%i]", path, ln, col + 1);
						printf(" %s%s%s",  fct_name ? fct : "", fct_name ? fct_name : "", fct_name ? "'" : "");
						if (flags->f)
							printf(": fonction trop longue ");
						else
							printf(": too long function ");
						printf("(%i)%s", line, flags->v ? "\n\n\n" : "\n");
					} else {
						display_path(path);
						printf(" [\033[32;1m%i\033[0m:\033[32;1m%i\033[0m]", ln, col + 1);
						printf(" \033[0m%s\033[31;1m%s\033[0m%s",  fct_name ? fct : "", fct_name ? fct_name : "", fct_name ? "'" : "");
						if (flags->f)
							printf("\033[0m: fonction trop longue ");
						else
							printf("\033[0m: too long function ");
						printf("(\033[31;1m%i\033[0m)%s", line, flags->v ? "\n\n\n" : "\n");
					}
					mistakes[TOO_LONG_FCT]++;
				}
				fine = file[i + 1] == '\n' || file[i + 1] == 0;
				fine = fine && (!file[i + 1] || !file[i + 2] || file[i + 2] == '\n');
				fine = fine && (!file[i + 1] || !file[i + 2] || !file[i + 3] || file[i + 3] != '\n');
				if (!fine) {
					if (flags->c) {
						printf("%s [%i:%i]", path, ln, col);
						printf(" %s%s%s",  fct_name ? "" : "", fct_name ? fct_name : "", fct_name ? "'" : "");
					} else {
						display_path(path);
						printf(" [\033[32;1m%i\033[0m:\033[32;1m%i\033[0m]", ln, col);
						printf(" \033[0m%s\033[31;1m%s\033[0m%s",  fct_name ? fct : "", fct_name ? fct_name : "", fct_name ? "'" : "");
					}
					if (flags->f) {
						printf(": Séparation do fonction invalide\n");
					} else
						printf(": Invalid function separator\n");
					mistakes[EMPTY_LINE_BETWEEN_FCTS]++;
					for (start = i; start > 0 && file[start] != '\n'; start--);
					for (end = start + 1; file[end] != '\n' && file[end]; end++);
					if (flags->v) {
						bu = my_malloc(end - start + 10);
						sub_strings(file, start + 1, end, bu);
						mistake_line(1, bu, col, ln, flags, q, s_q, comment, 1);
						free(bu);
					}
				}
				free(fct_name);
				fct_name = 0;
				line = 0;
			}
		}
		if (parenthesis == 0 && (file[i] == ';' || file[i] == '}')) {
			if (expected_indentlvl->data && flags->d)
				printf("[%i:%i]:Comparing %i with %i\n", ln, col, *(int *)expected_indentlvl->data, bracket);
			else if (flags->d)
				printf("[%i:%i]:No data\n", ln, col);
			for (start = i + 1; file[start] && space(file[start]); start++);
			if (match("else", &file[start])) {
				if (flags->d)
					printf("[%i:%i]:Found 'else'\n", ln, col);
				if (file[i] == ';')
					indentBuffer = -1;
				else
					indentBuffer = 1;
			}	
			while (indentBuffer <= 0 && expected_indentlvl->data && *(int *)expected_indentlvl->data >= bracket) {
				free(expected_indentlvl->data);
			        expected_indentlvl = expected_indentlvl->prev;
				free(expected_indentlvl->next);
				expected_indentlvl->next = 0;
				if (flags->d) {
					printf("[%i:%i]:Deleted list entry !\n", ln, col);
					if (expected_indentlvl->data)
						printf("[%i:%i]:Comparing %i with %i\n", ln, col, *(int *)expected_indentlvl->data, bracket);
					else
						printf("[%i:%i]:No data\n", ln, col);
				}
				if (indentBuffer == -1)
					break;
			}
			if (expected_indentlvl->data && flags->d)
				printf("[%i:%i]:%i < %i\n", ln, col, *(int *)expected_indentlvl->data, bracket);
		}
		if (file[i] == '\n') {
			act = 0;
		        current_indent_lvl = get_indent_lvl(&file[i + 1]);
			if (i == 0 || file[i - 1] != '\\')
				fine = get_indent_expected(&file[i], bracket, expected_indentlvl, comment);
			else
				fine = 0;
			for (int j = i; file[j] && (space(file[j]) || file[j] == '}'); j++)
				if (file[j] == '}') {
					fine--;
					break;
				}
			if (current_indent_lvl != -1 && current_indent_lvl != fine) {
				if (flags->c) {
					printf("%s [line:%i]", path, ln + 1);
					printf(" %s%s%s", fct_name ? fct : "", fct_name ? fct_name : "", fct_name ? "'" : "");
					if (flags->f)
						printf(": Mauvaise indentation (%i attendu mais %.2f trouvé)\n", fine, current_indent_lvl);
					else
						printf(": Bad indentation (%i expected %.2f found)\n", fine, current_indent_lvl);
				} else {
					display_path(path);
					printf(" [line:\033[32;1m%i\033[0m]", ln + 1);
					printf(" \033[0m%s\033[31;1m%s\033[0m%s",  fct_name ? fct : "", fct_name ? fct_name : "", fct_name ? "'" : "");
					if (flags->f)
						printf(": Mauvaise indentation (\033[32;1m%i\033[0m attendu mais \033[31;1m%.2f\033[0m trouvé)\n", fine, current_indent_lvl);
					else
						printf(": Bad indentation (\033[32;1m%i\033[0m expected but \033[31;1m%.2f\033[0m found)\n", fine, current_indent_lvl);
				}
				mistakes[BAD_INDENTATION]++;
				if (flags->v) {
					for (end = i + 1; file[end] && file[end] != '\n'; end++);
					bu = my_malloc(end - i + 1);
					sub_strings(file, i + 1, end, bu);
                                        mistake_line((int)current_indent_lvl * 8, bu, 0, ln + 1, flags, q, s_q, comment, 1);
					free(bu);
				}
			}
			if (fine > 10) {
				if (flags->c) {
					printf("%s [line:%i]", path, ln + 1);
					printf(" %s%s%s", fct_name ? fct : "", fct_name ? fct_name : "", fct_name ? "'" : "");
				} else {
					display_path(path);
					printf(" [line:\033[32;1m%i\033[0m]", ln + 1);
					printf(" \033[0m%s\033[31;1m%s\033[0m%s",  fct_name ? fct : "", fct_name ? fct_name : "", fct_name ? "'" : "");
				}
				printf(": il y a un jour où il faut s'arrêter...\n");
				mistakes[IF_DEPTH]++;
				mistakes[ETIENNE]++;
				if (flags->v) {
					for (end = i + 1; file[end] && file[end] != '\n'; end++);
					bu = my_malloc(end - i + 1);
					sub_strings(file, i + 1, end, bu);
                                        mistake_line((int)current_indent_lvl * 8, bu, 0, ln + 1, flags, q, s_q, comment, 1);
					free(bu);
				}
			} else if (fine > 3) {
				if (flags->c) {
					printf("%s [line:%i]", path, ln + 1);
					printf(" %s%s%s", fct_name ? fct : "", fct_name ? fct_name : "", fct_name ? "'" : "");
					if (flags->f)
						printf(": profondeur d'indentation de 3 ou plus (%i)\n", fine - 1);
					else
						printf(": nested conditonal branchings with a depth of 3 or more (%i)\n", fine - 1);
				} else {
					display_path(path);
					printf(" [line:\033[32;1m%i\033[0m]", ln + 1);
					printf(" \033[0m%s\033[31;1m%s\033[0m%s",  fct_name ? fct : "", fct_name ? fct_name : "", fct_name ? "'" : "");
					if (flags->f)
						printf(": profondeur d'indentation de 3 ou plus (\033[32;1m%i\033[0m)\n", fine - 1);
					else
						printf(": nested conditonal branchings with a depth of 3 or more (\033[31;1m%i\033[0m)\n", fine - 1);
				}
				mistakes[IF_DEPTH]++;
				if (flags->v) {
					for (end = i + 1; file[end] && file[end] != '\n'; end++);
					bu = my_malloc(end - i + 1);
					sub_strings(file, i + 1, end, bu);
                                        mistake_line((int)current_indent_lvl * 8, bu, 0, ln + 1, flags, q, s_q, comment, 1);
					free(bu);
				}
			}
			if (col > 1000) {
				printf("%s [line:%i]: ??????? Is this a joke ?\n", path, ln);
				for (start = i - 1; start > 0 && file[start] != '\n'; start--);
				bu = my_malloc(i - start + 1);
				sub_strings(file, start + 1, i, bu);
				mistake_line(col, bu, -1, ln, flags, q, s_q, comment, 1);
				free(bu);
				mistakes[TOO_LONG_LINE]++;
			        mistakes[ETIENNE]++;
			} else if (col > 80) {
                                if (flags->d)
                                        printf("Too long line %i\n", col);
				if (flags->c) {
					printf("%s [line:%i]", path, ln);
					printf(" %s%s%s", fct_name ? fct : "", fct_name ? fct_name : "", fct_name ? "'" : "");
					if (flags->f)
						printf(": ligne trop longue ");
					else
						printf(": too long line ");
					printf("(%i)\n", col);
				} else {
					display_path(path);
					printf(" [line:\033[32;1m%i\033[0m]", ln);
					printf(" \033[0m%s\033[31;1m%s\033[0m%s",  fct_name ? fct : "", fct_name ? fct_name : "", fct_name ? "'" : "");
					if (flags->f)
						printf("\033[0m: ligne trop longue ");
					else
						printf("\033[0m: too long line ");
					printf("(\033[31;1m%i\033[0m)\n", col);
				}
				mistakes[TOO_LONG_LINE]++;
				if (flags->v) {
					for (start = i - 1; start > 0 && file[start] != '\n'; start--);
					bu = my_malloc(i - start + 1);
					sub_strings(file, start + 1, i, bu);
                                        mistake_line(col - 80, bu, 80, ln, flags, q, s_q, comment, 1);
					free(bu);
				}
                        }
			for (fine = i + 1; file[fine] && space(file[fine]) && file[fine] != '\n'; fine++);
			if (bracket > 0 && file[fine] != '\n')
				line++;
			ln++;
			col = 0;
			begin_of_line = 1;
			declaring_var = 1;
			comment = comment == 1 ? 0 : comment;
			if (cond3)
				check_ind(file, mistakes, path, ln, i, flags, fct_name, fct, q, s_q, comment);
		} else if(!space(file[i]))
			begin_of_line =	0;
		if (file[i] == '(' || file[i] == '{' || file[i] == '}')
			declaring_var = 0;
		if (cond3 && !declaring_var && !begin_of_line && space(file[i]) && space(file[i + 1]) && nobackslash(&file[i])) {
			if (flags->c) {
				printf("%s [%i:%i]", path, ln, col - cond);
				printf(" %s%s%s",  fct_name ? fct : "", fct_name ? fct_name : "", fct_name ? "'" : "");
				cond = file[i] == '\t' ? 8 - col % 8 : 1;
				if (flags->f) {
					bu = file[i] == ' ' ? "Espace" : bu;
					bu = file[i] == '\t' ? "Tabulation" : bu;
					printf(": %s égaré", bu);
					printf(" dans le programme \n");
				} else {
					bu = file[i] == ' ' ? "space" : bu;
					bu = file[i] == '\t' ? "tab" : bu;
					printf(": Trailing %s\n", bu);
				}
			} else {
				display_path(path);
				printf(" [\033[32;1m%i\033[0m:\033[32;1m%i\033[0m]", ln, col - cond);
				printf(" \033[0m%s\033[31;1m%s\033[0m%s",  fct_name ? fct : "", fct_name ? fct_name : "", fct_name ? "'" : "");
				cond = file[i] == '\t' ? 8 - col % 8 : 1;
				if (flags->f) {
					bu = file[i] == ' ' ? "Espace" : bu;
					bu = file[i] == '\t' ? "Tabulation" : bu;
					printf("\033[0m: %s égaré", bu);
					printf(" dans le programme \n");
				} else {
					bu = file[i] == ' ' ? "space" : bu;
					bu = file[i] == '\t' ? "tab" : bu;
					printf("\033[0m: Trailing %s\n", bu);
				}
			}
			for (start = i; start > 0 && file[start] != '\n'; start--);
			for (end = start + 1; file[end] != '\n' && file[end]; end++);
			if (flags->v) {
				bu = my_malloc(end - start + 10);
				sub_strings(file, start + 1, end, bu);
				mistake_line(cond, bu,  col, ln, flags, q, s_q, comment, 1);
				free(bu);
			}
			mistakes[TRAILING_SPACE]++;
		}
	        if (file[i] >= 32 || (unsigned char)file[i] == 195)
			col++;
		else if (file[i] == '\t')
			col = (col + 8) - (col % 8);
	}
	if (function > 5) {
		if (flags->c)
			printf("%s", path);
		else
			display_path(path);
		if (flags->f) {
			printf(": Plus de 5 fonctions");
			if (flags->c)
				printf(" dans un fichier (%i)%s", function, flags->v ? "\n\n\n" : "\n");
			else
				printf(" dans un fichier (\033[31;1m%i\033[0m)%s", function, flags->v ? "\n\n\n" : "\n");
		} else {
			printf(": More than 5 functions");
			if (flags->c)
				printf(" in a single file (%i)%s", function, flags->v ? "\n\n\n" : "\n");
			else
				printf(" in a single file (\033[31;1m%i\033[0m)%s", function, flags->v ? "\n\n\n" : "\n");
		}
		mistakes[TOO_MNY_FCT]++;
	}
	free(fct_name);
	if (flags->d)
		printf("End of buffer\n");
        delStackTraceEntry();
}

void	scan_c_file(char *path, int *mistakes, char const **key_words, flag *flags)
{
	char	*file_content;

	addStackTraceEntry("scan_c_file", "pppp", "path", path, "mistakes", mistakes, "key_words", key_words, "flags", flags);
	file_content = load_file(path);
	if (!file_content) {
		delStackTraceEntry();
		return;
	}
	check_header(file_content, flags, mistakes, path);
	find_long_fct(file_content, mistakes, path, key_words, flags);
	if (flags->d)
		printf("File %s scanned !\n\n", path);
        free(file_content);
	delStackTraceEntry();
}

void	scan_h_file(char *path, int *mistakes, flag *flags)
{
	char	*file_content;

	addStackTraceEntry("scan_h_file", "ppp", "path", path, "mistakes", mistakes, "flags", flags);
	file_content = load_file(path);
	if (!file_content) {
		delStackTraceEntry();
		return;
	}
	check_header(file_content, flags, mistakes, path);
	find_long_fct(file_content, mistakes, path, (char const *[2]){0, 0}, flags);
	free(file_content);
	delStackTraceEntry();
}
