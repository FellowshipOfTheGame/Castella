#include <Widget.hpp>

Widget::Widget () : window (NULL), image (NULL) {};


Widget::~Widget () {};


Widget::Widget (SDL_Rect *window, int width, int height, int x, int y) 
		: window (window) {
	windowRelativeOffset.x = x;
	windowRelativeOffset.y = y;
	box.w = width;
	box.h = height;
	box.x = windowRelativeOffset.x + window->x;
	box.y = windowRelativeOffset.y + window->y;
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
