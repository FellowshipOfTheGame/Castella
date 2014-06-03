#!/bin/bash

# link com as libs que tão na pasta libs xD
export LD_LIBRARY_PATH=libs
if [[ $1 == "debug" ]]
then
	gdb build/Castella
else
	build/Castella
fi

exit
