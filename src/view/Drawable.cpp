#include "Drawable.hpp"

Drawable::Drawable () : Drawable (Screen::WIDTH, Screen::HEIGHT) {}

Drawable::Drawable (int width, int height) : image (create_surface (width, height)) {}

Drawable::Drawable (SDL_Surface *img) : image (img) {}

Drawable::~Drawable () {
	SDL_FreeSurface (image);
}

void Drawable::draw (SDL_Surface *screen, SDL_Rect *corte) {
	if (need_redraw) {
		redraw ();
		apply_surface (0, 0, image, screen, corte);
		need_redraw = false;
	}
}

void Drawable::draw (SDL_Surface *screen) {
	draw (screen, nullptr);
}

void Drawable::set_need_redraw () {
	need_redraw = true;
}
