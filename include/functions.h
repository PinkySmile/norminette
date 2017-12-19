/*
** EPITECH PROJECT, 2017
** functions header
** File description:
** Contains all functions prototypes
*/

#include "structs.h"
#include <signal.h>

#ifndef _FUNCTION_H_
#define _FUNCTION_H_

flag	get_flags(int argc, char **args);
void	scan_folder(char *path, flag *flags, int *mistakes);
void	scan_file(char *path, flag *flags, int *mistakes);
int	is_dir(char *path);
void	scan_c_file(char *path, int *mistakes, char const **key_words, flag *flags);
void	scan_h_file(char *path, int *mistakes, flag *flags);
void	display_result(int *mistakes, flag *flags);
void	catch_sig(int sig_ID, siginfo_t *infos, void *ptr);
void	display_path(char *path);

#endif
