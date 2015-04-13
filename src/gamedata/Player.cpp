#include "Player.hpp"

//Cria o player, garantindo que ele já receba um actor (o líder) no seu construtor
Player::Player(Actor* actor) : Player (vector<Actor *> {actor}) {}

Player::Player (vector<Actor *> actors) : actors (actors) {
    id = idCount;
}

Player::~Player()
{

}

std::vector<Actor*> Player::get_actors(){
    return this->actors;
}

int Player::get_id(){
    return id;
}

void Player::add_actor(Actor *actor){
    actors.push_back (actor);
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

void Player::registerOnLua (lua_State *L) {
	using namespace luabind;

	Actor::registerOnLua (L);

	module (L) [
		class_<Player> ("Player")
			.def_readonly ("id", &Player::id)
			.def ("add_actor", &Player::add_actor)
	];
}


Reign * Player::getReign () {
	return &reign;
}


Region * Player::getRegion () {
	return current_pos;
}


void Player::setRegion (Region *reg) {
	current_pos = reg;
}


void Player::turn_cycle () {
	reign.turn_cycle ();
}


int Player::idCount = 0;
