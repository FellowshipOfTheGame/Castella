#include "Scene_MapEditor.hpp"

Scene_MapEditor::Scene_MapEditor()
{
    SceneControl::set_cur(SceneControl::SCENE_EDITOR); //TODO Move this code to a SceneControl or somewhere alike
    window = new Window_StartMenu("startMenu");
    GameVar::fpsCap = false;
}

Scene_MapEditor::~Scene_MapEditor()
{
    //dtor
    cout << "dtor Scene_MapEditor" << endl;
    window->~Window();
}

void Scene_MapEditor::update(){
    window->update();
}

void Scene_MapEditor::draw(SDL_Surface *screen){
    SDL_FillRect(screen, NULL, 0x00f1eab9); //0x00f1eaa9 notebook
    window->draw(screen);
}

void Scene_MapEditor::handle_scene_input(int){
    switch(input){
        default:
            break;
    }
}

void Scene_MapEditor::mouseclick(int x, int y){
    //If the mouse click was on a window rect, call window->mouseclick()
    //if (window->mouse_inside(x, y)){
        window->mouseclick(x, y);
}
