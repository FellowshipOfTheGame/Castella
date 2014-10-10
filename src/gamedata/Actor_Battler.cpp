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
    apply_surface(x-clip(index).w/2, y, spritesheet, screen, &clip(index));
}

void Actor_Battler::set_map_pos(int x, int y){
    map_pos.x = x;
    map_pos.y = y;
}

SDL_Rect Actor_Battler::get_map_pos(){
    return map_pos;
}

bool Actor_Battler::is_passable(){
    return passable;
}
