#include "Slider.hpp"


inline int Slider::desl_x () {
	return img_selector->w / 2;
}


inline int Slider::desl_y () {
	return img_selector->h / 2;
}


Slider::Slider (SDL_Rect *window, int x, int y, SDL_Surface *img_back, SDL_Surface *img_selector) 
		: Widget (window, img_back->w, img_back->h, x, y), // ctor pai
		img_back (img_back), img_selector (img_selector), percent (0) {
	// Se altura é maior que largura, tá na vertical
	if (box.h > box.w) {
		dir = Direction::VERTICAL;
	}
	else {
		dir = Direction::HORIZONTAL;
	}
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
	}

	return aux;
}


// Funções auxiliares à draw
inline int max (int a, int b) {
	return (a > b) ? a : b;
}
inline int min (int a, int b) {
	return (a < b) ? a : b;
}


void Slider::draw (SDL_Surface *target) {
	apply_surface (box.x, box.y, img_back, target);
	// calcula posição do seletor
	int x, y;
	if (dir == Direction::VERTICAL) {
		// porcentagem na vertical
		y = box.h * (percent / 100.0);
		// aplica deslocamento e verifica se não chegou no cantos
		y -= desl_y ();
		y = max (y, 0);
		y = min (y, box.h - img_selector->h);
		// horizontal no meio do slider
		x = box.w / 2 - desl_x ();
	}
	else {
		// porcentagem na horizontal
		x = box.w * (percent / 100.0);
		// aplica deslocamento e verifica se não chegou no cantos
		x -= desl_x ();
		x = max (x, 0);
		x = min (x, box.w - img_selector->w);
		// vertical no meio do slider
		y = box.h / 2 - desl_y ();
	}
	apply_surface (box.x + x, box.y + y, img_selector, target);

	// escreve porcentagem em cima
	write_text (box.x, box.y, target, to_string (percent) + "%");
}
