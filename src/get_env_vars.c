/*
** EPITECH PROJECT, 2018
** get_env_var
** File description:
** Get an environnement var and returns it
*/

#include <stdlib.h>
#include <string.h>
#include "functions.h"

char	**split(char *var, char c)
{
	char	**tab = 0;
	int	nb = 2;
	int	start = 0;
	int	end = 0;

	for (int i = 0; var[i]; i++)
		if (var[i] == c)
			nb++;
	tab = malloc(sizeof(*tab) * nb);
	for (nb = 0; var[end]; end++)
		if (var[end] == c) {
			tab[nb] = malloc(end - start + 2);
			tab[nb] = sub_strings(var, start, end - 1, tab[nb]);
			nb++;
			start = end + 1;
		}
	tab[nb] = malloc(end - start + 2);
	tab[nb] = sub_strings(var, start, end, tab[nb]);
	tab[nb + 1] = 0;
	return (tab);
}

bool	match(char *str, char *str2);

int	get_env_var_pos(char **env, char *var_name)
{
	for (int i = 0; env[i]; i++)
		if (match(var_name, env[i]))
			return (i);
	return (-1);
}

char	*get_env_var(char **env, char *var_name)
{
	int	end = 0;
	int	start = 0;
	char	*buffer = 0;

	for (int i = 0; env[i]; i++)
		if (match(var_name, env[i])) {
			end = strlen(env[i]);
			start = strlen(var_name) + 1;
			buffer = malloc(end - start + 2);
			return (sub_strings(env[i], start, end, buffer));
		}
	return (strdup(""));
}
