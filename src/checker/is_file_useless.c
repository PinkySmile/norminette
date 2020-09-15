/*
** EPITECH PROJECT, 2020
** norminette
** File description:
** is_file_useless.c
*/

#include "is_file_useless.h"
#include "../utils/file_types.h"

bool is_file_useless(const char *path)
{
	return !is_reg_file(path);
}