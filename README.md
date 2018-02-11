# USAGE :
	/home/andgel/norminette/norminette [-vcfunahd] [-I<path>] [folders/files]

## DESCRIPTION :
	-a :		Enables v, u, b, I. and l options (like -vbunlI.

	-b :		Displays all banned functions found (useless without -I)

	-c :		Disables colors

	-d :		Debug option (don't use it)

	-f :		Change the main language to french

	-l :		Automaticaly answer yes for large files (> 1 Mo)

	-h :		Display this help page

	-n :		Displays the scanned files' names

	-s :		Automaticaly answer no for large files (> 1 Mo)
			Overrides -l

	-u :		Finds unseless files and invalid file names

	-v :		Displays the entire line and where the mistake
			is in it

	-I<path> : 	Using the I flag enables the forbidden functions
			checking in .c files. Using this flag transform the remaining
			string into the path of the folder or file which contains
			allowed functions. The program will save every function
			declared in those files/folders (only .c and .h files)
			and use them as only allowed functions. That means that all
			functions which are not declared in these files will be
			the forbidden functions. All the allowed system calls have
			have to be declared in a .h or .c file. No need to declare
			the functions properly. You juste have to follow this exemple
					void function();
			Note : severals -I can be used at the same if you have many include
			and source folders with, for exemple, the CSFML
			CSMFL's includes are in the folder /usr/local/include/SFML.
			For graphical projects use -I/usr/local/include/SFML .

## EXEMPLES :
	/home/andgel/norminette/norminette :
		Launch a basic test on the current folder

	/home/andgel/norminette/norminette src test.c :
		Launch a basic test in the folder 'src' and on the file 'test.c'

	/home/andgel/norminette/norminette -vfIinclude -I/usr -I../sys.h
		Launch the program in verbose mode, in french
		with forbidden function wich are not found neither in the folders 'include' and '/usr' nor in the file '../sys.h'

## RETURN VALUES :
	If no mistakes are found, the program exit with code 0.
	If one or many mistakes are found, the program eit with code 1.

## REPORT A BUG :
	If you find a bug, first, update  the program  (Use the
	'update.sh'  in  the  repository or, if  you  used  the
	installation script, <your alias>-update). If it is not
	yet patched, run the 'debug.sh' (or <your alias>-debug)
	with,  as argument, the  file  which caused  the bug to
	happen. Send me, then, the  scan.log file (you can join
	the source  file too) at  "andgel.halley@epitech.eu".
	Explain briefly in the mail what happened and  I'll fix
	as fast as I can !
	You  can also send it on discord or
	open a new issue ticket on github.

	Note : No need to launch  in debug mode if  it's just a
	display problem (spelling mistake, ...).
	The given scripts (update.sh, debug.sh) will only work
	if the program is stored in ~/norminette. You can also
	modify  the scripts  to make them  work with your  own
	path
	You can also send me ideas by mail !

## UPDATES :
	if you want to get notified on new updates, you can join
	this server https://discord.gg/RgDbJDW