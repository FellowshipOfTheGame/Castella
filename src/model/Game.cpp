#include "Game.hpp"

#include <iostream>
#include <cstdio>
#include <ctime>
#include <cstring>

#include "Screen.h"
#include "GameStructure.hpp"

#include "Timer.hpp"

#include "Input.hpp"

#include "SceneControl.hpp"
#include "SceneHeaders.hpp"

#include "World.hpp"
#include "Actor.hpp"
#include "Skill.hpp"


Game::Game()
{
    Scene::scene = NULL;
}

Game::~Game(){
    cout << "dtor Game" << endl;
}

const char* Game::CAPTION = "Castella";

void Game::setupSDL(){
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
    Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 );
    SDL_WM_SetCaption(CAPTION, NULL);
    putenv(strdup("SDL_VIDEO_CENTERED=1"));
    screen = SDL_SetVideoMode(Screen::WIDTH, Screen::HEIGHT, Screen::BPP, SDL_SWSURFACE); // | SDL_RESIZABLE | SDL_FULLSCREEN
    if (screen == NULL){} //Error
}

void Game::terminate(){
    SDL_FreeSurface(screen);
    Mix_CloseAudio();
    TTF_Quit();
    SDL_Quit();

	Skill::destroy_all_skills ();
}

int Game::initialize(){
    //Random seed
    std::srand(std::time(0));
    //Setup the SDL system
    setupSDL();
    //Set Game State
    GameVar::gameState = State::MAIN;
    //Sets the first game scene
	SceneControl::set_next (Scenes::SCENE_START_MENU);
    SceneControl::update ();
    //Creates the game world
    World::get_world();
    //If all went right
    return 0;
}

int Game::start(){
    //Setup the game world, gamestate, scene and SDL systems
    if(initialize() == -1) return -1;
    //Runs the game loop
    run();
    //Terminate SDL systems and frees memory
    terminate();
    return 0;
}

void Game::run(){
    //FPS Caps
    GameVar::fpsCap = true;
    Timer timer;
    Timer msTimer;
    msTimer.start();
    int frameCounter = 0;

    char caption[20];
    char stringBuffer[4];

    //Game Loop
    while (GameVar::gameState != State::QUIT){
        timer.start();

        /*Scene update*/
        SceneControl::update(); //changes scene if necessary

        /*Input*/
        //cout << "---------INPUT" << endl;
        Scene::scene->handle_input();

        /*Logic*/
        //cout << "---------LOGIC" << endl;
        Scene::scene->update();

        /*Render*/
        //cout << "---------RENDER" << endl;
        Scene::scene->draw(screen);
        SDL_Flip(screen);

        //Count the fps
        frameCounter ++;
        if (msTimer.get_ticks() >= 500){ //(one) half second has gone
            strcpy(caption, "Castella - FPS: ");
            frameCounter *= 2; // half second, double rate
			sprintf (stringBuffer, "%d", frameCounter);
            //itoa(frameCounter, stringBuffer, 10);
            strcat(caption, stringBuffer);
            SDL_WM_SetCaption(caption, NULL);
            msTimer.start();
            frameCounter = 0;
        }
        //End count the fps - TODO - review this code and consider splitting the method

        //Caps the fps
        if(GameVar::fpsCap) {
			// Verifica tempo a esperar, e espera se tal tempo é positivo (se
			// for negativo, é pq faltou tempo =P)
			int remaining_ms = (1000 / Screen::FPS) - timer.get_ticks ();
			if (remaining_ms > 0) {
				SDL_Delay (remaining_ms);
			}
		}
    }
    //Game Loop End
}

