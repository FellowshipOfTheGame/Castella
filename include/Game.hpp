#ifndef GAME_H
#define GAME_H

#include <SDL/SDL.h>



//The main game engine
class Game
{
    private:
        SDL_Surface *screen; //the screen to be drawed onto
        static const char* CAPTION; //the caption - Castella - on the system window

        void setupSDL(); //setup SDL systems
        int initialize(); //initialize game world and systems
        void terminate(); //frees memory and terminate SDL systems
        void run(); //game loop

    public:
        Game();
        virtual ~Game();
        int start(); //starts the game and get it going until terminated

    protected:

};

#endif // GAME_H
