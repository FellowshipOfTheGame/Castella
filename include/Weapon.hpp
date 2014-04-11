/*
* Um esboço das armas TODO: Definir tipos de dano, encantos(Aumenta velocidade, cega o inimigo, etc), adicionar gasto de stamina por ataque e "pontos de defesa" da arma.
*/

#ifndef _WEAPON_HPP_
#define _WEAPON_HPP_

#include "Item.hpp"

class weapon : public item {

    private:
        int damage;
        int fatigue;
        int range;

    public:
        weapon(const char *name, const int baseCost, SDL_Surface *img, const int damage, const int fatigue, const int range);
        weapon(const std::string *name, const int baseCost, SDL_Surface *img, const int damage, const int fatigue, const int range);
};

#endif
