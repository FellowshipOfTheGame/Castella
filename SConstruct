# SCons pra construir o jogo Castella!

import sys
import platform

Help ("""
Para compilar o projeto, escreva 'scons' na linha de comando. Rode o programa com o Castella.sh
Para apagar os objetos criados, assim como o executavel, use o comando 'scons -c'
""")

if not GetOption ('help'):
	# algumas opcoes de ambiente pra compilar os trem
	env = Environment (
		CC = 'g++',
		CCFLAGS = '-g -Wall -pipe -fpermissive -std=c++11',
		LIBPATH = ['/usr/lib'],
		LIBS = ['lua', 'SDL', 'SDL_image', 'SDL_mixer', 'SDL_ttf', 'SDL_gfx', 'luabindd'],
		CPPPATH = ['#include', '/usr/include/SDL', '/usr/local/include/', '/usr/include/lua5.2'],
	)

	# Configuracaozinha: serve pra achar as dependencias; so serve se pedir pra construir
	conf = Configure (env)

	# Checa arquitetura do processador
	arch = ''
	if platform.machine () == 'x86_64':
		arch = 'x86_64'
	else:
		arch = 'x86'
	conf.env.Append (LIBPATH = ('#libs/' + arch))

	env = conf.Finish ()

	# so recompila se for mais novo e se o arquivo objeto mudaria
	env.Decider ('MD5-timestamp')

	# constroi de 'src' pra 'build', sem duplicar os .cpp
	VariantDir ('build', 'src', duplicate = 0)
	SConscript ('build/SConscript', exports = 'env')	# script interno, que manda compilar na real o jogo
