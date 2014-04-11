#ifndef SCENE_BATTLE_HPP
#define SCENE_BATTLE_HPP

#include "Scene.hpp"
#include "Map_Battle.hpp"

class Scene_Battle : public Scene
{
    public:
        Scene_Battle();
        virtual ~Scene_Battle();
        virtual void draw(SDL_Surface *screen);
        virtual void update();



    protected:
        Map_Battle *battleMap;

        virtual void mouseclick(int x, int y);
        virtual void escape();
        virtual void handle_scene_input(int input);

    private:
};

#endif // SCENE_BATTLE_HPP
