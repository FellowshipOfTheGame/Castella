# SCons pra construir o jogo Castella!

# algumas opcoes de ambiente pra compilar os trem
env = Environment (
	CC = 'cc',
	CCFLAGS = '-g -Wall -pipe -fpermissive',
	LIBPATH = ['/usr/lib', '/usr/local/lib'],
	LIBS = ['lua', 'SDL', 'SDL_image', 'SDL_mixer', 'SDL_ttf'],
	CPPPATH = ['../include', '/usr/include/SDL', './arquivos\ lua']
)

# so recompila se for mais novo e se o arquivo objeto mudaria
env.Decider ('MD5-timestamp')

# constroi de 'src' pra 'build', sem duplicar os .cpp
VariantDir ('build', 'src', duplicate = 0)
SConscript ('build/SConscript', exports = 'env')	# script interno, que manda compilar na real o jogo
