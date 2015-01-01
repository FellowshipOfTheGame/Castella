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

#define DEFAULT_FONT_SIZE 26

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

/* Cores básicas, em SDL_Color */
#define PRETO		{0, 0, 0}
#define BRANCO		{255, 255, 255}
#define VERMELHO	{255, 0, 0}
#define VERDE		{0, 255, 0}
#define AZUL		{0, 0, 255}
#define AMARELO		{255, 255, 0}
#define MAGENTA		{255, 0, 255}
#define CIANO		{0, 255, 255}


//############################# FUNÇÔES DE ATALHO ##############################
// Funções para facilitar a aplicação de outras funções, otimizando suas
// utilizações, em termos de organização e linhas de código

//------------------------------ CARREGAR IMAGEM -----------------------------//
//Função de carregamento de imagem
SDL_Surface *load_image (std::string nome_do_arquivo);
//----------------------------------------------------------------------------//

//--------------------------------- CRIAR SUPERFICIE -------------------------//
// Função que cria uma superfície vazia
SDL_Surface *create_surface (int width, int height);
//----------------------------------------------------------------------------//

//---------------------------- APLICAR SUPERFICIE ----------------------------//
//Aplica uma superfície recebendo também suas coordenadas como parâmetros
void apply_surface(int x, int y, SDL_Surface* fonte, SDL_Surface* destino,
		SDL_Rect* corte = NULL, float empurrar = 0);
/// Transforma um SDL_Color em Uint32, pras funções que o precisam
Uint32 getRGBAMap (SDL_Surface *target, SDL_Color cor, Uint8 alpha = 0xff);
/** @brief Preenche o fundo de uma superfície
 *
 * @param[in] target Superfície a ser 'pintada'
 * @param[in] cor Cor de fundo; padrão = preto
 * @param[in] dstrect Retângulo a ser preenchido; padrão = em toda a superfície
 */
void fill_surface (SDL_Surface *target, SDL_Color cor = PRETO,
		SDL_Rect *dstrect = NULL);
//----------------------------------------------------------------------------//

//-------------------------------- ESCREVER TEXTO ----------------------------//
//Escreve um texto na tela, na posição desejada
// cor pelo SDL_Color: padrão = preto
void write_text (int x, int y, SDL_Surface *destino, std::string texto,
		SDL_Color cor = PRETO, float alinhamento = 0);
//----------------------------------------------------------------------------//
#endif // SIMPLESDLFUNCTIONS_H_INCLUDED

