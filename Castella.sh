#!/bin/sh
if [ `uname -m` == 'x86_64' ]
then
	arch='x86_64'
else
	arch='x86'
fi

# link com as libs que tão na pasta libs xD
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:libs/$arch

exe="build/Castella"

case "$1" in
	"debug")
		gdb $exe;;

	"memcheck")
		valgrind $exe;;

	"fullcheck")
		valgrind --leak-check=full --log-file=memcheck.out $exe;;

	# cria base de dados do cscope
	"cscope")
		cd src/
		cscope -b -I../include/ -smodel/ -sview/ -scontroller/ -sgamedata/
		;;

	*)
		$exe;;

esac

exit
