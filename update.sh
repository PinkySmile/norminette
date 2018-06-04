#!/bin/bash
cd $HOME/norminette
if [ $(($(git pull | wc -l) * $([ $1t == "--forcet" ]; echo -n $?))) != 1 ]
then
    if make re; then
	echo "coping nominette to /bin/norminette"
	sudo cp $HOME/norminette/norminette /bin/
	echo "adding manpage"
	sudo cp $HOME/norminette/manpage.1.gz /usr/share/man/man1/norminette.1.gz
	sudo cp $HOME/norminette/manpage.2.gz /usr/share/man/man2/norminette.2.gz
    else
	echo "Error: Compilation failed"
    fi
fi
