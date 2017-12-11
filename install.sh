#!/bin/bash
cd $HOME
result=$(git clone https://github.com/Gegel85/norminette.git)
if [ $? == 0 ]
then make -C norminette
     make -C norminette clean
     echo "Donnez le nom de l'alias : "
     read x
     echo alias $x="$HOME/norminette/norminette" >> $HOME/.bashrc
else
    echo "Error: could not clone repository"
    echo $result
fi
