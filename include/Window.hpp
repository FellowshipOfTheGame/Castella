#ifndef WINDOW_H
#define WINDOW_H

#include <list>
#include <vector>


#include "FileHandler.hpp"
#include "FileContainer.hpp"
#include "ImageHandler.hpp"


#include "Button.hpp"
#include "Screen.h"
#include "GameStructure.hpp"
#include "SceneControl.hpp"

#include "Callback.hpp"
#include "ScriptHandler.hpp"


//Virtual class parent to each window; holds elements such as buttons and responds to input
class Window
{
    public:
        Window();
        Window(int x, int y); //ctor with window position as parameter
        //Window(const std::string &scriptFile, lua_State *state );
        Window(std::string script); //ctor with a lua script as parameter
        Window(const char *scriptFile, ScriptHandler &sh );
        virtual ~Window();

        //Sets the window position
        virtual void set_position(int x, int y);
        //Gets the window rect
        virtual SDL_Rect get_position();
        //Runs a mouseclick on the specified coordinates
        virtual void mouseclick(int x, int y);
        //Draws the window
        virtual void draw(SDL_Surface *screen);
        //Do an update on the window's and its elements' logic
        virtual void update();

        Button *buttonList; //a pointer to a list of buttons
    protected:
        SDL_Rect rect; //the rectangle with coordinates and dimentions of the window
        SDL_Surface *wSurface; //the image surface for the window
        short int buttonCount; //the number of buttons on the window
        bool visible; //visibility of the window - to implement
        static const std::string scriptPath;
        static const std::string buttonImgPath;
        ScriptHandler *sHandler;

        FileContainer files;

        //Setup elements - such as buttons
        virtual void elements_setup(ScriptHandler &sh );
        //virtual void elements_setup(lua_State *state);
        virtual void elements_setup();
        //Checks if the mouse is inside the window
        bool is_mouse_inside(int x, int y);


    private:
};

#endif // WINDOW_H
