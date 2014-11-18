#include <Actor_Battler.hpp>

Actor_Battler::Actor_Battler()
{
    //ctor
    this->hp = 50; // puxa do actor
    this->mp = 30;
    this->stamina = 100;
    this->spritesheet = FileHandler::load_img("actors/actor1.png");
    this->direction = Direction::DOWN;
}

Actor_Battler::Actor_Battler(Actor* actor)
{
    this->hp = actor->get_hp();
    this->mp = actor->get_mp();
    this->stamina = actor->get_stamina();
    this->spritesheet = FileHandler::load_img("actors/actor1.png");
    this->direction = Direction::DOWN;
    //setar IA, de acordo com atributo do actor
}

Actor_Battler::~Actor_Battler()
{
    //dtor
}

SDL_Rect Actor_Battler::clip(int index){
    SDL_Rect clip;
    clip.w = spritesheet->w/3;
    clip.h = spritesheet->h/4;
    clip.x = index%3 * clip.w;
    clip.y = index/3 * clip.h;
    return clip;
}

void Actor_Battler::draw(int x, int y, int index, SDL_Surface *screen){
    index = (int)direction*3 + 1;
    apply_surface(x-clip(index).w/2, y, spritesheet, screen, &clip(index));
}

void Actor_Battler::set_allegiance(int allegiance){
    this->allegiance = allegiance;
}

int Actor_Battler::get_allegiance(){
    return allegiance;
}

void Actor_Battler::set_map_pos(int x, int y){
    map_pos.x = x;
    map_pos.y = y;
}

SDL_Rect Actor_Battler::get_map_pos(){
    return map_pos;
}

void Actor_Battler::look(Direction direction){
    this->direction = direction;
}

void Actor_Battler::set_ai(int ai){
    this->AI = ai;
}

bool Actor_Battler::is_player_controlled(){
    return !AI;
}

bool Actor_Battler::is_passable(){
    return passable;
}

int Actor_Battler::id = 0;
