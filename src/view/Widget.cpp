#include "Widget.hpp"

Widget::Widget () {}


Widget::Widget (SDL_Rect *window, int width, int height, int x, int y) 
		: window (window), image (create_surface (width, height)) {
	windowRelativeOffset.x = x;
	windowRelativeOffset.y = y;
	box.w = width;
	box.h = height;
	box.x = windowRelativeOffset.x + window->x;
	box.y = windowRelativeOffset.y + window->y;
}


Widget::~Widget () {
	SDL_FreeSurface (image);
};


void Widget::update () {
	box.x = windowRelativeOffset.x + window->x;
	box.y = windowRelativeOffset.y + window->y;
}


void Widget::draw (SDL_Surface *target) {
	apply_surface(box.x, box.y, image, target);
}


bool Widget::mouse_try_click (int x, int y){
	// se tá dentro, é true
	if (x > box.x && x < box.x + box.w && 
			y < box.y + box.h && y > box.y) {
		return true;
	}
	// se não tá dentro, tá fora =P
	else {
		return false;
	}
}


void Widget::handle_input (int input) {}
