/**
* @brief Base para os itens do jogo.
* Um esboço dos ítens, todos os ítens tem em comum: nome, preço e um sprite.
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

	protected:
		static const std::string scriptPath;
		
    public:
        Item(const std::string scriptFile);
        Item(const std::string name = "none", const std::string imgFile = "none", const double baseCost = 0.0);
		
		void buildItem(LuaTable &item);
		
};

#endif
