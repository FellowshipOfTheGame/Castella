#include "TextArea.hpp"

#include <cctype>

TextArea::TextArea (SDL_Rect *window, int width, int height, int x, int y,
		SDL_Color foreground, SDL_Color background)
		: Widget (window, width, height, x, y),
		foreground (foreground), background (background) {
	redraw ();
}


void TextArea::redraw () {
	fill_surface (image, background);

	write_text (0, 0, image, texto, foreground);
}


void TextArea::handle_input (int input) {
	enterInput (input);
}


void TextArea::setTexto (string texto) {
	this->texto = texto;
	redraw ();
}


void TextArea::enterInput (int c) {
	switch (c) {
		case SDLK_BACKSPACE:
			if (!texto.empty ()) {
				texto.pop_back ();
			}
			break;

		default:
			if (isprint (c)) {
				texto += c;
			}
			break;
	}
	redraw ();
}
