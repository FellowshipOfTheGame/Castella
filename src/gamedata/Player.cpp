#include "Player.hpp"

Player::Player()
{
    id = idCount;
    for (int i=0; i<3; i++){
        actors.push_back(new Actor());
    }
}

Player::~Player()
{
    //dtor
}

std::vector<Actor*> Player::get_actors(){
    return this->actors;
}

int Player::get_id(){
    return id;
}

int Player::idCount = 0;
