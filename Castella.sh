#!/bin/bash

# link com as libs que tão na pasta libs xD
export LD_LIBRARY_PATH=libs

exe="build/Castella"

case "$1" in
	"debug")
		gdb $exe;;

	"memcheck")
		valgrind $exe;;

	"fullcheck")
		valgrind --leak-check=full $exe;;

	*)
		$exe;;

esac

exit
