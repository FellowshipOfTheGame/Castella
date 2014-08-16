#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include <iostream>
#include <string>

#include <memory>
#include <fstream>

#include <Game.hpp>
#include <ScriptHandler.hpp>
#include <ImageHandler.hpp>
#include <Window.hpp>

int main() {
    /*
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
    putenv(strdup("SDL_VIDEO_CENTERED=1"));
    SDL_Surface *screen = SDL_SetVideoMode(Screen::WIDTH, Screen::HEIGHT, Screen::BPP, SDL_SWSURFACE);

    //ScriptHandler *sh = new ScriptHandler();

    //Window *temp = new Window("startMenu.lua");

    //temp.draw(screen);
    SDL_Flip(screen);

    SDL_Delay(5000);

    //delete sh;
    SDL_FreeSurface(screen);
    TTF_Quit();
    SDL_Quit();
*/

    Game *game = new Game();
    game-> start();

    delete game;

    return 0;
}
