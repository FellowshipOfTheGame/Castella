/** @file Drawable.hpp
 * Define objetos que são desenhados/desenháveis
 *
 * header do view/Drawable.cpp
 */

#ifndef DRAWABLE_HPP
#define DRAWABLE_HPP

#include "simpleSDLfunctions.h"
#include "Screen.h"

class Drawable {
public:
	/// Ctor padrão: imagem do tamanho da tela
	Drawable ();
	/// Ctor com parâmetros: imagem do tamanho especificado
	Drawable (int width, int height);
	/// Ctor com parâmetro: SDL_Surface a ser usada
	Drawable (SDL_Surface *img);
	/// Dtor: libera imagem
	virtual ~Drawable ();

	/// Desenha o que quer que precise na imagem inteira
	virtual void draw (SDL_Surface *screen);
	/// Desenha recorte na imagem
	virtual void draw (SDL_Surface *screen, SDL_Rect *corte);

	/// Força elemento a redesenhar
	virtual void set_need_redraw ();

protected:
	/// Redesenha tela na surface "image", pra poder ser desenhada na tela
	virtual void redraw () = 0;

	/// Imagem, o que será efetivamente mostrado
	SDL_Surface *image {NULL};
	/// Controla se precisa redesenhar (pra melhorar eficiência)
	bool need_redraw {true};
};

#endif
