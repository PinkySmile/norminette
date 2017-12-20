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

char	*load_file(char *path)
{
	int		fd = 0;
	char		*buffer;
	struct stat	info;

	if (stat(path, &info) < 0) {
		perror("");
		return (0);
	}
	fd = open(path, O_RDONLY);
	if (fd <= 0) {
		perror("");
		return (0);
	}
	buffer = malloc(info.st_size + 1);
	read(fd, buffer, info.st_size);
	buffer[info.st_size] = 0;
	close(fd);
	return (buffer);
}

void	mistake_line(int size, char *line, int col, int ln)
{
	int	col_c = 0;
	int	chars = 0;
	int	ik = 0;

	if (col == 0)
		col = 0;
	chars = printf("[%i:%i]-->", ln, col);
	for (int i = 0; line[i]; i++) {
		if (line[i] == '\t')
			col_c = (col_c + 8) - (col_c % 8);
		else if (line[i] >= 32)
			col_c++;
		if (col_c > col && col_c <= col + size)
			printf("\033[95;1m");
		else
			printf("\033[0m");
		printf("%c", line[i]);
	}
	printf("\033[0m\n");
	for (int i = 0; i < chars; i++)
		printf(" ");
	for (int jo = 0; jo < col - 1 && line[ik]; jo++) {
		if (line[ik] == '\t') {
			jo = jo + 8 - (jo % 8) - 1;
			printf("\t");
		} else if (line[ik] < 32)
			jo--;
		printf(" ");
		ik++;
	}
	printf("\033[95;1m^");
	for (int jo = 0; jo < size - 1; jo++)
		printf("~");
	printf("\n\033[0m");
}

void	display_path(char *path)
{
	int	slash = 0;
	int	max_slash = 0;

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
}

void	verif_fct_name(char *name, flag *flags, char *file_name, int *mistakes)
{
	int     cond = 0;

        for (int i = 0; name[i]; i++) {
                cond = name[i] == '_' || name[i] == '.';
                cond = cond || compare_strings(name, "Makefile");
		cond = cond || (name[i] >= '0' && name[i] <= '9');
                if (!((name[i] >= 'a' && name[i] <= 'z') || cond)) {
                        mistakes[24]++;
			display_path(file_name);
                        if (flags->f)
                                printf(" in function '\033[31;1m%s\033[0m': Nom invalide\n", name);
                        else
                                printf(" in function '\033[31;1m%s\033[0m': Invalid name\n", name);
                        break;
                }
        }
}

int	is_in_list(list_t *list, char *str)
{
	for (; list->next; list = list->next)
		if (compare_strings(str, (char *)list->data))
			return (1);
	return (0);
}

int	is_in_array(char const **array, char *str)
{
	for (int i = 0; array[i]; i++)
		if (compare_strings(str, array[i]))
			return (1);
	return (0);
}

void	verif_fct_used(char *name, flag *flags, char *file_name, int *mistakes, char const **words, char *fct, int ln, char *fct_name)
{
	if (!compare_strings(name, "") && !is_in_list(flags->fcts, name) && !is_in_array(words, name)) {
		display_path(file_name);
		mistakes[25]++;
		printf(" [line:\033[32;1m%i\033[0m]", ln);
		printf(" \033[0m%s\033[31;1m%s\033[0m%s",  fct_name ? fct : "", fct_name ? fct_name : "", fct_name ? "' " : "");
		if (flags->f)
			printf(": fonction interdite utilisée (\033[31;1m%s\033[0m)\n", name);
		else
			printf(": forbidden function used (\033[31;1m%s\033[0m)\n", name);
	}
}

void	check_ind(char *file, int *mistakes, char *path, int ln, int i, flag *flags, char *fct_name, char *fct)
{
	int	col = 0;
	int	c = 0;
	char	*bu = 0;
	int	spaces = 0;
	int	backslash_t = 0;

	if (flags->d)
		printf("[%i]:Checking ind\n", col);
        for (int jl = i + 1; jl != -1 && file[jl]; jl++) {
		if (flags->d)
			printf("[%i]:Loop start '%c' (%i)\n", col, file[jl] > 31 ? file[jl] : 0, file[jl]);
		if (file[jl] == ' ') {
			if (flags->d)
				printf("[%i]:Found a space\n", col);
			mistakes[10]++;
			display_path(path);
			printf(" [\033[32;1m%i\033[0m:\033[32;1m%i\033[0m]", ln, col + 1);
			printf(" \033[0m%s\033[31;1m%s\033[0m%s",  fct_name ? fct : "", fct_name ? fct_name : "", fct_name ? "'" : "");
			if (flags->f)
				printf("\033[0m: erreur d'indentation\n");
			else
				printf("\033[0m: bad indentation\n");
			for (c = i + 1; file[c] != '\n' && file[c]; c++);
			if (flags->v) {
				bu = malloc(c - i + 2);
				sub_strings(file, i + 1, c, bu);
				for (spaces = 0; file[jl + spaces] == ' '; spaces++);
				mistake_line(spaces, bu, col, ln);
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
			display_path(path);
			printf(" [\033[32;1m%i\033[0m:\033[32;1m%i\033[0m]", ln, col + 1);
			printf(" \033[0m%s\033[31;1m%s\033[0m%s",  fct_name ? fct : "", fct_name ? fct_name : "", fct_name ? "'" : "");
			if (flags->f)
				printf("\033[0m : erreur d'indentation (ligne vide)\n");
			else
				printf("\033[0m : bad indentation (empty line)\n");
			if (flags->v) {
				bu = malloc(i + 1);
				sub_strings(file, i + 1, i - jl, bu);
			        mistake_line((jl - i - 1) * 8, bu, -1, ln);
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
}

int	space(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

char	*get_function_name(char *file, flag *flags, int *mistakes, int ln, char *path)
{
	int	i = 0;
	int	beg = 0;
	char	*name = 0;
	int	end = 0;
	int	args_nbr = 1;
	char	*void_ = "void";
	int	col = 0;

	file++;
	if (*file == '#') {
		if (flags->d)
			printf("Found #\n\n");
		return (0);
	}
	if (flags->d) {
		printf("Getting function name for line : ");
		for (int j = 0; file[j] && file[j] != '\n'; j++)
			printf("%c", file[j]);
		printf("\n");
	}
	for (; file[beg] && file[beg] != '(' && file[beg] != ';' && file[beg] != '\n'; beg++) {
		col++;
		if (file[beg] == '\t')
			col += 7 - col % 8;
		if (flags->d)
			printf("Skipping %c\n", file[beg]);
	}
	if (file[beg] == ';' || file[beg] == '\n')
		return (0);
	for (; file[beg + i] && file[beg + i] != '*' && !space(file[beg + i]); i--) {
		col--;
		if (file[beg + i] == '\t')
			col -= 7 + col % 8;
	}
	for (int j = 0; file[beg + j] && file[beg + j] != ')'; j++)
		if (file[beg + j] == ',')
			args_nbr++;
	if (file[i + beg] && file[i + beg + 1] == ')')
		args_nbr = 0;
	name = malloc(1 - i);
	sub_strings(file, beg + i + 1, beg, name);
	for (int j = 0; name[j]; j++)
		if (name[j] <= 32)
			for (int k = j; name[k]; k++)
				name[k] = name[k + 1];
	if (args_nbr == 0) {
		for (; space(name[i + beg + args_nbr]) && name[i + beg + args_nbr]; args_nbr++);
		for (int j = args_nbr; void_[j - args_nbr] && name[i + beg + j]; j++)
			if (void_[j - args_nbr] != name[i + beg + j]) {
				display_path(path);
				printf(" [\033[32;1m%i\033[0m:\033[32;1m%i\033[0m]", ln, col + 1);
				printf(" \033[0m%s\033[31;1m%s\033[0m'",  flags->f ? " dans la fonction '" : " in function '", name);
				if (flags->f) {
					printf("\033[0m : 'void' attendu pour une fonction");
					printf(" ne prenant aucun argument\n");
				} else {
					printf("\033[0m : 'void' expected ");
					printf("for a function that takes no argument\n");
				}
			        for (end = 0; file[end] != '\n' && file[end]; end++);
				if (flags->v) {
					void_ = malloc(end + 10);
					sub_strings(file, 0, end, void_);
					mistake_line(strlen(name), void_, col - strlen(name) + 1, ln);
					free(void_);
				}
				mistakes[7]++;
			}
	} else if (args_nbr > 4) {
		display_path(path);
	        printf(" [\033[32;1m%i\033[0m:\033[32;1m%i\033[0m]", ln, col + 1);
		if (flags->f) {
			printf(" : trop d'arguments pour la fonction '%s'", name);
			printf(" (4 maximum mais \033[31;1m%i\033[0m trouvées)\n", args_nbr);
		} else {
			printf(" : too many arguments for function '%s'", name);
			printf(" (4 max but \033[31;1m%i\033[0m found)\n", args_nbr);
		}
		for (end = 0; file[end] != '\n' && file[end]; end++);
		if (flags->v) {
			void_ = malloc(end + 10);
			sub_strings(file, 0, end, void_);
			mistake_line(strlen(name), void_, col - strlen(name) + 1, ln);
			free(void_);
		}
		mistakes[7]++;
	}
	if (flags->d)
		printf("Found %i arguments for function %s\n\n", args_nbr, name);
	return (name);
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
	char	*fct = flags->f ? "\033[1mdans la fonction '" : "\033[1min function '";
        int	cond = 0;
	int	cond2 = 0;
	int	cond3 = 0;
	int	start = 0;
	int	end = 0;
	int	comment = 0;
	int	begin_of_line = 1;
	int	declaring_var = 0;

	if (flags->d)
		printf("Beggining of buffer\n");
	for (int i = 0 ; file[i] ; i++) {
		cond3 = !q && !s_q && comment == 0;
		if (flags->d)
			printf("[%i, %i]:Loop start '%c' (%i)\n", ln, col, file[i] > 31 ? file[i] : 0, file[i]);
		if (cond3 && bracket == 0 && file[i] == '\n') {
			if (flags->d)
				printf("[%i, %i]:Trying to find function's name\n", ln, col);
			bu = get_function_name(file + i, flags, mistakes, ln + 1, path);
			if (flags->d)
				printf("Got %p (%s)\n", bu, bu == 0 ? "?" : bu);
			if (bu != 0) {
				free(fct_name);
				fct_name = bu;
				verif_fct_name(bu, flags, path, mistakes);
			}
		} else if (cond3 && file[i] == '\n' && flags->i_caps) {
	        	if (flags->d)
				printf("[%i, %i]:Trying to find used function name\n", ln, col);
			bu = get_name(file + i, flags);
			if (flags->d)
				printf("Got %p (%s)\n", bu, bu == 0 ? "?" : bu);
			if (bu != 0) {
				verif_fct_used(bu, flags, path, mistakes, words, fct, ln, fct_name);
				free(bu);
			}
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
				for (start = i; file[start] != '\n'; start--);
				for (end = start + 1; file[end] != '\n' && file[end]; end++);
				if (flags->v) {
					bu = malloc(end - start + 10);
					sub_strings(file, start + 1, end, bu);
					mistake_line(strlen(words[k]), bu, col, ln);
					free(bu);
				}
				mistakes[11]++;
			}
		}
		if ((cond3 && file[i] < 32 && !space(file[i])) || file[i] == 127) {
		        cond = file[i] == '\t' ? 8 - col % 8 : 1;
			display_path(path);
			printf(" [\033[32;1m%i\033[0m:\033[32;1m%i\033[0m]", ln, col - cond);
			printf(" \033[0m%s\033[31;1m%s\033[0m%s",  fct_name ? fct : "", fct_name ? fct_name : "", fct_name ? "' " : "");
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
			if (flags->f) {
				printf("\033[0m: '\033[31;1m%s\033[0m' ", buffer);
				printf("(ASCII \033[31;1m%i\033[0m) égaré dans le programme \n", (unsigned char)file[i]);
			} else {
			        printf("\033[0m: Trailing '\033[31;1m%s\033[0m' (ASCII \033[31;1m%i\033[0m)\n", buffer, (unsigned char)file[i]);
			}
			for (start = i; start >= 0 && file[start] != '\n'; start--);
			for (end = start + 1; file[end] != '\n' && file[end]; end++);
			if (flags->v) {
				bu = malloc(end - start + 10);
				sub_strings(file, start + 1, end, bu);
				mistake_line(cond, bu,  col, ln);
				free(bu);
			}
			mistakes[19]++;
		}
		if (cond3 && file[i] == ';' && file[i - 1] == ' ') {
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
			for (start = i; file[start] != '\n'; start--);
			for (end = start + 1; file[end] != '\n' && file[end]; end++);
			if (flags->v) {
				bu = malloc(end - start + 10);
				sub_strings(file, start + 1, end, bu);
				mistake_line(2, bu, col - 1, ln);
				free(bu);
			}
			mistakes[21]++;
		}
		if (file[i] == '\n') {
			if (col > 80) {
                                if (flags->d)
                                        printf("Too long line %i\n", col);
				display_path(path);
				printf(" [line:\033[32;1m%i\033[0m]", ln);
				printf(" \033[0m%s\033[31;1m%s\033[0m%s",  fct_name ? fct : "", fct_name ? fct_name : "", fct_name ? "' " : "");
                                if (flags->f)
                                        printf("\033[0m: ligne trop longue ");
                                else
                                        printf("\033[0m: too long line ");
                                printf("(\033[31;1m%i\033[0m)\n", col);
				mistakes[5]++;
				if (flags->v) {
					for (start = i - 1; file[start] && file[start] != '\n'; start--);
					bu = malloc(i - start + 1);
					sub_strings(file, start + 1, i, bu);
                                        mistake_line(col - 80, bu, 80, ln);
					free(bu);
				}
                        }
			if (bracket > 0)
				line++;
			ln++;
			check_ind(file, mistakes, path, ln, i, flags, fct_name, fct);
			col = 0;
			begin_of_line = 1;
			declaring_var = 1;
			comment = comment == 1 ? 0 : comment;
		} else if(!space(file[i]))
			begin_of_line =	0;
		if (file[i] == '(' || file[i] == '{' || file[i] == '}')
			declaring_var = 0;
		if (cond3 && !declaring_var && !begin_of_line && space(file[i]) && space(file[i + 1])) {
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
			for (start = i; file[start] != '\n'; start--);
			for (end = start + 1; file[end] != '\n' && file[end]; end++);
			if (flags->v) {
				bu = malloc(end - start + 10);
				sub_strings(file, start + 1, end, bu);
				mistake_line(cond, bu,  col, ln);
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
				display_path(path);
				printf(" [\033[32;1m%i\033[0m:\033[32;1m%i\033[0m]", ln, col);
				printf(" \033[0m%s\033[31;1m%s\033[0m%s",  fct_name ? fct : "", fct_name ? fct_name : "", fct_name ? "' " : "");
				if (flags->f) {
					printf("\033[0m: commentaire dans une ");
					printf(" fonction\n");
				} else
					printf("\033[0m: comment in a function\n");
				mistakes[8]++;
				for (start = i; file[start] != '\n'; start--);
				for (end = start + 1; file[end] != '\n' && file[end]; end++);
				if (flags->v) {
					bu = malloc(end - start + 10);
					sub_strings(file, start + 1, end, bu);
					mistake_line(2, bu, col, ln);
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
					display_path(path);
					printf(" [\033[32;1m%i\033[0m:\033[32;1m%i\033[0m]", ln, col + 1);
					printf(" \033[0m%s\033[31;1m%s\033[0m%s",  fct_name ? fct : "", fct_name ? fct_name : "", fct_name ? "' " : "");
					if (flags->f)
						printf("\033[0m: fonction trop longue ");
					else
						printf("\033[0m: too long function ");
					printf("(\033[31;1m%i\033[0m)%s", line, flags->v ? "\n\n\n" : "\n");
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
		display_path(path);
		if (flags->f) {
			printf(" : Plus de 5 fonctions");
			printf(" dans un fichier (\033[31;1m%i\033[0m)%s", function, flags->v ? "\n\n\n" : "\n");
		} else {
			printf(" : More than 5 functions");
			printf(" in a single file (\033[31;1m%i\033[0m)%s", function, flags->v ? "\n\n\n" : "\n");
		}
		mistakes[1] += function - 5;
	}
	if (flags->d)
		printf("End of buffer\n");
}

void	scan_c_file(char *path, int *mistakes, char const **key_words, flag *flags)
{
	char	*file_content;

	file_content = load_file(path);
	if (!file_content)
		return;
	find_long_fct(file_content, mistakes, path, key_words, flags);
	if (flags->d)
		printf("File %s scanned !\n\n", path);
        free(file_content);
}

void	scan_h_file(char *path, int *mistakes, flag *flags)
{
	char	*file_content;

	file_content = load_file(path);
	if (!file_content)
		return;
	find_long_fct(file_content, mistakes, path, (char const *[2]){0, 0}, flags);
	free(file_content);
}
