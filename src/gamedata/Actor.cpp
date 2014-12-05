#include "Actor.hpp"

//Battle consts
const int Actor::BASE_HP                = 40;
const int Actor::BASE_PRECISION         = 80;
const int Actor::BASE_STAMINA           = 100;
const float Actor::BASE_STAMINA_REGEN   = 1;

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
    //mainHand = new Weapon("espadinha"); //código provisório: ela deve ser criada no player e o actor só deve pegar o endereço

    // Spritesheet
    this->spritesheet = FileHandler::load_img("actors/" + spritesheetName);
}

Actor::~Actor()
{
    //dtor
}

int Actor::get_id(){
    return id;
}

int Actor::get_max_hp(){
    return BASE_HP*(100 + 10*vitality)/100;
}

int Actor::get_max_stamina(){
    return BASE_STAMINA*(100 + vitality)/100;
}

int Actor::get_precision(){
    return BASE_PRECISION + agility;
}

int Actor::get_evasion(){
    return agility;
}

float Actor::get_stamina_recovery(){
    //Uma porcentagem da estamina total, aumentada pela agilidade
    return BASE_STAMINA_REGEN * get_max_stamina() * (100 + agility)/100;
}

float Actor::get_phys_dmg_amplifier(){
    return (100 + 2*strength)/100;
}

float Actor::get_magic_dmg_amplifier(){
    return (100 + 2*inteligence)/100;
}

float Actor::get_phys_dmg_attenuation(){
    return (100 + strength)/100;
}

float Actor::get_magic_dmg_attenuation(){
    return (100 + inteligence)/100;
}

int Actor::idCount = 0;
