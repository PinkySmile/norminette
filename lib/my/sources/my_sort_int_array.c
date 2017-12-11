/*
** EPITECH PROJECT, 2017
** my_sort_int_tab
** File description:
** sort an array of ints
*/

#include "my.h"

int	check_end(int *array, int size)
{
	for (int i = 0; i < size - 1; i++) {
		if (array[i] > array[i + 1]) {
			return (0);
		}
	}
	return (1);
}

void	my_sort_int_array(int *array, int size)
{
	int step = -1;
	int pos = 1;
	int end = 0;

	while (end == 0) {
		if (array[pos + step] * step < array[pos] * step) {
			my_swap(array + pos + step, array + pos);
		}
		if (pos > size - 3 || pos < 2) {
			step = -step;
			pos += step;
			end = check_end(array, size);
		} else {
			pos += step;
		}
	}
}
