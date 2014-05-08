#include <Button.hpp>
#include <simpleSDLfunctions.h>


Button::Button(SDL_Rect *window, int x, int y, SDL_Surface *imgInactive, SDL_Surface *imgActive, LuaFunction cbk) {
    callback_method = new LuaObject(cbk);
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

Button::Button(SDL_Rect *window, int x, int y, SDL_Surface *imgInactive, SDL_Surface *imgActive, void (*method)()) {
    cbk_method = method;
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
    std::cout << "Aqui =D\n";
    cbk();
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

void Button::cbk(){
    cbk_method();
}

void Button::callback(){
    using namespace std;
    using namespace luabind;
    //call_function<void>( *callback_method )[adopt(result)];
    (*callback_method)()[discard_result];
}

Button* Button::create_button_list(int buttonCount){
    return (Button *) malloc( buttonCount * sizeof(Button) );
}
