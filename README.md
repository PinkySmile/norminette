# USAGE:
       norminette [--update] [-vcfunahd] [-I <path>] [folders/files]

# DESCRIPTION:
       -U --update
              Updates from the repository stored in ~/norminette (will ask for sudo password)

       -a --all
              Enables v, u, b, I . and l options (like -vbunlI.)

       -b --banned-fct-list
              Displays all banned functions found (useless without -I)

       -c --colorless
              Disables colors

       -d --debug
              Debug option (don't use it)

       -f --french
              Change the main language to french

       -i --indent=SIZE
              Change  the  number of spaces required to achieve a level of indentation. (Default:
              8). Note that if the -A is not specified, only tabulation characters will not trig‐
              ger a bad indentation.

       -l --large
              Automaticaly answer yes for large files (> 1 Mo)

       -h --help
              Display this help page

       -n --name
              Displays the scanned files' names

       -s --small
              Automaticaly answer no for large files (> 1 Mo). Overrides -l

       -t --traceback
              Enables the stacktrace

       -u --useless-files
              Finds useless files and invalid file names

       -v --verbose
              Displays the entire line and where the mistake is in it

       -A --accept-space-indent
              Accept space as indentation

       -T --tab-size=SIZE
              Change the size of a tab character (default: 8)

       -I <path> --include=<path>
              Using  the  I flag enables the forbidden functions checking in .c files. Using this
              flag transform the remaining string into the path of the folder or file which  con‐
              tains  allowed  functions.  The  program will save every function declared in those
              files/folders (only .c and .h files) and use them as only allowed  functions.  That
              means  that all functions which are not declared in these files will be the forbid‐
              den functions. All the allowed system calls have to be declared in a .h or .c file.
              No need to declare the functions properly. You juste have to follow this exemple
              void function();
              Note  :  severals  -I  can  be used at the same if you have many include and source
              folders  with,  for  exemple,  the  CSFML  CSMFL's  includes  are  in  the   folder
              /usr/local/include/SFML.

# EXEMPLES:
       norminette
              Launch a basic test on the current folder

       norminette src test.c
              Launch a basic test in the folder 'src' and on the file 'test.c'

       norminette -vfI include -I /usr -I ../sys.h
              Launch  the program in verbose mode, in french with forbidden function wich are not
              found neither in the folders 'include' and '/usr' nor in the file '../sys.h'

# RETURN VALUES:
       If no mistakes are found, the prograam exit with code 0.
       If one or many mistakes are found, the program exit with code 1

# REPORT A BUG:
       If you find a bug, first, update  the program  (Use the 'update.sh'  in   the   repository
       or,  if   you   used   the  installation  script,  <your  alias>-update). If it is not yet
       patched, run the 'debug.sh' (or <your alias>-debug) with,  as argument, the   file   which
       caused   the  bug  to  happen.  Send me, then, the  scan.log file (you can join the source
       file too) at  "andgel.halley@epitech.eu".
       Explain briefly in the mail what happened and  I'll fix as fast as I can !
       You  can also send it on discord or open a new issue ticket on github.
       Note : No need to launch  in debug mode if  it's just a display problem (spelling mistake,
       ...).
       The  given  scripts  (update.sh,  debug.sh)  will  only  work  if the program is stored in
       ~/norminette. You can also modify  the scripts  to make them  work with your  own path
       You can also send me ideas by mail !

# UPDATE:
       If you want to get notified on new updates, you can join this discord server :
       https://discord.gg/RgDbJDW

# CHANGELOG:
	1.2:
		- Added option -T to control tab size
		- Added option -i to control indentation size
		- Added option -A to accept spaces as valid indentation characters
	1.1.1:
		- Added French manpage
	1.1:
		- Improved trailing spaces detection
		- Added long versions of arguments
	1.0:	Release