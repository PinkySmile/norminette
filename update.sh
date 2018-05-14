#!/bin/bash
cd $HOME/norminette
if [ $(git pull | wc -l) != 1 ]
then
    make re
    echo "coping nominette to /bin/norminette"
    sudo cp $HOME/norminette/norminette /bin/
    echo "adding manpage"
    sudo cp $HOME/norminette/manpage.1.gz /usr/local/share/man/man1/norminette.1.gz
fi
