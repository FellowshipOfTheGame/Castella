#ifndef BUTTON_H
#define BUTTON_H

#include "SDL/SDL.h"
#include <iostream>

class Button
{
    private:
        SDL_Rect box; //the rect that holds position and dimentions of the button
        SDL_Rect windowRelativeOffset; //offset relative to the parent window
        SDL_Rect *window; //parent window offset
        SDL_Surface *imgInactive, *imgActive, *image; //images when the button is active, inactive, and the logic image
        int activated; //holds the number of frames for the button to stay active
        void (*callback_method)(); //the method called back from the button when it is activated

    public:
        //Creates a button bound to a window, at a relative position (x,y), that calls a method when activated
        Button(SDL_Rect *window, int x, int y, SDL_Surface *imgInactive, SDL_Surface *imgActive, void (*method)());
        virtual ~Button();
        //Checks if the mouse is over the button
        bool mouse_try_click (int x, int y);
        //Activates a button, switching it's image and keeping it as active during some frames
        void activate();
        //Deactivates a button to it's default image
        void deactivate();
        //Does the update logic that must be called every frame
        void update();
        //Draws the button
        void draw(SDL_Surface* target);
        //Runs the callback method for this button
        void callback();

        //Static method to allocate memory for an array of buttons
        static Button* create_button_list(int buttonCount);
};

#endif // BUTTON_H
