#include "Player.hpp"

Player::Player()
{
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

Player::get_id(){
    return id;
}

int Player::id = 0;
