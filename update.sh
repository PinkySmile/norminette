#!/bin/bash
cd $HOME/norminette
if [ $(($(git pull | wc -l) * $([ "$1" == "--force" ]; echo -n $?))) != 1 ]
then
    if make; then
	echo "coping nominette to /bin/norminette"
	sudo cp $HOME/norminette/norminette /bin/
	echo "adding manpage"
	sudo cp $HOME/norminette/manpage.1.gz /usr/share/man/man1/norminette.1.gz
	sudo cp $HOME/norminette/manpage.1f.gz /usr/share/man/man1/norminette.1f.gz
    else
	echo "Error: Compilation failed"
    fi
fi
