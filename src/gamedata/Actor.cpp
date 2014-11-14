#include "Actor.hpp"

Actor::Actor()
{
    hp = 50;
    mp = 50;
    stamina = 100;
}

Actor::~Actor()
{
    //dtor
}

int Actor::get_hp(){
    return hp;
}

int Actor::get_mp(){
    return mp;
}

int Actor::get_stamina(){
    return stamina;
}

int Actor::id = 0;
