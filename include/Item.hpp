/*
*   Um esboço dos itens, todos os ítens tem em comum: nome, preço e um sprite.
*/

#ifndef ITEM_HPP
#define ITEM_HPP

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include <iostream>
#include <string>

#include "ScriptHandler.hpp"

class Item
{

    private:
        std::string name, imgFile;
        double baseCost;
        SDL_Surface *img;

    public:
        //Item(const Item& that);
        Item(const char *scriptFile, ScriptHandler &sh);
        //Item(const char *name, const char *imgFile, const double baseCost);
        Item(const std::string &name, const std::string &imgFile, const double baseCost);

        /* DISABLED
        void setName(std::string rhs);
        void setImgFile(std::string rhs);
        void setBaseCost(const double &rhs);
        */

        void print();
        //void registerAtLua(lua_State *state);

};

#endif
