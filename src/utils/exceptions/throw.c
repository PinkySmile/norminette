/*
** EPITECH PROJECT, 2020
** norminette
** File description:
** throw.c
*/

#include <malloc.h>
#include "../assert.h"
#include "../exceptions.h"

void __throw(const char *name, const char *desc)
{
	__alloc_exception();
	__exceptionsStack.last_exception->name = strdup(name);
	__exceptionsStack.last_exception->desc = strdup(desc);
	__rethrow();
}

void __rethrow(void)
{
	unsigned current_buffer = __exceptionsStack.buffers.current_buffer;
	unsigned buf = --__exceptionsStack.buffers.current_buffer;

	assert(current_buffer != 0, "Not in a try");
	raise(SIGTRAP);
	longjmp(__exceptionsStack.buffers.buffers[buf], true);
}

void __endtry(void)
{
	unsigned current_buffer = __exceptionsStack.buffers.current_buffer;

	assert(current_buffer != 0, "Not in a try");
	__exceptionsStack.buffers.current_buffer--;
	if (__exceptionsStack.last_exception) {
		free(__exceptionsStack.last_exception->name);
		free(__exceptionsStack.last_exception->desc);
	}
	free(__exceptionsStack.last_exception);
	__exceptionsStack.last_exception = NULL;
}