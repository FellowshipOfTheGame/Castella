#ifndef SCENE_WORLD_H
#define SCENE_WORLD_H

#include "Scene.hpp"
#include <Map_World.hpp>
#include <iostream>

class Scene_World : public Scene
{
    public:
        Scene_World();
        virtual ~Scene_World();

        virtual void update();

        virtual void draw(SDL_Surface *screen);

        virtual void mouseclick(int x, int y);

        virtual void escape();

        virtual void handle_scene_input(int input);

    protected:
    private:
		Map_World *map;
};

#endif // SCENE_WORLD_H
