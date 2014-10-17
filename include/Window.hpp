#ifndef WINDOW_H
#define WINDOW_H

#include <list>
#include <vector>


#include "FileHandler.hpp"
#include "FileContainer.hpp"
#include "ImageHandler.hpp"


#include "Widgets.hpp"
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
        Window(const std::string scriptFile);
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

    private:
        std::vector<Widget *> widgetList; //widget lsit
        //Button *buttonList; //a pointer to a list of buttons
        SDL_Rect rect; //the rectangle with coordinates and dimentions of the window
        SDL_Surface *wSurface; //the image surface for the window
        bool visible; //visibility of the window - to implement
        static const std::string scriptPath;
        static const std::string buttonImgPath;
        ScriptHandler sHandler;

        FileContainer files;

		void buttons_setup ();
        //Setup elements - such as buttons
        void elements_setup();
        //virtual void elements_setup(lua_State *state);
        //Checks if the mouse is inside the window
        bool is_mouse_inside(int x, int y);


    protected:
};

#endif // WINDOW_H
