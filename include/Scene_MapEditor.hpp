#ifndef SCENE_MAPEDITOR_H
#define SCENE_MAPEDITOR_H

#include "Scene.hpp"
#include "Window_StartMenu.hpp"


class Scene_MapEditor : public Scene
{
    public:
        Scene_MapEditor();
        virtual ~Scene_MapEditor();

        virtual void update();
        virtual void draw(SDL_Surface *screen);
        virtual void handle_scene_input(int);
        void mouseclick(int x, int y);

    protected:
    private:
        Window *window;
};

#endif // SCENE_MAPEDITOR_H
