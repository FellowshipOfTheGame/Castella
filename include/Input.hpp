#ifndef INPUT_H
#define INPUT_H

#include <SDL/SDL.h>

//Handles the input
class Input
{
    public:
    enum InputValue{
        NO_INPUT = 0,
        UNDEFINED_INPUT,
        QUIT,
        MOUSE_LEFTCLICK,

    };

    public:
        //Get the next input from the queue
        static int get_input();
        //Gets the mouse x and y coords into a SDL_Rect
        static SDL_Rect get_mouse_offset();
        //Finds out rather a key is pressed or not
        static bool is_key_pressed(SDLKey key);

    private:
        static SDL_Event event;
        //Stores mouse position
        static int mouseX, mouseY;
};

#endif // INPUT_H
