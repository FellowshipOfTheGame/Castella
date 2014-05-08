#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include <iostream>
#include <string>

#include <Weapon.hpp>
#include <Window.hpp>

#include <Game.hpp>
#include <memory>
#include <fstream>

#include <ScriptHandler.hpp>
#include <ImageHandler.hpp>

int main() {
/*
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
    putenv(strdup("SDL_VIDEO_CENTERED=1"));
    SDL_Surface *screen = SDL_SetVideoMode(Screen::WIDTH, Screen::HEIGHT, Screen::BPP, SDL_SWSURFACE);

    ScriptHandler sh = ScriptHandler();

    Window temp = Window("script/startMenu.lua", sh);

    temp.draw(screen);
    SDL_Flip(screen);

    SDL_Delay(5000);
*/

    Game *game = new Game();
    game-> start();

    return 0;
}
