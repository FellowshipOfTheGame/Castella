#include <Input.hpp>

int Input::get_input(){
    //Next input to be popped
    if (SDL_PollEvent(&event)){ //not empty
        //Quit
        if (event.type == SDL_QUIT){
            return QUIT;
        }
        //Key down
		else if(event.type == SDL_KEYDOWN){
			// código da tecla
			int c = event.key.keysym.sym;

			if(c != NO_INPUT){
				// checa shift e caps lock, pra mandar maiúsculo
				int mod = event.key.keysym.mod;
				if (mod & (KMOD_SHIFT | KMOD_CAPS)) {
					c = toupper (c);
				}
				return c;
			}
        }
        //Get mouse offsets
		else if (event.type == SDL_MOUSEMOTION){
            mouseX = event.motion.x;
            mouseY = event.motion.y;
        }
        //If a mouse button was pressed
		else if(event.type == SDL_MOUSEBUTTONDOWN){
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

bool Input::is_key_pressed(SDLKey key){
    Uint8 *keystates = SDL_GetKeyState(NULL);
    return keystates[key];
}

int Input::mouseX = 0;
int Input::mouseY = 0;
SDL_Event Input::event;
