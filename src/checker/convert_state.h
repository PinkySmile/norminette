/*
** EPITECH PROJECT, 2020
** norminette
** File description:
** convert_state.h
*/

#ifndef NORMINETTE_CONVERT_STATE_H
#define NORMINETTE_CONVERT_STATE_H


#include "../output/error_reporting.h"

struct checker_state_s;
made_style_error_t convert_state(const struct checker_state_s *state,
const char *file, enum mistake_name_e error, long special_value);


#endif //NORMINETTE_CONVERT_STATE_H
