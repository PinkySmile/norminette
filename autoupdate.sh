#!/bin/bash
nb_of_args=$#
arg=1
line=""
while [ $nb_of_args != 0 ]; do
    nb_of_args=$(($nb_of_args - 1))
    line="$line ${!arg}"
    arg=$(($arg + 1))
done
cd $HOME/norminette
./update.sh >> $HOME/norminette/update.log 2>>$HOME/norminette/update.log &
ls norm >> /dev/null 2>/dev/null
if [ $? == 2 ]
then make >> /dev/null
	if [ $? == 2 ]
	then echo -e "Error : Could not compile..."
	fi
	make clean >> /dev/null
fi
cd - >> /dev/null
$HOME/norminette/norminette $line
