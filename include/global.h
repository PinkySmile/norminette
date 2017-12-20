/*
** EPITECH PROJECT, 2017
** global
** File description:
** My globals vars
*/

const char	*style_names[] = {
	"O1",			/*0  : garbage files				*/
	"O3",			/*1  : > 5 fcts					*/
	"O4",			/*2  : files names				*/
	"G1",			//3  : epi header
	"G2",			//4  : empty lines between fcts
	"F3",			/*5  : too long line				*/
	"F4",			/*6  : too long function			*/
	"F5",			//7  : fct > 4 args
	"F6",			/*8  : comment in fct				*/
	"L1",			//9  : +1 action per line
	"L2",			//10 : indentation
	"L3",			/*11 : space after key words and operators	*/
	"L4",			//12 : brackets
	"L5",			//13 : 
	"L6",			//14 : 
	"V3",			//15 : 
	"C1",			//16 : if depth > 3 or if forest
	"C3",			//17 : 
	"H1",			//18 : bad seperation between header and source
	"implicit_L001",	//19 : trailing space
	"implicit_L003",	//20 : trailing empty line
	"implicit_T007",	//21 : semicolon isolated
	"implicit_T010",	//22 : l or o 
	"V1",			//23 :
	"F2",			//24 : function's name invalid
	"implicit_F001",	//25 : forbidden fcts
	0
};

const char	*style_description[] = {
	"content of the delivery folder should contain only files required for compilation",
	"more than 5 function in a single file",
	"your file name must follow the snake_case convention, be clear, precise, explicit, and unambiguous",
	"you must start your source code with a correctly formatted Epitech standard header",
	"one and only one empty line should separate the implementations of functions",
	"too long line",
	"too long function",
	"a function should not need more than 4 arguments and taking no parameters should take void as argument in the function declaration.",
	"comment inside a function.",
	"a line correspond to more than one statement",
	"bad indentation on start of a line",
	"operators should be isolated by spaces and a space should follow 'if', 'for', 'return' and 'while'",
	"curly brackets misplaced",
	"",
	"",
	"",
	"nested conditonal branchings with a depth of 3 or more should be avoided and an if block should not contain more than 3 branchings",
	"",
	"bad separation between source file and header file",
	"trailing space",
	"leading or trailing empty line",
	"semicolon is isolated from other tokens",
	"identifier should not be composed of only 'l' and 'o'",
	"",
	"function should be in english, according to the snake_case convention",
	"forbiden functions used",
	0
};

const char	*key_words[] = {
	"while",
	"return",
	"if",
	"else",
	"for",
	"switch",
	0
};

const int	style_type[] = {
	2,
	2,
	2,
	2,
	1,
	2,
	2,
	2,
	1,
	2,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	2,
	0,
	0,
	0,
	0,
	2,
	2,
	2
};
