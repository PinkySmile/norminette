/*
** EPITECH PROJECT, 2020
** norminette
** File description:
** alloc.c
*/

#include <malloc.h>
#include <stdlib.h>
#include "../exceptions.h"

void __alloc_exception(void)
{
	if (!__exceptionsStack.last_exception)
		__exceptionsStack.last_exception =\
		malloc(sizeof(*__exceptionsStack.last_exception));

	if (!__exceptionsStack.last_exception) {
		puts("Out of memory");
		exit(EXIT_FAILURE);
	}
}

void __init_exceptions(void)
{
	if (!__exceptionsStack.buffers.nb_buffers)
		__alloc_new_buffer();
	__exceptionsStack.buffers.current_buffer = 1;
}

void __free_exceptions(void)
{
	free(__exceptionsStack.last_exception);
	__exceptionsStack.last_exception = NULL;

	free(__exceptionsStack.buffers.buffers);
	__exceptionsStack.buffers.nb_buffers = 0;
	__exceptionsStack.buffers.buffers = NULL;
}

void __alloc_new_buffer(void)
{
	unsigned current = __exceptionsStack.buffers.current_buffer;
	unsigned size = __exceptionsStack.buffers.nb_buffers;
	jmp_buf *ptr = __exceptionsStack.buffers.buffers;

	if (size <= current) {
		__exceptionsStack.buffers.nb_buffers++;
		ptr = realloc(
			__exceptionsStack.buffers.buffers,
			__exceptionsStack.buffers.nb_buffers * sizeof(*ptr)
		);
		if (!ptr) {
			puts("Out of memory");
			exit(EXIT_FAILURE);
		}
	}
	__exceptionsStack.buffers.current_buffer++;
	__exceptionsStack.buffers.buffers = ptr;
}