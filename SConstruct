# SCons pra construir o jogo Castella!
# coding: utf-8

import os
import platform

Help ("""
Para compilar o projeto, escreva 'scons' na linha de comando. Rode o programa \
com o Castella.sh
Para apagar os objetos criados, assim como o executavel, use o comando \
'scons -c'
""")

if not GetOption ('help'):
	# algumas opcoes de ambiente pra compilar os trem
	env = Environment (
		CC = 'g++',
		CCFLAGS = '-g -Wall -pipe -fpermissive -std=c++11',
		LIBPATH = ['/usr/lib'],
		LIBS = ['SDL', 'SDL_image', 'SDL_mixer', 'SDL_ttf', 'SDL_gfx',
				'luabindd'],
		CPPPATH = ['#include', '/usr/include/SDL', '/usr/local/include/',
				'/usr/include/lua5.2'],
	)

	# Configuracaozinha: bibliotecas dinâmicas!
	conf = Configure (env)

	# Checa arquitetura do processador
	arch = ''
	if platform.machine () == 'x86_64':
		arch = 'x86_64'
	else:
		arch = 'x86'
	conf.env.Append (LIBPATH = ('#libs/' + arch))

	# -llua ou -llua5.2 ?
	# se o grep retornar 0, é pq achou 'lua5.2', então linka com tal;
	# se retornar 1, é pq não achou, então o lua5.2 linka diretão no -llua
	if not os.system ('pkg-config --list-all | grep lua5.2'):
		lua = '-llua5.2'
	else:
		lua = '-llua'
	conf.env.Append (LIBS = (lua))

	env = conf.Finish ()


	# só recompila se for mais novo e se o arquivo objeto mudaria
	env.Decider ('MD5-timestamp')

	# constroi de 'src' pra 'build', sem duplicar os .cpp
	VariantDir ('build', 'src', duplicate = 0)
	# script interno, que manda compilar na real o jogo
	SConscript ('build/SConscript', exports = 'env')
