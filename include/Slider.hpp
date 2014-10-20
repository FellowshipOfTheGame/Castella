/** @file Slider.hpp
 * header do ../src/view/Slider.cpp
 */

#ifndef SLIDER_HPP
#define SLIDER_HPP

#include "Widget.hpp"

/** @brief Slider é um Widget daquele de arrastar.
 */
class Slider : public Widget {
private:
	/// Imagem de fundo do Slider
	SDL_Surface *img_back;
	/// Imagem do seletor do Slider (aquele trem que slida)
	SDL_Surface *img_selector;

	/// Posição do slider
	int percent;

	/**
	 * Deslocamento do centro do Slider em relação à suas imagens.
	 *
	 * Posição do Slider é contado em relação ao seu centro em ambos eixos,
	 * portanto precisamos de um deslocamento que é de metade do
	 * tamanho do seletor, para as contas ficarem certinhas, e podermos
	 * usar nosso Slider sempre sem sair de sua fronteira ;]
	 */
	inline int desl_x ();
	inline int desl_y ();

	/// Enum das direções do Slider
	enum class Direction {
		HORIZONTAL,
		VERTICAL
	};

	Direction dir;

public:
	/**
	 * Ctor do Slider
	 *
	 * @param[in] window Window
	 * @param[in] x Posição horizontal em relação à Window
	 * @param[in] y Posição vertical em relação à Window
	 * @param[in] img_back Imagem de fundo Slider (afeta seu tamanho, use com sabedoria)
	 * @param[in] img_selector Imagem do selecionador do Slider (a ser posto sobre o fundo)
	 */
	Slider (SDL_Rect *window, int x, int y, SDL_Surface *img_back, SDL_Surface *img_selector);
	/// Clica lá
	bool mouse_try_click (int x, int y);
	/// Desenha esse trem
	void draw (SDL_Surface *target);
	/// Getter da porcentagem: saída do slider (sua utilidade)
	int getPercent () const;


protected:
};

#endif
