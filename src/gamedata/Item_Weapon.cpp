#include <Item_Weapon.hpp>

Weapon::Weapon(const std::string scriptFile) {
	ScriptHandler sH (Weapon::scriptPath + scriptFile);
	sH.run_lua ();
	LuaTable weapon = sH.getTable("arma");
	buildItem(weapon);
	buildWeapon(weapon);
}

Weapon::Weapon(const std::string name, const std::string imgFile, const double baseCost,
        const double damage, const double fatigue, const double range)
        : Item(name, imgFile, baseCost) {
    this->damage = damage;
    this->fatigue = fatigue;
    this->range = range;
}

void Weapon::buildWeapon(LuaTable &weapon) {
	damage = weapon.getDouble("dano");
	fatigue = weapon.getDouble("fadiga");
	range = weapon.getDouble("alcance");
}

float Weapon::get_damage(){
    return this->damage;
}

float Weapon::get_fatigue(){
    return this->fatigue;
}

float Weapon::get_range(){
    return this->range;
}

const std::string Weapon::scriptPath(Item::scriptPath + "weapons/");
