/*
** EPITECH PROJECT, 2020
** norminette
** File description:
** state.h
*/

#ifndef NORMINETTE_STATE_H
#define NORMINETTE_STATE_H


typedef struct source_checker_state_s {
	unsigned line;
	unsigned column;
	unsigned nb_fct;
	char *decl_name;
	const char *decl_type;
} source_checker_state_t;


#endif //NORMINETTE_STATE_H
