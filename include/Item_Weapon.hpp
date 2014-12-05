/**
* Um esboço das armas TODO: Definir tipos de dano, encantos(Aumenta velocidade, cega o inimigo, etc),
* adicionar gasto de stamina por ataque e "pontos de defesa" da arma.
*/

#ifndef ITEM_WEAPON_HPP
#define ITEM_WEAPON_HPP

#include "Item.hpp"

class Weapon : public Item
{

    private:
        double damage;
        double fatigue;
        double range;

	protected:
		static const std::string scriptPath;

    public:
        Weapon(const std::string scriptFile);
        Weapon(const std::string name, const std::string imgFile,
				const double baseCost = 0.0, const double damage = 0.0,
				const double fatigue = 0.0, const double range = 0.0);

		void buildWeapon(LuaTable &weapon);
};

#endif
