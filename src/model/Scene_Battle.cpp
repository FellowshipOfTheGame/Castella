#include <Scene_Battle.hpp>

Scene_Battle::Scene_Battle()
{
    SceneControl::set_cur (Scenes::SCENE_BATTLE); //TODO Move this code to a SceneControl or somewhere alike

    battleMap = new Map_Battle(20,12);
}

Scene_Battle::Scene_Battle(Player* player1, Player* player2)
{
    SceneControl::set_cur (Scenes::SCENE_BATTLE); //TODO Move this code to a SceneControl or somewhere alike
    battleMap = new Map_Battle(20,12);

    load_battlers(player1, player2);
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
    battleMap->draw(screen, battlersTeam1, battlersTeam2);
}

void Scene_Battle::mouseclick(int x, int y){
    //Super
    Scene::mouseclick(x, y);
    //Extention
}

void Scene_Battle::escape(){
    SceneControl::exitScene ();
}

void Scene_Battle::handle_scene_input(int input){
    switch(input){
        default:
            break;
    }
}

void Scene_Battle::load_battlers(Player* player1, Player* player2){
    std::vector <Actor*> actors1 = player1->get_actors();
    std::vector <Actor*> actors2 = player2->get_actors();

    std::vector<Actor*>::iterator actorIt;

    for (actorIt = actors1.begin(); actorIt != actors1.end(); actorIt++){
        battlersTeam1.push_back(new Actor_Battler(*actorIt));
    }
    for (actorIt = actors2.begin(); actorIt != actors2.end(); actorIt++){
        battlersTeam2.push_back(new Actor_Battler(*actorIt));
    }
}
