#include <SDL.h>
#include <SDL_image.h>

#include <iostream>
#include <string>

#include "Weapon.hpp"
#include "Window.hpp"

#include "Game.hpp"
#include <memory>
#include <fstream>

#include "ScriptHandler.hpp"
#include "ImageHandler.hpp"

int main() {

    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
    putenv(strdup("SDL_VIDEO_CENTERED=1"));
    SDL_Surface *screen = SDL_SetVideoMode(Screen::WIDTH, Screen::HEIGHT, Screen::BPP, SDL_SWSURFACE);

    ScriptHandler sh = ScriptHandler();

    Window temp = Window("startMenu.lua", sh);
    temp.buttonList[0].callback();

/*
    Item temp = Item("pizza.lua", sh);
    std::cout << "Item address: " << &temp << std::endl;
    temp.print();
*/

/*
    std::cout << "Tamanho de Item:\t" << sizeof(Item) << std::endl
                << "Tamanho de LuaTable:\t" << sizeof(LuaTable) << std::endl
                << "Tamanho de Weapon:\t" << sizeof(Weapon) << std::endl
                << "Tamanho de String:\t" << sizeof(std::string) << std::endl
                << "Tamanho de SDL_Rect:\t" << sizeof(SDL_Rect) << std::endl;
*/
}
