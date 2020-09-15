/*
** EPITECH PROJECT, 2020
** norminette
** File description:
** alloc.h
*/

#ifndef NORMINETTE_ALLOC_H
#define NORMINETTE_ALLOC_H

#include <stddef.h>

void *alloc(size_t size);
void *alloc_again(void *old, size_t newSize);

#endif //NORMINETTE_ALLOC_H
