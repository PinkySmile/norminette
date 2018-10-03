#!/bin/bash
cd $HOME
if git clone https://github.com/Gegel85/norminette.git
then make -C norminette
     make -C norminette clean
     chmod 755 $HOME/norminette/update.sh
     echo "coping nominette to /bin/norminette"
     sudo cp $HOME/norminette/norminette /bin/
     echo "adding manpage"
     sudo cp $HOME/norminette/manpage.1.gz /usr/local/share/man/man1/norminette.1.gz
     sudo cp $HOME/norminette/manpage.2.gz /usr/share/man/man2/norminette.2.gz
else
    echo "Error: could not clone repository"
fi
