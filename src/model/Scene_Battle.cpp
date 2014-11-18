#include <Scene_Battle.hpp>

Scene_Battle::Scene_Battle() : battleMap (20, 12)
{
    SceneControl::set_cur (Scenes::SCENE_BATTLE); //TODO Move this code to a SceneControl or somewhere alike

	//Player *players = (Player *) Scene::ptr; //Recebe os players do ponteiro estático da scene

    //Código provisório nesta classe para inicializar os players
    Player players[2];
	players[0] = Player();
	players[1] = Player();

    std::cout << "loading battlers... ";
	load_battlers (&players[0], &players[1]);
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

    player1 = new Player();
    player2 = new Player();

    std::cout << "loading battlers";

    std::vector <Actor*> actors1 = player1->get_actors();
    std::vector <Actor*> actors2 = player2->get_actors();

    int i=0;
    for (auto actor : actors1) {
        Actor_Battler *battler = new Actor_Battler(actor);
        battler->set_map_pos(3, 2*i++ +4);
        battler->set_allegiance(1);
        battler->look(Direction::RIGHT);
        battlersTeam1.push_back(battler);
    }
    i=0;
    for (auto actor : actors2) {
        Actor_Battler *battler = new Actor_Battler(actor);
        battler->set_map_pos(16, 2*i++ +4);
        battler->set_allegiance(2);
        battler->look(Direction::LEFT);
        battlersTeam2.push_back(battler);
    }
}
