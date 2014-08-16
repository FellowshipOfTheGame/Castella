#include <Button.hpp>
#include <simpleSDLfunctions.h>

Button::Button(){};

Button::Button(SDL_Rect *window, int x, int y, SDL_Surface *imgInactive, SDL_Surface *imgActive, LuaFunction cbk) {
    callback = cbk;
    this->imgInactive = imgInactive;
    this->imgActive = imgActive;
    this->window = window;
    windowRelativeOffset.x = x;
    windowRelativeOffset.y = y;
    box.x = windowRelativeOffset.x + window->x;
    box.y = windowRelativeOffset.y + window->y;
    box.w = this->imgInactive->w;
    box.h = this->imgInactive->h;
    deactivate();
}

Button::~Button(){
    std::cout << "Buttton dtor" << std::endl;
    //dtor
}

bool Button::mouse_try_click (int x, int y){
    //If it is over it:
    if( (x > box.x) && (y > box.y) && (x < box.x + box.w) && (y < box.y + box.h) ){
        activate();
        return true;
    }
    else{
        return false;
    }
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

Button* Button::create_button_list(int buttonCount){
    return new Button[buttonCount];
    //return (Button *) malloc( buttonCount * sizeof(Button) );
}
