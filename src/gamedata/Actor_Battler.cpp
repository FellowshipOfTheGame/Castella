#include <Actor_Battler.hpp>
#include <MapTile.hpp>

// FORWARD DECLARATIONS ---------->
class Scene_Battle{
    public:
        static int frame;
};

class Skill{
    public:
        static std::vector<Skill*> skills;
        int get_cost(Actor_Battler *battler);
        int get_damage(Actor_Battler *battler);
};
// <-------------------------------

const int Actor_Battler::WALKING_TIME = 7;

Actor_Battler::Actor_Battler(Actor* actor){
    //Copia o ator base
    Actor_Battler *battler = this;
    *battler = *( (Actor_Battler*)actor );
    //Ajusta os estados
    dead = false;
    cout << " DEAD: " << (int)dead << endl;
    //Inicializa HP e Estamina
    this->hp = get_max_hp();
    this->stamina = 0;
    //this->spritesheet = FileHandler::load_img("actors/actor1.png");
    this->direction = Direction::DOWN;
    //setar IA, de acordo com atributo do actor
    walking = 0;
}

Actor_Battler::~Actor_Battler()
{
    //dtor
}

void Actor_Battler::draw(int x, int y, int index, SDL_Surface *screen){
    index = (int)direction * SPRITECLIPS_HOR + SPRITECLIPS_NEUTRAL_HOR_INDEX;
    if (walking == 0){
        aSprite->set_position(x , y);
    }
    else {
        walking--;
    }
    aSprite->draw(screen);
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
    //Muda o clip do battler para corresponder à direção
    int clip = (int)direction * SPRITECLIPS_HOR + SPRITECLIPS_NEUTRAL_HOR_INDEX;
    aSprite->animate({clip}, 1, 1);
}

void Actor_Battler::walk(Direction direction){
    // Cancela a ação caso ainda esteja executando outra
    if (walking > 1) return; // permite ao jogador executar a ação ainda no final da movimentação
    // Vira-se na direção apropriada
    look(direction);
    // Adicionar verificação de passabilidade do tile...
    //Caso seja passável, verificar custo e tentar executar a movimentação
    int cost = (30)/3; // estabelecer custo em função do peso e da força
    if (use_stamina(cost)){ //se tiver estamina suficiente, gasta e executa
        walking = WALKING_TIME;
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
        aSprite->translate( (x+0.5) * MapTile::TILESIZE, y* MapTile::TILESIZE-18, walking);
        int clipRef = (int)direction * SPRITECLIPS_HOR + 1;
        aSprite->animate({clipRef-1, clipRef, clipRef+1, clipRef}, walking, 1); //atrelado à subdivisão da spritesheet - TODO: utilizar as consts para calcular os índices
        set_map_pos(x, y);
    }
}

bool Actor_Battler::use_skill(int skill_id){
    // Cancela a ação caso j esteja usando outra
    if (walking) return false;
    Skill *sk = Skill::skills.at(skill_id);
    int cost = sk->get_cost(this);
    std::cout << "Use Skill, cost:" << cost << std::endl;
    if ( enough_stamina(cost) ){
        SDL_Rect target;
        target.x = map_pos.x;
        target.y = map_pos.y;
        switch (direction){
            case Direction::DOWN:
                target.y++;
                break;
            case Direction::UP:
                target.y--;
                break;
            case Direction::LEFT:
                target.x--;
                break;
            case Direction::RIGHT:
                target.x++;
                break;
        }
        use_stamina(cost);
        skillDamageBuffer = sk->get_damage(this);
        skillTargetBuffer = target;
        return true;
    }
    return false;
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
    cout << "DEAD: " << (int)dead << endl;
    if (!dead){
        stamina += CALL_ACTOR_FUNC (get_stamina_recovery);
        float max_stamina = CALL_ACTOR_FUNC (get_max_stamina);
        if (stamina >= max_stamina){
            stamina = max_stamina;
        }
    }
    else { // morto
        hp = 0;
        stamina = 0;
    }
}

float Actor_Battler::get_stamina_percent(){
    return (stamina / CALL_ACTOR_FUNC (get_max_stamina)) * 100;
}

int Actor_Battler::get_hp(){
    return hp;
}

bool Actor_Battler::use_stamina(int cost){
    if (enough_stamina(cost)){
        stamina -= cost;
        return true;
    }
    else return false;
}

bool Actor_Battler::enough_stamina(int cost){
    if (stamina >= cost){
        return true;
    }
    else return false;
}

void Actor_Battler::take_damage(int damage){
    hp -= damage;
    //Antes devem seguir possíveis redutores de dano, como:
    // atenuação de dano físico;
    // redução pela armadura;
    // etc
    //Depois, devem ser feitos outros testes, como de morte
    if (hp <= 0){
        //Flag de morto
        dead = true;
        //Força atualização os valores de vida e estamina
        update();
        //Muda a spritesheet para a de morto
        std::string deadSpriteSheet = "skull.png";
        this->spritesheet = FileHandler::load_img ("actors/" + deadSpriteSheet);
        aSprite = new Animated_Sprite("actors/" + deadSpriteSheet);
    }
}

int Actor_Battler::get_skill_damage_buffer(){
    return skillDamageBuffer;
}

SDL_Rect Actor_Battler::get_skill_target_buffer(){
    return skillTargetBuffer;
}

bool Actor_Battler::is_acting(){
    //TODO - Adicionar ação de usar skills
    return (bool)walking;
}

bool Actor_Battler::is_dead(){
    return dead;
}


void Actor_Battler::registerOnLua (lua_State *L) {
	using namespace luabind;

	Actor::registerOnLua (L);

	module (L) [
		class_<Actor_Battler, Actor> ("Actor_Battler")
	];
}
