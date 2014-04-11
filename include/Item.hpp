/*
*   Um esboço dos itens, todos os ítens tem em comum: nome, preço e um sprite.
*/

#ifndef _ITEM_HPP_
#define _ITEM_HPP_

#include <SDL.h>
#include <SDL_image.h>
#include <string>

class item {

    private:
        std::string name;
        int baseCost;
        SDL_Surface *img;

    public:
        item(const char *name, const int baseCost, SDL_Surface *img);
        item(const std::string *name, const int baseCost, SDL_Surface *img);

};

#endif
