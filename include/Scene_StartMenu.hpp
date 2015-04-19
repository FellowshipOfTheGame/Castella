#ifndef SCENE_STARTMENU_H
#define SCENE_STARTMENU_H

#include "Scene.hpp"
#include "Window_StartMenu.hpp"
#include <cassert>

class Scene_StartMenu : public Scene
{
    public:
        Scene_StartMenu();
        virtual ~Scene_StartMenu();

        virtual void redraw ();

        virtual void update();

    protected:
        virtual void escape();
        virtual void handle_scene_input(int input);

    private:
        SDL_Surface *title;
};

#endif // SCENE_STARTMENU_H
