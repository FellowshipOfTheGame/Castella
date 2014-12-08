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
}

void Skill::add_skill(std::string skillScript, std::string skillName){
    skills.push_back(Skill(skillScript, skillName));
}

std::vector<Skill> Skill::skills;

std::string Skill::scriptPath = "script/skills/";
