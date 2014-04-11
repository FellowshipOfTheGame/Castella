#ifndef SCENE_H
#define SCENE_H

#include <vector>

#include "Window.hpp"
#include "SceneControl.hpp"
#include "Input.hpp"
#include "ScriptHandler.hpp"

//Virtual class parent to every game scene
class Scene
{
    public:
        Scene();
        virtual ~Scene();
        //Runs the scene logic
        virtual void update();
        //Draws the scene items
        virtual void draw(SDL_Surface *screen);
        //Handles the scene input - handles generic context inputs and calls specific context handler
        void handle_input();

        static Scene *scene; //the logic game scene

    protected:
        int input; //stores the last input value returned
        vector<Window*> windows;
        //Handles scene-specific input - called from handle_input()
        virtual void handle_scene_input(int input) = 0;
        //Handles a mouse click input on the scene
        virtual void mouseclick(int x, int y);
        //Defines a method for the ESC key
        virtual void escape();

    private:
};

// - TODO: base Scene must control mouse position aquisition and standard inputs like asking to quit on the X(close) button

#endif // SCENE_H
