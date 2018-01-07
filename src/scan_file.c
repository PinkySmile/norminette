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
	buffer = malloc(info.st_size + 1);
	read(fd, buffer, info.st_size);
	buffer[info.st_size] = 0;
	close(fd);
	delStackTraceEntry();
	return (buffer);
}

void	mistake_line(int size, char *line, int col, int ln, flag *flags, int q, int s_q, int comment)
{
	int	col_c = 0;
	int	chars = 0;
	int	arrow_displayed = 0;
	int	buffer = 0;

	addStackTraceEntry("mistake_line", "ipiipbbi", "size", size, "line", line, "col", col, "ln", ln, "flags", flags, "q", q, "s_q", s_q, "comment", comment);
	if (!flags->c)
		printf("\033[0m\033[32m");
	chars = printf("[%i:%i]", ln, col);
	if (!flags->c)
		printf("\033[93m");
	for (int i = 0; i < 8 - chars % 8 + 7; i++)
		printf("-");
	printf(">");
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
		if (!flags->c && col_c > col && col_c <= col + size)
			printf("\033[95;1m");	
		else if (!flags->c && (buffer > 0 || comment != 0))
			printf("\033[0m\033[31m");
		else if (!flags->c && (q || s_q || line[i] == '"' || line[i] == '\''))
			printf("\033[0m\033[35m");
		else if (!flags->c)
			printf("\033[0m");
		printf("%c", line[i]);
	}
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
			printf("\033[0m\033[1m%c", path[i]);
			slash++;
		} else if (slash == max_slash)
			printf("\033[36;1m%c", path[i]);
		else
			printf("\033[34;1m%c", path[i]);
	printf("\033[0m");
	delStackTraceEntry();
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

	addStackTraceEntry("verif_fct_used", "ppppppipip", "name", name, "flags", flags, "file_name", file_name, "mistakes", mistakes, \
			   "words", words, "fct", fct, "ln", ln, "fct_name", "col", col, "file", file);
	if (!is_in_list(flags->fcts, name) && !is_in_array(words, name) && !whitelisted(name)) {
		mistakes[25]++;
		if (flags->c) {
			printf("%s [%i:%i]", file_name, ln, col);
			printf(" %s%s%s",  fct_name ? fct : "", fct_name ? fct_name : "", fct_name ? "' " : "");
			if (flags->f)
				printf(": fonction interdite utilisée (%s)\n", name);
			else
				printf(": forbidden function used (%s)\n", name);
		} else {
			display_path(file_name);
			printf(" [\033[32;1m%i\033[0m:\033[32;1m%i\033[0m]", ln, col);
			printf(" \033[0m%s\033[31;1m%s\033[0m%s",  fct_name ? fct : "", fct_name ? fct_name : "", fct_name ? "' " : "");
			if (flags->f)
				printf(": fonction interdite utilisée (\033[31;1m%s\033[0m)\n", name);
			else
				printf(": forbidden function used (\033[31;1m%s\033[0m)\n", name);
		}
		if (flags->v) {
			for (; file[end] && file[end] != '\n'; end++);
			buffer = malloc(end + 2);
			sub_strings(file, 0, end, buffer);
			mistake_line(strlen(name), buffer, col - strlen(name), ln, flags, 0, 0, 0);
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
			mistakes[10]++;
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
				bu = malloc(c - i + 2);
				sub_strings(file, i + 1, c, bu);
				for (spaces = 0; file[jl + spaces] == ' '; spaces++);
				mistake_line(spaces, bu, col, ln, flags, q, s_q, comment);
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
			mistakes[10]++;
			if (flags->c){
				printf("%s [%i:%i]", path, ln, col + 1);
				printf(" %s%s%s",  fct_name ? fct : "", fct_name ? fct_name : "", fct_name ? "'" : "");
				if (flags->f)
					printf(" : erreur d'indentation (ligne vide)\n");
				else
					printf(" : bad indentation (empty line)\n");
			} else {
				display_path(path);
				printf(" [\033[32;1m%i\033[0m:\033[32;1m%i\033[0m]", ln, col + 1);
				printf(" \033[0m%s\033[31;1m%s\033[0m%s",  fct_name ? fct : "", fct_name ? fct_name : "", fct_name ? "'" : "");
				if (flags->f)
					printf("\033[0m : erreur d'indentation (ligne vide)\n");
				else
					printf("\033[0m : bad indentation (empty line)\n");
			}
			if (flags->v) {
				bu = malloc(i + 1);
				sub_strings(file, i + 1, i - jl, bu);
			        mistake_line((jl - i - 1) * 8, bu, 0, ln, flags, 0, 0, 0);
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
	if (file[beg] == ';' || file[beg] == '\n')
		return (0);
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
	name = malloc(1 - i);
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
				printf(" : 'void' attendu pour une fonction");
				printf(" ne prenant aucun argument\n");
			} else {
				printf(" : 'void' expected ");
				printf("for a function that takes no argument\n");
			}
		} else {
			display_path(path);
			printf(" [\033[32;1m%i\033[0m:\033[32;1m%i\033[0m]", ln, col);
			printf("\033[1m%s\033[31;1m%s\033[0m'",  flags->f ? " dans la fonction '" : " in function '", name);
			if (flags->f) {
				printf("\033[0m : 'void' attendu pour une fonction");
				printf(" ne prenant aucun argument\n");
			} else {
				printf("\033[0m : 'void' expected ");
				printf("for a function that takes no argument\n");
			}
		}
		for (end = 0; file[end] != '\n' && file[end]; end++);
		if (flags->v) {
			void_ = malloc(end + 10);
			sub_strings(file, 0, end, void_);
			mistake_line(strlen(name), void_, col, ln, flags, 0, 0, 0);
			free(void_);
		}
		mistakes[7]++;
	} else if (args_nbr > 4) {
		if (flags->c) {
			printf("%s [%i:%i]", path, ln, col + 1);
			if (flags->f) {
				printf(" : trop d'arguments pour la fonction '%s'", name);
				printf(" (4 maximum mais %i trouvés)\n", args_nbr);
			} else {
				printf(" : too many arguments for function '%s'", name);
				printf(" (4 max but %i found)\n", args_nbr);
			}
		} else {
			display_path(path);
			printf(" [\033[32;1m%i\033[0m:\033[32;1m%i\033[0m]", ln, col + 1);
			if (flags->f) {
				printf(" : trop d'arguments pour la fonction '%s'", name);
				printf(" (4 maximum mais \033[31;1m%i\033[0m trouvés)\n", args_nbr);
			} else {
				printf(" : too many arguments for function '%s'", name);
				printf(" (4 max but \033[31;1m%i\033[0m found)\n", args_nbr);
			}
		}
		for (end = 0; file[end] != '\n' && file[end]; end++);
		if (flags->v) {
			void_ = malloc(end + 10);
			sub_strings(file, 0, end, void_);
			mistake_line(strlen(name), void_, col, ln, flags, 0, 0, 0);
			free(void_);
		}
		mistakes[7]++;
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
			if (flags->c)
				if (flags->f)
					printf(" dans la fonction '%s': Nom invalide\n", name);
				else
					printf(" in function '%s': Invalid name\n", name);
			else {
				if (flags->f)
					printf(" dans la fonction '\033[31;1m%s\033[0m': Nom invalide\n", name);
				else
					printf(" in function '\033[31;1m%s\033[0m': Invalid name\n", name);
			}
			for (end = 0; file[end] != '\n' && file[end]; end++);
			if (flags->v) {
				void_ = malloc(end + 10);
				sub_strings(file, 0, end, void_);
				mistake_line(strlen(name), void_, col, ln, flags, 0, 0, 0);
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
	char	*fct = flags->f ? (flags->c ? "dans la fonction '" : "\033[1mdans la fonction '") : (flags->c ? "in function '" : "\033[1min fonction '");
        int	cond = 0;
	int	cond2 = 0;
	int	cond3 = 0;
	int	start = 0;
	int	end = 0;
	int	comment = 0;
	int	begin_of_line = 1;
	int	declaring_var = 0;
	char	*ptr = file;
	int	l_o = 0;

	addStackTraceEntry("find_long_fct", "ppppp", "file", file, "mistakes", mistakes, "path", path, "words", words, "flags", flags);
	if (flags->d)
		printf("Beggining of buffer\n");
	for (int i = 0 ; file[i] ; i++) {
		cond3 = !q && !s_q && comment == 0;
		if (flags->d) {
			printf("[%i, %i]:Loop start '%c' (%i)\n", ln, col, file[i] > 31 ? file[i] : 0, file[i]);
			printf("Global conditions :\tcond3   : %s\n", cond3 ? "TRUE" : "FALSE");
			printf("\t\t\ts_quote : %s\n", q ? "TRUE" : "FALSE");
			printf("\t\t\td_quote : %s\n", s_q ? "TRUE" : "FALSE");
			printf("\t\t\tcomment: %i\n", comment);
		}
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
		} else if (cond3 && file[i] == '\n' && flags->i_caps) {
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
					printf(" %s%s%s",  fct_name ? fct : "", fct_name ? fct_name : "", fct_name ? "' " : "");
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
					printf(" \033[0m%s\033[31;1m%s\033[0m%s",  fct_name ? fct : "", fct_name ? fct_name : "", fct_name ? "' " : "");
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
					bu = malloc(end - start + 10);
					sub_strings(file, start + 1, end, bu);
					mistake_line(l_o, bu, col - l_o, ln, flags, q, s_q, comment);
					free(bu);
				}
				mistakes[22]++;
			}
			l_o = 0;
		}
		if (cond3 && file[i] == '/' && file[i + 1] == '/') {
			comment = 1;
			if (flags->d)
				printf("[%i, %i]:Start simple comments\n", ln, col);
		} else if (cond3 && file[i] == '/' && file[i + 1] == '*') {
			comment += 2;
			if (flags->d)
				printf("[%i, %i]:Start of multilines comments\n", ln, col);
		}
		if (!q && !s_q && !(comment % 2) && file[i] == '*' && file[i + 1] == '/') {
			comment -= 2;
			if (flags->d)
				printf("[%i, %i]:End of multilines comments\n", ln, col);
		}
		sub_strings(file, i, i + 4, buffer);
		if (cond3 && compare_strings(buffer, "goto")) {
			if (flags->c) {
				printf("%s [%i:%i]", path, ln, col + 1);
				printf(" %s%s%s",  fct_name ? fct : "", fct_name ? fct_name : "", fct_name ? "' " : "");
				if (flags->f)
					printf(": Utilisation de goto interdit\n");
				else
					printf(": The use of goto is forbidden\n");
			} else {
				display_path(path);
				printf(" [\033[32;1m%i\033[0m:\033[32;1m%i\033[0m]", ln, col + 1);
				printf(" \033[0m%s\033[31;1m%s\033[0m%s",  fct_name ? fct : "", fct_name ? fct_name : "", fct_name ? "' " : "");
				if (flags->f)
					printf("\033[0m: Utilisation de goto interdit\n");
				else
					printf("\033[0m: The use of goto is forbidden\n");
			}
			for (start = i; file[start] != '\n'; start--);
			for (end = start + 1; file[end] != '\n' && file[end]; end++);
			if (flags->v) {
				bu = malloc(end - start + 10);
				sub_strings(file, start + 1, end, bu);
				mistake_line(4, bu, col, ln, flags, q, s_q, comment);
				free(bu);
			}
			mistakes[17]++;
		
		}
		for (int k = 0; words[k] && cond3; k++) {
			sub_strings(file, i, i + strlen(words[k]), buffer);
			cond = (i + strlen(words[k])) < strlen(file);
		        cond = cond && file[i + strlen(words[k])] == '(';
			if (flags->d) {
				printf("[%i, %i]:Searching for '%s'", ln, col, words[k]);
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
		        cond = cond && cond2;
			if(compare_strings(buffer, words[k]) && cond) {
				if (flags->c) {
					printf("%s [%i:%i]", path, ln, col + 1);
					printf(" %s%s%s",  fct_name ? fct : "", fct_name ? fct_name : "", fct_name ? "' " : "");
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
					printf(" \033[0m%s\033[31;1m%s\033[0m%s",  fct_name ? fct : "", fct_name ? fct_name : "", fct_name ? "' " : "");
					if (flags->f) {
						printf("\033[0m: espace manquant ");
						printf("après le mot clé '%s'\n", words[k]);
					} else {
						printf("\033[0m: space missing after ");
						printf("key word '%s'\n", words[k]);
					}
				}
				for (start = i; file[start] != '\n'; start--);
				for (end = start + 1; file[end] != '\n' && file[end]; end++);
				if (flags->v) {
					bu = malloc(end - start + 10);
					sub_strings(file, start + 1, end, bu);
					mistake_line(strlen(words[k]), bu, col, ln, flags, q, s_q, comment);
					free(bu);
				}
				mistakes[11]++;
			}
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
				printf(" %s%s%s",  fct_name ? fct : "", fct_name ? fct_name : "", fct_name ? "' " : "");
				if (flags->f) {
					printf(": '%s' ", buffer);
					printf("(ASCII %i) égaré dans le programme \n", (unsigned char)file[i]);
				} else {
					printf(": Trailing '%s' (ASCII %i)\n", buffer, (unsigned char)file[i]);
				}
			} else {
				display_path(path);
				printf(" [\033[32;1m%i\033[0m:\033[32;1m%i\033[0m]", ln, col - cond);
				printf(" \033[0m%s\033[31;1m%s\033[0m%s",  fct_name ? fct : "", fct_name ? fct_name : "", fct_name ? "' " : "");
				if (flags->f) {
					printf("\033[0m: '\033[31;1m%s\033[0m' ", buffer);
					printf("(ASCII \033[31;1m%i\033[0m) égaré dans le programme \n", (unsigned char)file[i]);
				} else {
					printf("\033[0m: Trailing '\033[31;1m%s\033[0m' (ASCII \033[31;1m%i\033[0m)\n", buffer, (unsigned char)file[i]);
				}
			}
			for (start = i; start >= 0 && file[start] != '\n'; start--);
			for (end = start + 1; file[end] != '\n' && file[end]; end++);
			if (flags->v) {
				bu = malloc(end - start + 10);
				sub_strings(file, start + 1, end, bu);
				mistake_line(cond, bu,  col, ln, flags, q, s_q, comment);
				free(bu);
			}
			mistakes[19]++;
		}
		if (cond3 && file[i] == ';' && file[i - 1] == ' ') {
			if (flags->c) {
				printf("%s [%i:%i]", path, ln, col + 1);
				printf(" %s%sm%s",  fct_name ? fct : "", fct_name ? fct_name : "", fct_name ? "' " : "");
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
				printf(" \033[0m%s\033[31;1m%s\033[0m%s",  fct_name ? fct : "", fct_name ? fct_name : "", fct_name ? "' " : "");
				if (flags->f) {
					printf("\033[0m: Point virgule isolé ");
					printf("des autres éléments\n");
				} else {
					printf("\033[0m: Semicolon isolated from ");
					printf("other tokens\n");
				}
			}
			for (start = i; file[start] != '\n'; start--);
			for (end = start + 1; file[end] != '\n' && file[end]; end++);
			if (flags->v) {
				bu = malloc(end - start + 10);
				sub_strings(file, start + 1, end, bu);
				mistake_line(2, bu, col - 1, ln, flags, q, s_q, comment);
				free(bu);
			}
			mistakes[21]++;
		}
		if (file[i] == '\n') {
			if (col > 80) {
                                if (flags->d)
                                        printf("Too long line %i\n", col);
				if (flags->c) {
					printf("%s [line:%i]", path, ln);
					printf(" %s%s%s", fct_name ? fct : "", fct_name ? fct_name : "", fct_name ? "' " : "");
					if (flags->f)
						printf(": ligne trop longue ");
					else
						printf(": too long line ");
					printf("(%i)\n", col);
				} else {
					display_path(path);
					printf(" [line:\033[32;1m%i\033[0m]", ln);
					printf(" \033[0m%s\033[31;1m%s\033[0m%s",  fct_name ? fct : "", fct_name ? fct_name : "", fct_name ? "' " : "");
					if (flags->f)
						printf("\033[0m: ligne trop longue ");
					else
						printf("\033[0m: too long line ");
					printf("(\033[31;1m%i\033[0m)\n", col);
				}
				mistakes[5]++;
				if (flags->v) {
					for (start = i - 1; file[start] && file[start] != '\n'; start--);
					bu = malloc(i - start + 1);
					sub_strings(file, start + 1, i, bu);
                                        mistake_line(col - 80, bu, 80, ln, flags, q, s_q, comment);
					free(bu);
				}
                        }
			if (bracket > 0)
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
				printf(" %s%s%s",  fct_name ? fct : "", fct_name ? fct_name : "", fct_name ? "' " : "");
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
				printf(" \033[0m%s\033[31;1m%s\033[0m%s",  fct_name ? fct : "", fct_name ? fct_name : "", fct_name ? "' " : "");
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
				bu = malloc(end - start + 10);
				sub_strings(file, start + 1, end, bu);
				mistake_line(cond, bu,  col, ln, flags, q, s_q, comment);
				free(bu);
			}
			mistakes[19]++;
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
					printf(" %s%s%s",  fct_name ? fct : "", fct_name ? fct_name : "", fct_name ? "' " : "");
					if (flags->f) {
						printf(": commentaire dans une ");
						printf(" fonction\n");
					} else
						printf(": comment in a function\n");
				} else {
					display_path(path);
					printf(" [\033[32;1m%i\033[0m:\033[32;1m%i\033[0m]", ln, col);
					printf(" \033[0m%s\033[31;1m%s\033[0m%s",  fct_name ? fct : "", fct_name ? fct_name : "", fct_name ? "' " : "");
					if (flags->f) {
						printf("\033[0m: commentaire dans une ");
						printf(" fonction\n");
					} else
						printf("\033[0m: comment in a function\n");
				}
				mistakes[8]++;
				for (start = i; file[start] != '\n'; start--);
				for (end = start + 1; file[end] != '\n' && file[end]; end++);
				if (flags->v) {
					bu = malloc(end - start + 10);
					sub_strings(file, start + 1, end, bu);
					mistake_line(2, bu, col, ln, flags, q, s_q, 0);
					free(bu);
				}
			}
		}
		cond = i > 0 && (file[i - 1] != '\\' || file[i - 2] == '\\');
		if (comment == 0 && !q && file[i] == '\'' && cond)
			s_q = !s_q;
		if (comment == 0 && !s_q && file[i] == '"' && cond)
			q = !q;
		if (!s_q && !q && file[i] == '{')
			bracket++;
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
						printf(" %s%s%s",  fct_name ? fct : "", fct_name ? fct_name : "", fct_name ? "' " : "");
						if (flags->f)
							printf(": fonction trop longue ");
						else
							printf(": too long function ");
						printf("(%i)%s", line, flags->v ? "\n\n\n" : "\n");
					} else {
						display_path(path);
						printf(" [\033[32;1m%i\033[0m:\033[32;1m%i\033[0m]", ln, col + 1);
						printf(" \033[0m%s\033[31;1m%s\033[0m%s",  fct_name ? fct : "", fct_name ? fct_name : "", fct_name ? "' " : "");
						if (flags->f)
							printf("\033[0m: fonction trop longue ");
						else
							printf("\033[0m: too long function ");
						printf("(\033[31;1m%i\033[0m)%s", line, flags->v ? "\n\n\n" : "\n");
					}
					mistakes[6]++;
				}
				free(fct_name);
				fct_name = 0;
				line = 0;
        		}
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
			printf(" : Plus de 5 fonctions");
			if (flags->c)
				printf(" dans un fichier (%i)%s", function, flags->v ? "\n\n\n" : "\n");
			else
				printf(" dans un fichier (\033[31;1m%i\033[0m)%s", function, flags->v ? "\n\n\n" : "\n");
		} else {
			printf(" : More than 5 functions");
			if (flags->c)
				printf(" in a single file (%i)%s", function, flags->v ? "\n\n\n" : "\n");
			else
				printf(" in a single file (\033[31;1m%i\033[0m)%s", function, flags->v ? "\n\n\n" : "\n");
		}
		mistakes[1] += function - 5;
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
	find_long_fct(file_content, mistakes, path, (char const *[2]){0, 0}, flags);
	free(file_content);
	delStackTraceEntry();
}
