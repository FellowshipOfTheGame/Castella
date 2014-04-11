#include "Input.hpp"

int Input::get_input(){
    //Next input to be popped
    if (SDL_PollEvent(&event)){ //not empty
        //Quit
        if (event.type == SDL_QUIT){
            return QUIT;
        }
        //Key down
        if(event.type == SDL_KEYDOWN){
                if((int)event.key.keysym.sym != (int)NO_INPUT){
                    return (int)event.key.keysym.sym;
                }
        }
        //Get mouse offsets
        if (event.type == SDL_MOUSEMOTION){
            mouseX = event.motion.x;
            mouseY = event.motion.y;
        }
        //If a mouse button was pressed
        if(event.type == SDL_MOUSEBUTTONDOWN){
            //Left button
            if(event.button.button == SDL_BUTTON_LMASK){
                return MOUSE_LEFTCLICK;
            }
        }

        return UNDEFINED_INPUT; //if the input was not defined
    }
    else return NO_INPUT;
}

SDL_Rect Input::get_mouse_offset(){
    SDL_Rect offset;
    offset.x = mouseX;
    offset.y = mouseY;
    return offset;
}

int Input::mouseX = 0;
int Input::mouseY = 0;
SDL_Event Input::event;
