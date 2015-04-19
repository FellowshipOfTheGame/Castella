#include "Scene_StartMenu.hpp"

Scene_StartMenu::Scene_StartMenu()
{
    //Let the SceneControl know that the current scene is now a Scene_StartMenu
    SceneControl::set_cur(Scenes::SCENE_START_MENU);

    //Build scene objects
    title = FileHandler::load_img("Castella2.png");
	assert (title);
    //std::cout << title->format->Rmask << "        -.-" << std::endl;
    //Set the windows
    windows.push_back(new Window ("startMenu.lua", &Callback::registerCallbacks) );
}

Scene_StartMenu::~Scene_StartMenu()
{
    //dtor
    SDL_FreeSurface(title);
}

void Scene_StartMenu::redraw(){
	//Set scene background
	fill_surface (image, {0xf1, 0xea, 0xb9});
	apply_surface(Screen::WIDTH/2 - 262, 100, title, image);
}

void Scene_StartMenu::update(){
    Scene::update();
}

void Scene_StartMenu::escape(){
    GameVar::gameState = State::QUIT;
}

void Scene_StartMenu::handle_scene_input(int input){
    //switch(input){
        //default:
            //break;
    //}
}
