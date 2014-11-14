#ifndef PLAYER_H
#define PLAYER_H
#include "Actor.hpp"
#include <vector>

class Player //Possivelmente diferenciar Human e Computer player por subclasses
{
    public:
        Player();
        virtual ~Player();
        int get_id();
        std::vector<Actor*> get_actors();

    protected:

    private:
        static int id;
        std::vector<Actor*> actors;
};

#endif // PLAYER_H
