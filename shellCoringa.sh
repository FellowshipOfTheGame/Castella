#!/bin/bash

# shellCoringa.sh é um utilitário feito por Gil Barbosa Reis [Zumbi]
# pode ser copiado, modificado, vendido, só não retirem as 3 primeiras funções,
# já que são as que eu uso =P
# para a terceira, o programa cmatrix precisa estar instalado, então já sabem

echo -e "O que deseja fazer?\n"

echo -n "1. Limpar os descartáveis da vida
2. Tentar compilar Region.cpp e Structure.cpp e World.cpp
3. Gerar e ver a documentação a la Doxygen
4. Ver os numerim caindo do Matrix!
q. Nada, sair

Sua escolha, jovem > "

read ESCOLHA
CXXFLAGS='-I../arquivos\ lua'

case $ESCOLHA in
	# apaga arquivos gerados pelo cmake e backups de texto
	1) rm -rf html CMakeFiles/ src/CMakeFiles/ build/* \
		cmake_install.cmake CMakeCache.txt Makefile *~ ;;

	# compila Region.cpp e Structure.cpp: pra ver se as sintaxe tão certa, talz
	2) cp src/{Region.cpp,Structure.cpp,World.cpp} build/
	   cp include/{Region.hpp,Structure.hpp,World.hpp} build/
	   cd build/
	   g++ -c Region.cpp "$CXXFLAGS"
	   g++ -c Structure.cpp "$CXXFLAGS" 
	   g++ -c World.cpp "$CXXFLAGS"
	   cd .. ;;
	
	# documentar é preciso!
	3) doxygen
	   x-www-browser ./html/index.html & ;;

	# Diversão! (solução sim) Diversão! (solução pra mim)
	4) cmatrix -abs	;;

	# ah, xaquieto, vambora desse script lixo
	q) ;;

	*) echo -e "Opção inválida =/\nTente novamente" ;;
esac

exit
