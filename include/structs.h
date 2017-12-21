/*
** EPITECH PROJECT, 2017
** structs header
** File description:
** Contains all structures
*/

#ifndef _STRUCTS_H_
#define _STRUCTS_H_

typedef struct list_s {
	void		*data;
	struct list_s	*next;
	struct list_s	*prev;
} list_t;

typedef struct {
	int	v;
	int	f;
	int	n;
	int	u;
	int	d;
	int	c;
	int	i_caps;
	int	no_big_files;
	list_t	*fcts;
} flag;

#endif
