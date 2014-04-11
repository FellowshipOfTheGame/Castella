#include "Weapon.hpp"

weapon::weapon(const char *name, const int baseCost, SDL_Surface *img, const int damage, const int fatigue, const int range)
        : item(name, baseCost, img) {
    this->damage = damage;
    this->fatigue = fatigue;
    this->range = range;
};

weapon::weapon(const std::string *name, const int baseCost, SDL_Surface *img, const int damage, const int fatigue, const int range)
        : item(name, baseCost, img) {
    this->damage = damage;
    this->fatigue = fatigue;
    this->range = range;
};
