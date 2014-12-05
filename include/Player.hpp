#ifndef PLAYER_H
#define PLAYER_H
#include "Actor.hpp"
#include <vector>

class Player //Possivelmente diferenciar Human e Computer player por subclasses
{
    public:
        Player(Actor* actor);
        virtual ~Player();
        int get_id();
        std::vector<Actor*> get_actors();
        void add_actor(Actor *actor);
        void remove_actor(Actor *actor);

    protected:

    private:
        static int idCount;
        int id;
        std::vector<Actor*> actors;
};

#endif // PLAYER_H
