#include "Game.hpp"
#include <iostream>
#include <memory>
#include <fstream>

#include "ScriptHandler.hpp"
#include "Window.hpp"
#include "ImageHandler.hpp"

void func(){}

int main(int argc, char* argv[]){

    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
    Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 );
    putenv(strdup("SDL_VIDEO_CENTERED=1"));
    SDL_Surface *screen = SDL_SetVideoMode(Screen::WIDTH, Screen::HEIGHT, Screen::BPP, SDL_SWSURFACE); // | SDL_RESIZABLE | SDL_FULLSCREEN
    if (screen == NULL){} //Error


    int r = 0;

    for(int i=0; i < 1; i++){ //1000
        //cout << " - " << endl;

    //    int i = 1;
    //    ofstream save("save/test1");
    //    save << i << endl;


    }




    {
        std::auto_ptr<Game> game (new Game);
        r = (int)(100*game->start());
    }

    //system("PAUSE");
    return r;
}


