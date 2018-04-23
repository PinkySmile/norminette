/*
** EPITECH PROJECT, 2017
** free_list
** File description:
** free the list
*/

#include <stdlib.h>
#include "structs.h"

void	free_b_fct_list(list_t *list)
{
	list_t	*prev = 0;

	if (list == 0)
		return;
	for (; list->prev; list = list->prev);
	for (; list->next; list = list->next) {
		free(prev);
		prev = list;
		if (list->data)
			free(((b_fcts_t *)list->data)->name);
		free(list->data);
	}
	free(list->data);
	free(prev);
	free(list);
}

void	free_list(list_t *list)
{
	list_t	*prev = 0;

	if (list == 0)
		return;
	for (; list->prev; list = list->prev);
	for (; list->next; list = list->next) {
		free(prev);
		prev = list;
		free(list->data);
	}
	free(list->data);
	free(prev);
	free(list);
}
