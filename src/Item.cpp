#include "Item.hpp"

item::item(const char *name, const int baseCost, SDL_Surface *img) {
    this->name = std::string(name);
    this->baseCost = baseCost;
    this->img = img;
}

item::item(const std::string *name, const int baseCost, SDL_Surface *img) {
    this->name = std::string(*name);
    this->baseCost = baseCost;
    this->img = img;
}
