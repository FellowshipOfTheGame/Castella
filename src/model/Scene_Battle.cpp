#include <Scene_Battle.hpp>

Scene_Battle::Scene_Battle() : battleMap (20, 12)
{
    SceneControl::set_cur (Scenes::SCENE_BATTLE); //TODO Move this code to a SceneControl or somewhere alike

	Player **players = (Player **) Scene::ptr;

	load_battlers (players[0], players[1]);
}

Scene_Battle::~Scene_Battle()
{
    //dtor
}

void Scene_Battle::update(){Scene::update();}

void Scene_Battle::draw(SDL_Surface *screen){
    //Super
    Scene::draw(screen);
    battleMap.draw(screen, battlersTeam1, battlersTeam2);
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

    for (auto actor : actors1) {
        battlersTeam1.push_back(new Actor_Battler(actor));
    }

    for (auto actor : actors2) {
        battlersTeam2.push_back(new Actor_Battler(actor));
    }
}
