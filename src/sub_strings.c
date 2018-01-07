/*
** EPITECH PROJECT, 2017
** sub_strings
** File description:
** take a part of a given string
*/

#include "my.h"
#include "stacktrace.h"

char	*sub_strings(char const *str, int start, int end, char *to_return)
{
	int pos = start > 0 ? -start : 0;
	int i = start > 0 ? start : 0;
	int real_start = i;

	addStackTraceEntry("sub_strings", "piip", "str", str, "start", start, "end", end, "to_return", to_return);
        for (; i < end && str[i]; i++) {
		to_return[pos + i] = str[i];
	}
        to_return[i - real_start] = 0;
	delStackTraceEntry();
	return (to_return);
}
