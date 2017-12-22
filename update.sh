#!/bin/bash
cd $HOME/norminette
if [ $(git pull | wc -l) != 1 ]
then make re >> /dev/null
fi
