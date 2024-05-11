#!/bin/bash

make

if [ -z "$1" ]; then
	./pipex in "cat" "grep a" out
	exit 0
fi

case "$1" in
	"fun")
		funcheck -a ./pipex in "cat -e" "grep a" out
		;;
	"gdb")
		gdb --args ./pipex in "cat -e" "grep a" out
		;;
	"val")
		valgrind --leak-check=full ./pipex in "cat -e" "grep a" out
		;;
esac
