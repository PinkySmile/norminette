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
	return alloc_again(NULL, size);
}

void *alloc_again(void *old, size_t newSize)
{
	void *ptr = realloc(old, newSize);

	if (!ptr)
		throw(OutOfMemoryError, "Out of memory");
	return ptr;
}