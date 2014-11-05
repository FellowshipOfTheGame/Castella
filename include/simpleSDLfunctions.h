/** @file simpleSDLfunctions.h
 * header do model/simpleSDLfunctions.cpp
 */

#ifndef SIMPLESDLFUNCTIONS_H_INCLUDED
#define SIMPLESDLFUNCTIONS_H_INCLUDED

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_gfxPrimitives.h>

#include <string>

/* Máscara de bits pra criação de superfície, dica do SDL */
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
#	define RMASK 0xff000000
#	define GMASK 0x00ff0000
#	define BMASK 0x0000ff00
#	define AMASK 0x000000ff
#else
#	define RMASK 0x000000ff
#	define GMASK 0x0000ff00
#	define BMASK 0x00ff0000
#	define AMASK 0xff000000
#endif

//################################## FUNÇÔES DE ATALHO ##################################OO
//Funções para facilitar a aplicação de outras funções, otimizando suas utilizações,
//em termos de organização e linhas de código

//---------------------------------- CARREGAR IMAGEM ------------------------------------//
//Função de carregamento de imagem
SDL_Surface *load_image (std::string nome_do_arquivo);
//----------------------------------------------------------------------------//

//--------------------------------- CRIAR SUPERFICIE -------------------------//
// Função que cria uma superfície vazia
SDL_Surface *create_surface (int width, int height);
//----------------------------------------------------------------------------//

//---------------------------- APLICAR SUPERFICIE ----------------------------//
//Aplica uma superfície recebendo também suas coordenadas como parâmetros
void apply_surface(int x, int y, SDL_Surface* fonte, SDL_Surface* destino, SDL_Rect* corte = NULL, float empurrar = 0);
// Preenche o fundo de uma superfície: padrão = preto, em toda a superfície
void fill_surface (SDL_Surface *target, SDL_Rect *dstrect = NULL,
		SDL_Color cor = {0, 0, 0});
//----------------------------------------------------------------------------//

//-------------------------------- ESCREVER TEXTO ----------------------------//
//Escreve um texto na tela, na posição desejada
// cor por RGB: padrão = preto
void write_text(int x, int y, SDL_Surface *destino, std::string texto, unsigned char R = 0, unsigned char G = 0, unsigned char B = 0);
// cor direto pelo SDL_Color
void write_text(int x, int y, SDL_Surface *destino, std::string texto, SDL_Color cor);
//----------------------------------------------------------------------------//
#endif // SIMPLESDLFUNCTIONS_H_INCLUDED

