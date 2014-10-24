#include <Button.hpp>

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
    apply_surface (0, 0, imgActive, image);
    activated = 8;
    try{
		callback();
    }
    catch(luabind::error& e){
		std::cout << "Error calling Luafunction: " << lua_tostring(e.state(), -1) << std::endl;
    }

}

void Button::deactivate(){
    apply_surface (0, 0, imgInactive, image);
    activated = 0;
}

void Button::update(){
	Widget::update ();
    //Countdown on active time
    if (activated > 0) activated--;
    else deactivate();
}

Button* Button::create_button_list (int buttonCount){
    return new Button[buttonCount];
}
