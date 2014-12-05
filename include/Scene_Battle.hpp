#ifndef SCENE_BATTLE_HPP
#define SCENE_BATTLE_HPP

#include "Scene.hpp"
#include "Map_Battle.hpp"
#include "Player.hpp"
#include "World.hpp"

class Scene_Battle : public Scene
{
    public:
        Scene_Battle();
        virtual ~Scene_Battle();
        virtual void draw(SDL_Surface *screen);
        virtual void update();



    protected:
        Map_Battle battleMap;
        std::vector<Actor_Battler*> battlersTeam1;
        std::vector<Actor_Battler*> battlersTeam2;

        virtual void mouseclick(int x, int y);
        virtual void escape();
        virtual void handle_scene_input(int input);

    private:
        virtual void load_battlers(Player* player1, Player* player2);
};

#endif // SCENE_BATTLE_HPP
