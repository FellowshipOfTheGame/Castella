#ifndef SIMPLESDLFUNCTIONS_H_INCLUDED
#define SIMPLESDLFUNCTIONS_H_INCLUDED

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"

#include <iostream>
#include <memory>
#include <stdlib.h>

using namespace std;

//################################## FUNÇÔES DE ATALHO ##################################OO
//Funções para facilitar a aplicação de outras funções, otimizando suas utilizações,
//em termos de organização e linhas de código

//---------------------------------- CARREGAR IMAGEM ------------------------------------//
//Função de carregamento de imagem
SDL_Surface *load_image(const char *nome_do_arquivo);
//---------------------------------------------------------------------------------------//

//--------------------------------- APLICAR SUPERFICIE ----------------------------------//
//Aplica uma superfície recebendo também suas coordenadas como parâmetros
void apply_surface(int x, int y, SDL_Surface* fonte, SDL_Surface* destino, SDL_Rect* corte = NULL, float empurrar = 0);
//---------------------------------------------------------------------------------------//

//--------------------------------- ESCREVER TEXTO --------------------------------------//
//Escreve um texto na tela, na posição desejada
//void write_text(int x, int y, char texto[])
//{
//    mensagem_texto = TTF_RenderText_Solid(fonte, texto, cortexto);
//    aplicar_superficie(x, y, mensagem_texto, tela);
//}
//---------------------------------------------------------------------------------------//
#endif // SIMPLESDLFUNCTIONS_H_INCLUDED

