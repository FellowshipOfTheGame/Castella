#include <Button.hpp>
#include <simpleSDLfunctions.h>

Button::Button() : Widget () {};

Button::Button(SDL_Rect *window, int x, int y, SDL_Surface *imgInactive, SDL_Surface *imgActive, LuaFunction cbk) 
		: Widget (window, imgInactive->w, imgInactive->h, x, y), // ctor pai
		imgInactive (imgInactive), imgActive (imgActive), // imgs
		callback (cbk) { // e o callback
    deactivate();
}

Button::~Button(){
    std::cout << "Buttton dtor" << std::endl;
    //dtor
}

bool Button::mouse_try_click (int x, int y){
	bool aux = Widget::mouse_try_click (x, y);
	if (aux) {
		activate ();
	}
	return aux;
}

void Button::activate(){
    image = imgActive;
    activated = 8;
    try{
		callback();
    }
    catch(luabind::error& e){
		std::cout << "Error calling Luafunction: " << lua_tostring(e.state(), -1) << std::endl;
    }

}

void Button::deactivate(){
    image = imgInactive;
    activated = 0;
}

void Button::update(){
    //Refresh button position
    box.x = windowRelativeOffset.x + window->x;
    box.y = windowRelativeOffset.y + window->y;
    //Countdown on active time
    if (activated > 0) activated--;
    else deactivate();
}

void Button::draw(SDL_Surface* target){
    apply_surface(box.x, box.y, image, target);
}

Button* Button::create_button_list (int buttonCount){
    return new Button[buttonCount];
}
