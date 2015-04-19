#include "Slider.hpp"


inline int Slider::desl_x () {
	return img_selector->w / 2;
}


inline int Slider::desl_y () {
	return img_selector->h / 2;
}


Slider::Slider (SDL_Rect *window, int x, int y, SDL_Surface *img_back, SDL_Surface *img_selector) 
		: Widget (window, img_back->w, img_back->h, x, y), // ctor pai
		img_back (img_back), img_selector (img_selector) {
	// Se altura é maior que largura, tá na vertical
	if (box.h > box.w) {
		dir = Direction::VERTICAL;
	}
	else {
		dir = Direction::HORIZONTAL;
	}
	// desenha pela primeira vez o Slider, visto que ele 
	// só é redesenhado hora que é clicado
	redraw ();
}


int Slider::getPercent () const {
	return percent;
}


bool Slider::mouse_try_click (int x, int y) {
	bool aux = Widget::mouse_try_click (x, y);
	// tá dentro da zona clicável
	if (aux) {
		// atualiza percent (em relação à vertical ...
		if (dir == Direction::VERTICAL) {
			percent = (y - box.y) * 100.0 / box.h;
		}
		// ... ou horizontal)
		else {
			percent = (x - box.x) * 100.0 / box.w;
		}

		redraw ();
	}

	return aux;
}


void Slider::redraw () {
	// fundo
	apply_surface (0, 0, img_back, image);
	// calcula posição do seletor
	int x, y;
	if (dir == Direction::VERTICAL) {
		// porcentagem na vertical
		y = box.h * (percent / 100.0);
		// aplica deslocamento e verifica se não chegou no cantos
		y -= desl_y ();
		if (y < 0) {
			y = 0;
			percent = 0;
		}
		else if (y > box.h - img_selector->h) {
			y = box.h - img_selector->h;
			percent = 100;
		}
		// horizontal no meio do slider
		x = box.w / 2 - desl_x ();
	}
	else {
		// porcentagem na horizontal
		x = box.w * (percent / 100.0);
		// aplica deslocamento e verifica se não chegou no cantos
		x -= desl_x ();
		if (x < 0) {
			x = 0;
			percent = 0;
		}
		else if (x > box.w - img_selector->w) {
			x = box.w - img_selector->w;
			percent = 100;
		}
		// vertical no meio do slider
		y = box.h / 2 - desl_y ();
	}
	apply_surface (x, y, img_selector, image);

	// escreve porcentagem em cima
	write_text (0, 0, image, to_string (percent) + "%");

	need_redraw = true;
}
