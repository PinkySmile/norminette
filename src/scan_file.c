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

char	*load_file(char *path)
{
	int		fd = 0;
	char		*buffer;
	struct stat	info;

	if (stat(path, &info) < 0) {
		perror("");
		exit(84);
	}
	fd = open(path, O_RDONLY);
	if (fd <= 0) {
		perror("");
		exit(84);
	}
	buffer = malloc(info.st_size + 1);
	read(fd, buffer, info.st_size);
	buffer[info.st_size] = 0;
	close(fd);
	return (buffer);
}

void	mistake_line(int size, char *line, int col, int ln)
{
	int	col_c = 1;
	int	chars = 0;
	int	ik = 0;

	if (col == 0)
		col = 1;
	chars = printf("[%i:%i]-->", ln, col);
	for (int i = 0; line[i]; i++) {
		if (line[i] != '\t')
			col_c++;
		else
			col_c = (col_c + 8) - (col_c % 8);
		if (col_c > col && col_c <= col + size)
			printf("\033[95;1m");
		printf("%c\033[0m", line[i]);
	}
	printf("\n");
	for (int i = 1; i < chars; i++)
		printf(" ");
	for (int jo = 0; jo < col && line[ik]; jo++) {
		if (line[ik] != '\t')
			printf(" ");
		else {
			jo = jo + 8 - (jo % 8) - 1;
			printf("\t");
		}
		ik++;
	}
	printf("\033[95;1m^");
	for (int jo = 0; jo < size - 1; jo++)
		printf("~");
	printf("\n\033[0m");
}

void	find_long_lines(char *file, int *mistakes, char *path, flag *flags)
{
	int	ln = 1;
	int	col = 0;
	int	character = 0;
	char	*buffer = 0;
	int	line_beg = 0;

	if (flags->d)
		printf("Finding to long lines\n");
        for (int i = 0; file[i]; i++) {
		col++;
		if (flags->d)
			printf("[%i, %i]:Loop start\n", ln, col);
		if (file[i] == '\t') {
			col += 7;
			character +=  8 - (col % 8);
			col -= col % 8;
			if (flags->d)
				printf("Found \\t : [%i, %i]\n", ln, col);
		} else if (file[i] == '\n') {
			col--;
			if (flags->d)
				printf("Found \\n : [%i, %i]\n", ln, col);
			if (col > 80) {
				if (flags->d)
					printf("Too long line %i\n", col);
				printf("\033[31;1m%s [line %i]", path, ln);
				if (flags->f)
					printf("\033[0m : ligne trop longue ");
				else
					printf("\033[0m : too long line ");
				printf("(\033[31;1m%i\033[0m)\n", col);
				buffer = malloc(col + 1);
				sub_strings(file, line_beg, i, buffer);
				if (flags->v)
					mistake_line(col - 80, buffer, 80, ln);
				mistakes[5]++;
				free(buffer);
			}
			line_beg = i + 1;
			if (flags->d)
				printf("Set begin of line %i\n", line_beg);
			ln++;
			character = 0;
			col = 0;
		}
	}
	if (col > 80) {
		printf("\033[31;1m%s [line %i]", path, ln);
		if (flags->f)
			printf("\033[0m : ligne trop longue");
		else
			printf("\033[0m : too long line ");
		printf("(\033[31;1m%i\033[0m)\n", col);
		mistakes[5]++;
		buffer = malloc(col + 1);
		sub_strings(file, line_beg, col + line_beg, buffer);
		if (flags->v)
			mistake_line(col - 80, buffer, 81, ln);
        	free(buffer);
	}
	if (flags->d)
		printf("End of buffer\n");
}

void	check_ind(char *file, int *mistakes, char *path, int ln, int i, flag *flags)
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
			printf("[%i]:Loop start\n", col);
		if (file[jl] == ' ') {
			if (flags->d)
				printf("[%i]:Found a space\n", col);
			mistakes[10]++;
			printf("\033[31;1m%s [%i:%i]", path, ln, col);
			if (flags->f)
				printf("\033[0m : erreur d'indentation\n");
			else
				printf("\033[0m : bad indentation\n");
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
			printf("\033[31;1m%s [%i:0]", path, ln);
			if (flags->f)
				printf("\033[0m : erreur d'indentation (ligne vide)\n");
			else
				printf("\033[0m : bad indentation (empty line)\n");
			if (flags->v) {
				bu = malloc(i + 1);
				sub_strings(file, i + 1, i - jl, bu);
			        mistake_line((jl - i - 1) * 8, bu, 0, ln);
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
			printf("[%i, %i]:Loop start '%c (%i)'\n", ln, col, file[i], file[i]);
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
				printf("\033[31;1m%s [%i:%i]", path, ln, col + 1);
				if (flags->f) {
					printf("\033[0m : espace manquant ");
					printf("après le mot clé '%s'\n", words[k]);
				} else {
					printf("\033[0m : space missing after ");
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
		if (cond3 && file[i] == ';' && file[i - 1] == ' ') {
		        printf("\033[31;1m%s [%i:%i]", path, ln, col + 1);
			if (flags->f) {
				printf("\033[0m : Point virgule isolé ");
				printf("des autres éléments\n");
			} else {
				printf("\033[0m : Semicolon isolated from ");
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
			if (bracket > 0)
				line++;
			ln++;
			check_ind(file, mistakes, path, ln, i, flags);
			col = 0;
			begin_of_line = 1;
			declaring_var = 1;
			comment = comment == 1 ? 0 : comment;
		} else if(!space(file[i]))
			begin_of_line =	0;
		if (file[i] == '(' || file[i] == '{' || file[i] == '}')
			declaring_var = 0;
		if (cond3 && !declaring_var && !begin_of_line && space(file[i]) && space(file[i + 1])) {
		        printf("\033[31;1m%s [%i:%i]", path, ln, col - cond);
			cond = file[i] == '\t' ? 8 - col % 8 : 1;
			if (flags->f) {
				bu = file[i] == ' ' ? "Espace" : bu;
				bu = file[i] == '\t' ? "Tabulation" : bu;
				printf("\033[0m : %s égaré", bu);
				printf(" dans le programme \n");
			} else {
				bu = file[i] == ' ' ? "space" : bu;
				bu = file[i] == '\t' ? "tab" : bu;
				printf("\033[0m : Trailing %s\n", bu);
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
	        if (bracket > 0 && cond3) {
			if (flags->d) {
				printf("[%i, %i]:Searching for comments.", ln, col);
				printf(" Found '");
				sub_strings(file, i, i + 2, buffer);
				my_showstr(buffer);
				printf("'\n");
			}
			if (file[i] == '/' && (file[i + 1] == '/' || file[i + 1] == '*')) {
				printf("\033[31;1m%s [%i:%i]", path, ln, col);
				if (flags->f) {
					printf("\033[0m : commentaire dans une ");
					printf(" fonction\n");
				} else
					printf("\033[0m : comment in a function\n");
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
			if (!bracket) {
				if (flags->d)
					printf("[%i, %i]:New function found\n", ln, col);
				function++;
				line--;
				if (line > 20) {
					printf("\033[31;1m%s [line %i]", path, ln - line);
					if (flags->f)
						printf("\033[0m : fonction trop longue");
					else
						printf("\033[0m : too long function ");
					printf("(\033[31;1m%i\033[0m)\n", line);
					mistakes[6]++;
				}
				line = 0;
        		}
		}
		if (file[i] != '\t')
			col++;
		else
			col = (col + 8) - (col % 8);
	}
	if (function > 5) {
		if (flags->f) {
			printf("\033[31;1m%s\033[0m : Plus de 5 fonctions", path);
			printf(" dans un fichier (\033[31;1m%i\033[0m)\n", function);
		} else {
			printf("\033[31;1m%s\033[0m : More than 5 functions", path);
			printf(" in a single file (\033[31;1m%i\033[0m)\n", function);
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
	find_long_lines(file_content, mistakes, path, flags);
	if (flags->d)
		printf("Tracking other styles errors\n");
	find_long_fct(file_content, mistakes, path, key_words, flags);
	if (flags->d)
		printf("File %s scanned !\n\n", path);
        free(file_content);
}

void	scan_h_file(char *path, int *mistakes, flag *flags)
{
	char	*file_content;

	file_content = load_file(path);
	find_long_lines(file_content, mistakes, path, flags);
	free(file_content);
}
