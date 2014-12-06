/** @file TextArea.hpp
 * header do view/TextArea.cpp
 */
#ifndef TEXTAREA_HPP
#define TEXTAREA_HPP

#include "Widget.hpp"

/** @brief Widget que é uma caixa de texto
 */
class TextArea : public Widget {
private:
	SDL_Color foreground;	///< Cor do escrito
	SDL_Color background;	///< Cor do fundo

	string texto;

public:
	/** @brief Ctor do TextArea */
	TextArea (SDL_Rect *window, int width, int height, int x, int y,
			SDL_Color foreground = PRETO, SDL_Color background = BRANCO);

	/// Redesenha o escrito dentro da TextArea
	void redraw ();

	/// Gerencia input de teclado
	void handle_input (int input);

	/** @brief Trabalha o texto, a partir dum clique
	 * 
	 * Se 'c' der pra ser escrito, escreve. aceita backspace também.
	 *
	 * @param[in] c Caractere de entrada
	 */
	void enterInput (int c);
};

#endif
