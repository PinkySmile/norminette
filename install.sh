#!/bin/bash
cd $HOME
result=$(git clone https://github.com/Gegel85/norminette.git)
if [ $? == 0 ]
then make -C norminette
     make -C norminette clean
     chmod 755 $HOME/norminette/update.sh
     echo "Donnez le nom de l'alias : "
     read x
     echo alias $x="$HOME/norminette/norminette" >> $HOME/.bashrc
     echo alias $x="$HOME/norminette/norminette" >> $HOME/.zshrc
     echo Alias $x créé
     echo alias $x-update="$HOME/norminette/update.sh" >> $HOME/.bashrc
     echo alias $x-update="$HOME/norminette/update.sh" >> $HOME/.zshrc
     echo Alias $x-update créé
     echo alias $x-debug="$HOME/norminette/debug.sh" >> $HOME/.bashrc
     echo alias $x-debug="$HOME/norminette/debug.sh" >> $HOME/.zshrc
     echo Alias $x-debug créé
else
    echo "Error: could not clone repository"
    echo $result
fi
