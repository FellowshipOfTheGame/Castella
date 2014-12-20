#include "Actor.hpp"

//Battle consts
const int Actor::BASE_HP                = 40;
const int Actor::BASE_PRECISION         = 80;
const int Actor::BASE_STAMINA           = 100;
const float Actor::BASE_STAMINA_REGEN   = 0.01;
//Spritesheet consts
const int Actor::SPRITECLIPS_HOR = 3;   // 3 clips horizontal
const int Actor::SPRITECLIPS_VER = 4;   // 4 clips vertical
const int Actor::SPRITECLIPS_NEUTRAL_HOR_INDEX = 1;
const int Actor::SPRITECLIPS_INITIAL_INDEX = SPRITECLIPS_NEUTRAL_HOR_INDEX;    // clip inicial da imagem
const std::string Actor::IMG_FOLDER = "actors/";

Actor::Actor(){
    //default ctor
}

Actor::Actor(std::string spritesheetName, int str, int intel, int agi, int vit)
{
    //Forcener ID do personagem
    id = idCount++; //deve-se evitar que a subclasse incremente a ID
    std::cout << "Actor ID = " << id << std::endl;
    //Iniciar atributos nos valores iniciais
    strength = str;
    inteligence = intel;
    agility = agi;
    vitality = vit;
    //Equipamentos iniciais:
	mainHand = new Weapon("espadinha"); //código provisório: ela deve ser criada no player e o actor só deve pegar o endereço
    //Habilidades iniciais:
    skills.push_back(0); //atribui a habilidade de ID 0 ao repertório do personagem - TODO: adicionar campo de ID
    // Spritesheet
    this->spritesheet = FileHandler::load_img (IMG_FOLDER + spritesheetName);
    aSprite = new Animated_Sprite(IMG_FOLDER + spritesheetName, SPRITECLIPS_HOR, SPRITECLIPS_VER, SPRITECLIPS_INITIAL_INDEX);
}

Actor::~Actor()
{
    //dtor
}

int Actor::get_id(){
    return id;
}

int Actor::get_max_hp(){
    return CALL_ACTOR_FUNC (get_max_hp);
}

int Actor::get_max_stamina(){
    return CALL_ACTOR_FUNC (get_max_stamina);
}

int Actor::get_precision(){
	return CALL_ACTOR_FUNC (get_precision);
}

int Actor::get_evasion(){
    return CALL_ACTOR_FUNC (get_evasion);
}

float Actor::get_stamina_recovery(){
    //Uma porcentagem da estamina total, aumentada pela agilidade
    return CALL_ACTOR_FUNC (get_stamina_recovery);
}

float Actor::get_phys_dmg_amplifier(){
    return CALL_ACTOR_FUNC (get_phys_dmg_amplifier);
}

float Actor::get_magic_dmg_amplifier(){
    return CALL_ACTOR_FUNC (get_magic_dmg_amplifier);
}

float Actor::get_phys_dmg_attenuation(){
    return CALL_ACTOR_FUNC (get_phys_dmg_attenuation);
}

float Actor::get_magic_dmg_attenuation(){
    return CALL_ACTOR_FUNC (get_magic_dmg_attenuation);
}

float Actor::get_weapon_damage(){
    return mainHand->get_damage();
}

void Actor::registerOnLua (lua_State *L) {
	using namespace luabind;

	module (L) [
		class_<Actor> ("Actor")
			.def_readonly ("strength", &Actor::strength)
			.def_readonly ("inteligence", &Actor::inteligence)
			.def_readonly ("agility", &Actor::agility)
			.def_readonly ("vitality", &Actor::vitality)
	];
	ScriptHandler::send_to_lua<int> (L, "BASE_PRECISION", BASE_PRECISION);
	ScriptHandler::send_to_lua<int> (L, "BASE_HP", BASE_HP);
	ScriptHandler::send_to_lua<int> (L, "BASE_STAMINA", BASE_STAMINA);
	ScriptHandler::send_to_lua<float> (L, "BASE_STAMINA_REGEN", Actor::BASE_STAMINA_REGEN);
}
ScriptHandler Actor::sH;

int Actor::idCount = 0;
