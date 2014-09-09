#ifndef ACTOR_BATTLER_H
#define ACTOR_BATTLER_H

#include <FileHandler.hpp>


enum class Direction {
    RIGHT,
    LEFT,
    UP,
    DOWN
};

class Actor_Battler
{
    private:
        int hp;
        int mp;
        int stamina;
        SDL_Surface* spritesheet;
        Direction direction;
        SDL_Rect spriteclip[12];
        SDL_Rect map_pos; //battler position on the battler map

    public:
        Actor_Battler(); // Deve receber um objeto Actor como parametro, para ajustar os valores base dos atributos, bem como a sptitesheet
        virtual ~Actor_Battler();

        bool use_skill(int skill_id);

        bool is_passable();

        void draw(int x, int y, int index, SDL_Surface *screen);

        void set_map_pos(int x, int y);

        SDL_Rect get_map_pos();

    protected:
        bool passable;
        SDL_Rect clip(int index);

    private:
};

#endif // ACTOR_BATTLER_H
