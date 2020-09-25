/*
** EPITECH PROJECT, 2020
** norminette
** File description:
** recap.c
*/

#include "recap.h"
#include "../codes.h"
#include "../output/color.h"
#include "../output/easter_eggs.h"

static const char *strs[] = {
	"info",
	"minor",
	"major"
};
static const enum color_e cols[] = {
	CYAN,
	BROWN,
	RED
};

void show_error_count(unsigned count, int ind)
{
	set_output_properties(RESET, RED, BOLD);
	printf("\n%s", coding_style[ind].name);
	set_output_properties(RESET, RESET, BOLD);
	printf(" rule has been violated ");
	set_output_properties(RESET, RED, BOLD);
	printf("%u", count);
	set_output_properties(RESET, RESET, BOLD);
	printf(" time%s ", count > 1 ? "s" : "");
	set_output_properties(RESET, RESET, NORMAL);
	printf(": ");
	set_output_properties(RESET, LIGHTRED, NORMAL);
	printf("%s", coding_style[ind].desc);
}

void print_recap(unsigned score, unsigned err[3])
{
	for (int i = 0; i < 3; i++) {
		set_output_properties(RESET, cols[i], NORMAL);
		printf("%s", strs[i]);
		set_output_properties(RESET, RESET, NORMAL);
		printf(": ");
		set_output_properties(RESET, err[i] ? RED : GREEN, BOLD);
		printf("%i  ", err[i]);
	}
	set_output_properties(RESET, RESET, BOLD);
	printf("\nStyle mark");
	set_output_properties(RESET, RESET, NORMAL);
	printf(" : ");
	set_output_properties(RESET, score ? RED : GREEN, BOLD);
	printf("-%i\n", score);
}

int make_scan_recap(const checker_state_t *state)
{
	unsigned silenced = 0;
	unsigned err[3] = {0, 0, 0};
	unsigned score = 0;
	const int *pts = &state->args->infos_points;

	for (int i = 0; coding_style[i].name; i++)
		if (
			!is_mistake_ignored(state->args->ignored_mistakes, i) &&
			state->mistakes_counts[i]
		) {
			show_error_count(state->mistakes_counts[i], i);
			err[coding_style[i].type] += state->mistakes_counts[i];
		} else
			silenced += state->mistakes_counts[i];

	if (err[0] || err[1] || err[2])
		printf("\n\n");

	/*if (mistakes[FORBIDDEN_FCT_USED] != 0) {
		if (flags->b) {
			printf("\nBanned functions used :\n");
			print_list(flags->b_fcts, flags);
			printf("\n\n");
			free_b_fct_list(flags->b_fcts);
		} else
			printf("Re-run with -b to see a detailed list of all forbidden functions found.\n\n");
	}*/

	for (int i = 0; i < 3; i++)
		score += err[i] * pts[i];

	print_recap(score, err);
	set_output_properties(RESET, RESET, NORMAL);
	if (state->args->easter)
		puts EASTER_EGG_1;
	printf("%i lines scanned\n", state->lines_scanned);
	return score ? RETURN_SUCCESS : RETURN_ERRORS_FOUND;
}
