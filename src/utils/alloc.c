/*
** EPITECH PROJECT, 2020
** norminette
** File description:
** alloc.c
*/

#include <malloc.h>
#include "exceptions.h"
#include "alloc.h"

void *alloc(size_t size)
{
	void *ptr = malloc(size);

	if (!ptr)
		throw(OutOfMemoryError, "Out of memory");
	return ptr;
}