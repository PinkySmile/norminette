#!/bin/sh

nb_of_args=$#
arg=1
line=""
while [ $nb_of_args != 0 ]; do
    nb_of_args=$(($nb_of_args - 1))
    line="$line ${!arg}"
    arg=$(($arg + 1))
done
$HOME/norminette/norminette -ad$line > scan.log
echo "$HOME/norminette/norminette -ad$line" >> scan.log
echo >> scan.log
