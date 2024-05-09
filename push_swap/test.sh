#!/bin/bash

make

ARG=$(cat input)

if [ -z "$1" ]; then
	./push_swap $ARG
	exit 0
fi

case "$1" in
	"fun")
		funcheck -a ./push_swap $ARG
		;;
	"check")
		./push_swap $ARG | ./checker_linux $ARG
		;;
	"gdb")
		gdb --args ./push_swap $ARG
		;;
	"val")
		valgrind --leak-check=full ./push_swap $ARG
esac
