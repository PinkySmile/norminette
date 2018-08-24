#!/bin/bash

if [[ $1 == "-h" ]]; then
	echo "Usage: $0 <installation path>"
	exit 0
fi

if [[ -z "$1" ]]; then
	path=$(realpath "./norminette")
else
	path=$(realpath $1)
fi

echo "Fetching norminette..."
echo "======================"

if git clone https://github.com/Gegel85/norminette.git $path; then
	echo "Compiling..."
	echo "======================"
	make -C $path 1> /dev/null
	make -C $path clean 1> /dev/null
	chmod 755 $path/update.sh
	echo "Compiled."

	echo "Installing..."
	echo "======================"
	sudo ln -s $path/norminette /usr/local/bin/norminette
	echo "Done."
	exit 0;
else
	echo "Download failed."
	exit 1
fi
