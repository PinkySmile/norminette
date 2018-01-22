/*
** EPITECH PROJECT, 2018
** concat
** File description:
** Concatenate two strings together
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "functions.h"

char	*concat(char *str1, char *str2)
{
	char	*result = my_malloc(strlen(str1) + strlen(str2) + 1);

	strcpy(result, str1);
	strcat(result, str2);
	return (result);
}
