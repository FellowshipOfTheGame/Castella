#include "Skill.hpp"

Skill::Skill(std::string skillScript, std::string skillName)
{
    ScriptHandler sH (Skill::scriptPath + skillScript);
    sH.run_lua();
    LuaTable skill = sH.getTable(skillName.c_str());
    build_skill(skill);
}

Skill::~Skill()
{
    //dtor
}

void Skill::build_skill(LuaTable &skill){
    name = skill.getString("nome");
    weapon_based = (bool)skill.getInt("usaArma");
    base_cost = skill.getDouble("custoBase");
    relative_cost = skill.getDouble("custoCarga");
    damage = skill.getDouble("dano");
    range = skill.getInt("alcance");
    area = skill.getInt("area");
    std::cout << "Name: " << name << std::endl;
    std::cout << "Base Cost: " << base_cost << std::endl;
}

void Skill::add_skill(std::string skillScript, std::string skillName){
    skills.push_back(new Skill(skillScript, skillName));
}

int Skill::get_cost(Actor_Battler *battler){
    std::cout << "Name: " << name << std::endl;
    float attenuation = battler->get_phys_dmg_attenuation(); //usar int pra magias e str pra ataques - FIX
    std::cout << "Name: " << name << std::endl;
    float cost = base_cost + (int)weapon_based*relative_cost*attenuation;
    std::cout << "Name: " << name << std::endl;
    return cost;
}

int Skill::get_damage(Actor_Battler *battler){
    float modifier = battler->get_phys_dmg_amplifier(); // se for físico
    std::cout << "Modifier: " << modifier << endl;
    float dmg = this->damage;
    std::cout << dmg << endl;
    if (weapon_based){
        dmg *= battler->get_weapon_damage();
        std::cout << dmg << endl;
    }
    return dmg*modifier;
}

std::vector<Skill*> Skill::skills;

std::string Skill::scriptPath = "script/skills/";
