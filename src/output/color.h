//
// Created by andgel on 04/09/2020
//

#ifndef NORMINETTE_COLOR_H
#define NORMINETTE_COLOR_H

#include <stdbool.h>

#ifdef _WIN32
enum color_e {
	BLACK,
	BLUE,
	GREEN,
	CYAN,
	RED,
	MAGENTA,
	BROWN,
	LIGHTGRAY,
	DARKGRAY,
	LIGHTBLUE,
	LIGHTGREEN,
	LIGHTCYAN,
	LIGHTRED,
	LIGHTMAGENTA,
	YELLOW,
	WHITE
};
#else
enum color_e {
	BLACK = 30,
	RED,
	GREEN,
	BROWN,
	BLUE,
	MAGENTA,
	CYAN,
	LIGHTGRAY,
	DARKGRAY = 90,
	LIGHTRED,
	LIGHTGREEN,
	YELLOW,
	LIGHTBLUE,
	LIGHTMAGENTA,
	LIGHTCYAN,
	WHITE,
};
#endif

enum properties_e {
	NORMAL = 0,
	BOLD = 1U << 0U,
	DARK = 1U << 1U,
	ITALIC = 1U << 2U,
	UNDERLINED = 1U << 3U,
	BLINK = 1U << 4U,
	FG_BG_INVERTED = 1U << 6U,
	TEXT_HIDDEN = 1U << 7U,
	CROSSED = 1U << 8U,
};

void set_output_properties(unsigned bg, unsigned fg, unsigned properties);

#endif //NORMINETTE_COLOR_H
