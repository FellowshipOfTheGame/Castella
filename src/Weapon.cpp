#include "Weapon.hpp"

Weapon::Weapon(const Weapon &that) : Item( that ) {
    this->damage = that.damage;
    this->fatigue = that.fatigue;
    this->range = that.range;
}

/*
Weapon::Weapon(const char *name, const char *imgFile, const double baseCost,
                const double damage, const double fatigue, const double range)
        : Item(name, imgFile, baseCost) {
    this->damage = damage;
    this->fatigue = fatigue;
    this->range = range;
}
*/

Weapon::Weapon(const std::string &name, const std::string &imgFile, const double baseCost,
                const double damage, const double fatigue, const double range)
        : Item(name, imgFile, baseCost) {
    this->damage = damage;
    this->fatigue = fatigue;
    this->range = range;
}
