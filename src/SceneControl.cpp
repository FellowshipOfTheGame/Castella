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

Scenes SceneControl::get_next(){
    return nextScene;
}
void SceneControl::set_next(Scenes next){
    nextScene = next;
}

void SceneControl::exitScene () {
	set_next (Scenes::SCENE_EXIT);
}

void SceneControl::popScene () {
	delete (Scene::scenes.top ());
	Scene::scenes.pop ();
	Scene::scene = Scene::scenes.top ();
}

Scenes SceneControl::get_cur(){
    return curScene;
}
void SceneControl::set_cur(Scenes cur){
    set_next(Scenes::SCENE_NULL);
    curScene = cur;
}

void SceneControl::update(){
    //scene must change
    if (SceneControl::get_next() != Scenes::SCENE_NULL) {
		GameVar::fpsCap = true; //FIXME - this line is for test, only, and should be removed
		
		Scene *aux;
        switch(get_next()) {
            case Scenes::SCENE_WORLD:
                aux = new Scene_World();
                break;
            case Scenes::SCENE_START_MENU:
                aux = new Scene_StartMenu();
                break;
            case Scenes::SCENE_EDITOR:
                aux = new Scene_MapEditor();
                break;
            case Scenes::SCENE_BATTLE:
                aux = new Scene_Battle();
                break;
			case Scenes::SCENE_REGION:
				aux = new Scene_Region ();
				break;
			// saindo da cena
			case Scenes::SCENE_EXIT:
				popScene ();
				set_next (Scenes::SCENE_NULL);
			default:	// nada interessante, só vaza
				return;
        }
        
        Scene::scenes.push (aux);
        Scene::scene = Scene::scenes.top ();
    }
}


Scenes SceneControl::nextScene = Scenes::SCENE_NULL;
Scenes SceneControl::curScene = Scenes::SCENE_NULL; //must be set in Game.cpp
