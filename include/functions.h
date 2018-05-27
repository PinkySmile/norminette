/*
1;5003;0c** EPITECH PROJECT, 2017
** functions header
** File description:
** Contains all functions prototypes
*/

#include "structs.h"
#include <signal.h>

#ifndef _FUNCTION_H_
#define _FUNCTION_H_

flag	get_flags(int argc, char **args, char **env, char ***dirs);
void	scan_folder(char *path, flag *flags, int *mistakes);
void	scan_file(char *path, flag *flags, int *mistakes, int force);
bool	is_dir(char *path);
void	scan_c_file(char *path, int *mistakes, char const **key_words, flag *flags);
void	scan_h_file(char *path, int *mistakes, flag *flags);
void	display_result(int *mistakes, flag *flags);
void	catch_sig(int sig_ID, siginfo_t *infos, void *ptr);
void	display_path(char *path);
void	free_list(list_t *list);
char	*load_file(char *path);
void	load_functions(char *path, flag *flags);
int	space(char c);
char	*find_path(char *path, char *name);
char	*get_name(char *file, flag *flags, int *col, char **end_ptr, int comment, _Bool q, _Bool s_q, _Bool declare);
int	is_file_c(char *path);
int	list_len(list_t *list);
int	char_valid(char c);
char	*get_prog_name();
int	*get_mistakes();
flag	*get_flags_var();
void	free_b_fct_list(list_t *list);
char	*int_to_str(int nbr);
char	*long_to_str(long nbr);
char	*double_to_str(double nbr);
int	get_nbrlen(int nbr);
char	*concat(char *str1, char *str2);
char	*my_putnbrbase(unsigned int nbr, char const *base);
void	*my_malloc(int size);
char	*get_env_var(char **env, char *var_name);
char	*sub_strings(char const *str, int start, int end, char *buffer);

#endif
