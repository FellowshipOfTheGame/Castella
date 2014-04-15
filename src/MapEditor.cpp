#include "MapEditor.hpp"
#include <iostream>

MapEditor::Game()
{
    Scene::scene = NULL;
}

const char* MapEditor::CAPTION = "Castella Map Editor";

void MapEditor::setupSDL(){
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
    Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 );
    SDL_WM_SetCaption(CAPTION, NULL);
    putenv(strdup("SDL_VIDEO_CENTERED=1"));
    screen = SDL_SetVideoMode(Screen::WIDTH, Screen::HEIGHT, Screen::BPP, SDL_SWSURFACE); // | SDL_RESIZABLE | SDL_FULLSCREEN
    if (screen == NULL){} //Error
}

void MapEditor::terminate(){
    SDL_FreeSurface(screen);
    Mix_CloseAudio();
    TTF_Quit();
    SDL_Quit();
}

int MapEditor::initialize(){
    //Setup the SDL system
    setupSDL();
    //Set Game State
    GameVar::gameState = State::MAIN;
    //Load images (should be grouped and loaded accordingly to game states or scenes)
    if(FileHandler::load_button_images() == -1) return -1; //If could not load images
    //Sets the first game scene
    Scene::scene = new Scene_MapEditor();
    //Creates the game world
    World::get_world();
    //If all went right
    return 0;
}

int MapEditor::start(){
    //Setup the game world, gamestate, scene and SDL systems
    if(initialize() == -1) return -1;
    //Runs the game loop
    run();
    //Terminate SDL systems and frees memory
    terminate();
    return 0;
}

void MapEditor::run(){
    //FPS Caps
    GameVar::fpsCap = true;
    Timer timer;

    //Game Loop
    while (GameVar::gameState != State::QUIT){
        timer.start();

        /*Scene update*/ //TODO - MOVE THE SCENE UPDATE TO SceneControl CLASS
        if(SceneControl::get_next() != SceneControl::SCENE_NULL){ //scene must change
            switch(SceneControl::get_next()){
                case SceneControl::SCENE_WORLD: //changes scene to Scene_World
                    Scene::scene = new Scene_World();
                    break;
                case SceneControl::SCENE_START_MENU:
                    Scene::scene = new Scene_StartMenu();
                    break;
            }
        }

        /*Input*/
        Scene::scene->handle_input();

        /*Logic*/
        Scene::scene->update();

        /*Render*/
        SDL_FillRect(screen, NULL, 00000000); //clear the screen
        Scene::scene->draw(screen);
        SDL_Flip(screen);

        //Caps the fps
        if(GameVar::fpsCap) while(timer.get_ticks() < 1000/Screen::FPS){/*Wait*/}
    }

    //Game Loop End
}
