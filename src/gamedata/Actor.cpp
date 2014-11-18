#include "Actor.hpp"

Actor::Actor()
{
    id = idCount;
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

int Actor::idCount = 0;
