#include <Actor_Battler.hpp>

Actor_Battler::Actor_Battler(Actor* actor)
{
	Actor_Battler *battler = this;
	*battler = *( (Actor_Battler*)actor );
	this->hp = get_max_hp();
	this->stamina = 0;
	//this->spritesheet = FileHandler::load_img("actors/actor1.png");
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
    //Código provisório para simular uma HUD em texto:
    write_text(x, y+clip(index).h, screen, to_string( (int)get_stamina_percent() ) +"%", {0,0,0}, 0.5);
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

void Actor_Battler::walk(Direction direction){
    // Adicionar verificação de passabilidade do tile...
    //Caso seja passável, verificar custo e tentar executar a movimentação
    int cost = (30)/3; // estabelecer custo em função do peso e da força
    if (use_stamina(cost)){ //se tiver estamina suficiente, gasta e executa
        look(direction);
        int x = map_pos.x;
        int y = map_pos.y;
        switch (direction){
            case Direction::DOWN:
                y++;
                break;
            case Direction::UP:
                y--;
                break;
            case Direction::LEFT:
                x--;
                break;
            case Direction::RIGHT:
                x++;
                break;
        }
        set_map_pos(x, y);
    }
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

void Actor_Battler::update(){
    stamina += CALL_ACTOR_FUNC (get_stamina_recovery);

	float max_stamina = CALL_ACTOR_FUNC (get_max_stamina);
    if (stamina >= max_stamina){
        stamina = max_stamina;
    }
}

float Actor_Battler::get_stamina_percent(){
    return (stamina / CALL_ACTOR_FUNC (get_max_stamina)) * 100;
}

bool Actor_Battler::use_stamina(int cost){
    if (stamina >= cost) {
        stamina -= cost;
        return true;
    }
    else return false;
}

void Actor_Battler::registerOnLua (lua_State *L) {
	using namespace luabind;

	Actor::registerOnLua (L);

	module (L) [
		class_<Actor_Battler, Actor> ("Actor_Battler")
	];
}
