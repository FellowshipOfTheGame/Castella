#include <SceneControl.hpp>
#include <SceneHeaders.hpp>

SceneControl::SceneControl()
{
    //ctor
}

SceneControl::~SceneControl()
{
    //dtor
}

int SceneControl::get_next(){
    return nextScene;
}
void SceneControl::set_next(Scenes next){
    nextScene = next;
}
int SceneControl::get_cur(){
    return curScene;
}
void SceneControl::set_cur(Scenes cur){
    set_next(SceneControl::SCENE_NULL);
    curScene = cur;
}

void SceneControl::update(){
    //TODO - Should handle scene change
    if(SceneControl::get_next() != SceneControl::SCENE_NULL){ //scene must change
            Scene::scene->~Scene();
            //delete Scene::scene;
            GameVar::fpsCap = true; //FIXME - this line is for test, only, and should be removed
        switch(get_next()){
            case SCENE_WORLD:
                Scene::scene = new Scene_World();
                break;
            case SCENE_START_MENU:
                Scene::scene = new Scene_StartMenu();
                break;
            case SCENE_EDITOR:
                Scene::scene = new Scene_MapEditor();
                break;
            case SCENE_BATTLE:
                Scene::scene = new Scene_Battle();
                break;
        }
    }
}


int SceneControl::nextScene = SCENE_NULL;
int SceneControl::curScene = SCENE_NULL; //must be set in Game.cpp
