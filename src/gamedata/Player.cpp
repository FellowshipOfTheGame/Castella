#include "Player.hpp"

//Cria o player, garantindo que ele já receba um actor (o líder) no seu construtor
Player::Player(Actor* actor)
{
    id = idCount;
    actors.push_back(actor);
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

void Player::add_actor(Actor *actor){
    actors.push_back(actor);
}

void Player::remove_actor(Actor *actor){
    //Remove o actor, caso o player tenha pelo menos 2 deles
    if (actors.size() > 2){
        for (auto it = actors.begin(); it != actors.end(); it++){
            if (actor->get_id() == (*it)->get_id()){
                actors.erase(it);
            }
        }
    }
}

int Player::idCount = 0;
