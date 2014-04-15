/*
* Um esboço das armas TODO: Definir tipos de dano, encantos(Aumenta velocidade, cega o inimigo, etc), adicionar gasto de stamina por ataque e "pontos de defesa" da arma.
*/

#ifndef WEAPON_HPP
#define WEAPON_HPP

#include "Item.hpp"

class Weapon : public Item
{

    private:
        double damage;
        double fatigue;
        double range;

    public:
        Weapon(const Weapon &that);
        /*Weapon(const char *name, const char *imgFile, const double baseCost,
                const double damage, const double fatigue, const double range);*/
        Weapon(const std::string &name, const std::string &imgFile, const double baseCost,
                const double damage, const double fatigue, const double range);
};

#endif
