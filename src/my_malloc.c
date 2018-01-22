/*
** EPITECH PROJECT, 2018
** my_malloc
** File description:
** Mallocs and verify it
*/

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stacktrace.h>

void	*my_malloc(int size)
{
	void	*ptr = 0;

	addStackTraceEntry("my_malloc", "i", "size", size);
	ptr = malloc(size);
	if (ptr == 0) {
		printf("\nError: Couldn't malloc %iB. Aborting.", size);
		raise(SIGABRT);
		exit(84);
	}
	delStackTraceEntry();
	return (ptr);
}
