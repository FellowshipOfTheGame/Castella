#include <Scene_Battle.hpp>

Scene_Battle::Scene_Battle()
{
    SceneControl::set_cur(SceneControl::SCENE_BATTLE); //TODO Move this code to a SceneControl or somewhere alike

    battleMap = new Map_Battle(20,12);
}

Scene_Battle::~Scene_Battle()
{
    //dtor
    battleMap->~Map_Battle();
}

void Scene_Battle::update(){Scene::update();}

void Scene_Battle::draw(SDL_Surface *screen){
    //Super
    Scene::draw(screen);
    battleMap->draw(screen);
}

void Scene_Battle::mouseclick(int x, int y){
    //Super
    Scene::mouseclick(x, y);
    //Extention
}

void Scene_Battle::escape(){
    SceneControl::set_next(SceneControl::SCENE_WORLD);
}

void Scene_Battle::handle_scene_input(int input){
    switch(input){
        default:
            break;
    }
}
