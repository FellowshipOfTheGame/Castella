#include <Scene_StartMenu.hpp>

Scene_StartMenu::Scene_StartMenu()
{
    //Let the SceneControl know that the current scene is now a Scene_StartMenu
    SceneControl::set_cur(SceneControl::SCENE_START_MENU);

    //Build scene objects
    title = FileHandler::load_img("Castella2.png");
    std::cout << title->format->Rmask << "        -.-" << std::endl;
    //Set the windows
    windows.push_back(new Window("startMenu.lua") );
}

Scene_StartMenu::~Scene_StartMenu()
{
    //dtor
    SDL_FreeSurface(title);
}

void Scene_StartMenu::draw(SDL_Surface *screen){
    //Set scene background
    SDL_FillRect(screen, NULL, 0x00f1eab9); //0x00f1eaa9 notebook; 0x00f1eab9 desk
    apply_surface(Screen::WIDTH/2 - 262, 100, title, screen);
    //Call super
    Scene::draw(screen);
}

void Scene_StartMenu::update(){
    Scene::update();
}

void Scene_StartMenu::escape(){
    GameVar::gameState = State::QUIT;
}

void Scene_StartMenu::handle_scene_input(int input){
    switch(input){
        default:
            break;
    }
}
