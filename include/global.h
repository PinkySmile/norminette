/*
** EPITECH PROJECT, 2017
** global
** File description:
** My globals vars
*/

const char	*style_names[] = {
	"O1",			/*garbage files					*/
	"O3",			/*5 fcts					*/
	"O4",			/*files names					*/
	"G1",			//epi header
	"G2",			//empty lines between fcts
	"F2",			/*function's name invalid			*/
	"F3",			/*too long line					*/
	"F4",			/*too long function				*/
	"F5",			//fct > 4 args
	"F6",			/*comment in fct				*/
	"L1",		//	//+1 action per line
	"L2",			//indentation
	"L3",			/* space after key words and operators		*/
	"L4",			//brackets
	"L5",		//	//x vars declared on 1 line or in prog
	"L6",		//	//line break after vars declarations
	"V1",		//	//nom de types
	"V3",		//	//pointers declaration
	"C1",			//if depth > 3 or if forest
	"C3",		//	/*goto						*/
	"H1",			//bad seperation between header and source
	"implicit_L001",	/*trailing space				*/
	"implicit_L003",	//trailing empty line
	"implicit_T007",	/*semicolon isolated				*/
	"implicit_T010",	/*l and o					*/
	"implicit_F001",	/*forbidden fcts				*/
	"implicit_F002",	//too long file name
	0
};

const char	*style_description[] = {
	"content of the delivery folder should contain only files required for compilation",
	"more than 5 function in a single file",
	"your file name must follow the snake_case convention, be clear, precise, explicit, and unambiguous",
	"you must start your source code with a correctly formatted Epitech standard header",
	"one and only one empty line should separate the implementations of functions",
	"function should be in english, according to the snake_case convention",
	"too long line",
	"too long function",
	"a function should not need more than 4 arguments and taking no parameters should take void as argument in the function declaration.",
	"comment inside a function.",
	"a line correspond to more than one statement",
	"bad indentation on start of a line",
	"misplaced space(s)",
	"curly brackets misplaced",
	"",
	"",
	"",
	"nested conditonal branchings with a depth of 3 or more should be avoided and an if block should not contain more than 3 branchings",
	"",
	"goto keyword is forbidden",
	"bad separation between source file and header file",
	"trailing space",
	"leading or trailing empty line",
	"semicolon is isolated from other tokens",
	"identifier should not be composed of only 'l' and 'o'",
	"banned functions used",
	"bad file or directory name",
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
	0,
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
	2,
	1,
	2,
	0,
	0,
	0,
	2,
	2
};
