/*
** EPITECH PROJECT, 2020
** norminette
** File description:
** throw.c
*/

#include <malloc.h>
#include "../exceptions.h"

void __throw(const char *name, const char *desc)
{
	__alloc_exception();
	__exceptionsStack.last_exception->name = name;
	__exceptionsStack.last_exception->desc = desc;
	__rethrow();
}

void __rethrow(void)
{
	unsigned buf = --__exceptionsStack.buffers.current_buffer;

	raise(SIGTRAP);
	longjmp(__exceptionsStack.buffers.buffers[buf], true);
}

void __endtry(void)
{
	__exceptionsStack.buffers.current_buffer--;
	free(__exceptionsStack.last_exception);
	__exceptionsStack.last_exception = NULL;
}