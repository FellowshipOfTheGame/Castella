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

    private:
        static SDL_Event event;
        //Stores mouse position
        static int mouseX, mouseY;
};

#endif // INPUT_H
