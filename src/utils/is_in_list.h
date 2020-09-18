/*
** EPITECH PROJECT, 2020
** norminette
** File description:
** is_in_list.h
*/

#ifndef NORMINETTE_IS_IN_LIST_H
#define NORMINETTE_IS_IN_LIST_H


#include <stdbool.h>
#include "../data/style_errors.h"

bool is_in_list(const char **list, const char *value);
bool is_mistake_ignored(const enum mistake_name_e *list,\
enum mistake_name_e value);


#endif //NORMINETTE_IS_IN_LIST_H
