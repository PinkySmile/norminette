/*
** EPITECH PROJECT, 2017
** compare_strings.c
** File description:
** Compare to strings return 1 if same or 0
*/

#include <string.h>
#include "stacktrace.h"

int	compare_strings(char *str1, char *str2)
{
	int	result;

	addStackTraceEntry("compare_strings", "pp", "str1", str1, "str2", str2);
	result = strcmp(str1, str2) == 0;
	delStackTraceEntry();
	return (result);
}
