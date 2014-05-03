#################################################################################
## _______         __ __                        __     __                 ___  ##
##|    ___|.-----.|  |  |.-----.--.--.--.-----.|  |--.|__|.-----. .-----.'  _| ##
##|    ___||  -__||  |  ||  _  |  |  |  |__ --||     ||  ||  _  | |  _  |   _| ##
##|___|    |_____||__|__||_____|________|_____||__|__||__||   __| |_____|__|   ##
##                                                        |__|                 ##
## __   __            _______                                                  ##
##|  |_|  |--.-----. |     __|.---.-.--------.-----.						   ##
##|   _|     |  -__| |    |  ||  _  |        |  -__|						   ##
##|____|__|__|_____| |_______||___._|__|__|__|_____|						   ##
#################################################################################      

#Castella Makefile
SHELL = /bin/sh

#CASTELLA PATHS
HPATH = ./include
LIBSPATH = ./libs
OBJPATH = ./obj
SPTPATH = ./script
SRCPATH = ./src

CSTPATH = $(HPATH) $(LIBSPATH) $(OBJPATH) $(SPTPATH) $(SRCPATH)

#Bibliotecas utilizadas
LIBSLIST = SDL SDL_image SDL_ttf SDL_mixer lua luabindd

#COMMON linux paths
CMMHPATH = /usr/include /usr/local/include
CMMLPATH = /usr/lib /usr/local/lib

#Lista de todos os paths para headers
ALLPHDR = $(HPATH)
#Lista de todos os paths para as libs
ALLPLIB = $(LIBSPATH) $(OBJPATH) $(SRCPATH)

#Macros para a chamada ao g++
INCALL = $(foreach path, $(ALLPHDR), -I$(path))
LIBALL = $(foreach path, $(ALLPLIB), -L$(path))
LINKALL = $(foreach lib, $(LIBSLIST), -l$(lib))

ALLCPP = ./src/*.c*
ALLOBJ = ./obj/*.o

DEBUG = -Wall -g

final: objs
	g++ -v
	g++ $(DEBUG) $(ALLOBJ) -o castella $(INCALL) $(LIBALL) $(LINKALL)

objs:
	g++ $(DEBUG) -c $(ALLCPP) $(INCALL) $(LIBALL) $(LINKALL)
	mv *.o ./obj 

clean: 
	rm -f *.o ./obj/*.o castella

run:
	./castella

echo:
	echo $(FILELIST)
	echo $(OBJ) 