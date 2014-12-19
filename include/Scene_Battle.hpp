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
        static int frame;


    protected:
        Map_Battle battleMap;
        std::vector<Actor_Battler*> battlersTeam1;
        std::vector<Actor_Battler*> battlersTeam2;

        virtual void mouseclick(int x, int y);
        virtual void escape();
        virtual void handle_scene_input(int input);

        SDL_Surface* cursor;

    private:
        Actor_Battler *active_battler;

        virtual void load_battlers(Player* player1, Player* player2);
        std::vector<Actor_Battler*> get_battlers();
        void update_stamina();
        bool cause_damage(int damage, SDL_Rect target); //return true if a battler was damaged

        //temp:
        Animated_Sprite aSprite;
};

#endif // SCENE_BATTLE_HPP
