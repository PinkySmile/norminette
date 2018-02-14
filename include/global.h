/*
** EPITECH PROJECT, 2017
** global
** File description:
** My globals vars
*/

#include "structs.h"

const char	*key_words[] = {
	"while",
	"return",
	"if",
	"else",
	"for",
	"switch",
	0
};

const style_error	coding_style[] = {
	/*garbage files*/
	{
		"O1",
		"content of the delivery folder should contain only files required for compilation",
		2
	},
	/*5 fcts*/
	{
		"O3",
		"more than 5 function in a single file",
		2
	},
	/*files names*/
	{
		"O4",
		"your file name must follow the snake_case convention, be clear, precise, explicit, and unambiguous",
		2
	},
	/*epi header*/
	{
		"G1",
		"you must start your source code with a correctly formatted Epitech standard header",
		2
	},
	/*empty lines between fcts*/
	{
		"G2",
		"one and only one empty line should separate the implementations of functions",
		1
	},
	/*function's name invalid*/
	{
		"F2",
		"function should be in english, according to the snake_case convention",
		2
	},
	/*too long line*/
	{
		"F3",
		"too long line",
		2
	},
	/*too long function*/
	{
		"F4",
		"too long function",
		2
	},
	/*fct > 4 args*/
	{
		"F5",
		"a function should not need more than 4 arguments and taking no parameters should take void as argument in the function declaration.",
		2
	},
	/*comment in fct*/
	{
		"F6",
		"comment inside a function.",
		1
	},
	/*+1 action per line*/
	{
		"L1",
		"a line correspond to more than one statement",
		2
	},
	/*indentation*/
	{
		"L2",
		"bad indentation on start of a line",
		1
	},
	/*space after key words and operators*/
	{
		"L3",
		"misplaced space(s)",
		1
	},
	/*brackets*/
	{
		"L4",
		"curly brackets misplaced",
		1
	},
	/*x vars declared on 1 line or in prog*/
	{
		"L5",
		"severals variables declared on the same line",
		1
	},
	//line break after vars declarations
	{
		"L6",
		"",
		1
	},
	//nom de types
	{
		"V1",
		"",
		2
	},
	//pointers declaration
	{
		"V3",
		"",
		1
	},
	//if depth > 3 or if forest
	{
		"C1",
		"nested conditonal branchings with a depth of 3 or more should be avoided and an if block should not contain more than 3 branchings",
		1
	},
	/*goto*/
	{
		"C3",
		"goto keyword is forbidden",
		1
	},
	//bad seperation between header and source
	{
		"H1",
		"bad separation between source file and header file",
		2
	},
	/*trailing space*/
	{
		"implicit_L001",
		"trailing space",
		0
	},
	//trailing empty line
	{
		"implicit_L003",
		"leading or trailing empty line",
		0
	},
	/*semicolon isolated*/
	{
		"implicit_T007",
		"semicolon is isolated from other tokens",
		0			
	},
	/*l and o*/
	{
		"implicit_T010",
		"identifier should not be composed of only 'l' and 'o'",
		0
	},
	/*banned fct*/
	{
		"explicit_F001",
		"banned functions used",
		2
	},
	//too long file name ?
	{
		"implicit_F002",
		"bad file or directory name",
		0
	},
	{
		0,
		0,
		0
	}
};
