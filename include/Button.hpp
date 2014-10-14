#ifndef BUTTON_H
#define BUTTON_H

#include <Widget.hpp>
#include <iostream>

#include "LuaWBind.hpp"

class Button : public Widget
{
    private:
        SDL_Surface *imgInactive, *imgActive; //images when the button is active, inactive, and the logic image
        int activated; //holds the number of frames for the button to stay active
        LuaFunction callback; //the method called back from the button when it is activated

    public:
        Button();
        //Creates a button bound to a window, at a relative position (x,y), that calls a method when activated
        Button(SDL_Rect *window, int x, int y, SDL_Surface *imgInactive, SDL_Surface *imgActive, LuaFunction cbk);
        virtual ~Button();
		// Se clicar, activate ()
		virtual bool mouse_try_click (int x, int y);
        //Activates a button, switching it's image and keeping it as active during some frames
        void activate();
        //Deactivates a button to it's default image
        void deactivate();
        //Does the update logic that must be called every frame
        virtual void update();
        //Draws the button
        virtual void draw(SDL_Surface* target);

        //Static method to allocate memory for an array of buttons
        static Button* create_button_list(int buttonCount);
};

#endif // BUTTON_H
