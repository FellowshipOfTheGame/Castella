#include "Skill.hpp"

Skill::Skill () {}

Skill::Skill(std::string skillScript, std::string skillName)
{
    ScriptHandler sH (Skill::scriptPath + skillScript);
    sH.run_lua();
    LuaTable skill = sH.getTable (skillName);
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

void Skill::add_skill_table (std::string skillScript, std::string tableName) {
    ScriptHandler sH (Skill::scriptPath + skillScript);
    sH.run_lua();
	
	LuaTable table = sH.getTable (tableName);

	// a cada table lá dentro
	for (LuaObject obj : table) {
		LuaTable skill_table (obj);
		// pega  skill, o constrói e adiciona
		Skill *S = new Skill;
		S->build_skill (skill_table);
		skills.push_back (S);
	}
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

void Skill::destroy_all_skills () {
	for (auto skill : skills) {
		delete skill;
	}
}

std::vector<Skill*> Skill::skills;

std::string Skill::scriptPath = "script/skills/";
