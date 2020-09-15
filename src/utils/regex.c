/*
** EPITECH PROJECT, 2020
** norminette
** File description:
** regex.c
*/

#include <stddef.h>
#include <regex.h>
#include "regex.h"
#include "exceptions.h"

bool match_regex(const char *pattern, const char *str)
{
	char err_buffer[200];
	regex_t regex;
	int err = regcomp(&regex, pattern, REG_NOMATCH);

	if (err) {
		regerror(err, &regex, err_buffer, sizeof(err_buffer));
		throw(InvalidRegexException, err_buffer);
	}
	return regexec(&regex, str, 0, NULL, 0) == 0;
}