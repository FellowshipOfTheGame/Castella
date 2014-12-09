#include <Scene_Battle.hpp>
#include <cstdlib>

Scene_Battle::Scene_Battle() : battleMap (20, 12)
{
    SceneControl::set_cur (Scenes::SCENE_BATTLE); //TODO Move this code to a SceneControl or somewhere alike

    cursor = FileHandler::load_img("battle_cursor.png");

	//Player **players = (Player **) Scene::ptr;

    //Código provisório nesta classe para inicializar os players - deve ser passado no construtor (de preferência) ou pelo ponteiro void da scene
    Player* players[2];
	players[0] = World::get_world()->get_player(0);
	players[1] = World::get_world()->get_player(1);

    std::cout << "loading battlers... ";
	load_battlers (players[0], players[1]);
	active_battler = NULL;
}

Scene_Battle::~Scene_Battle()
{
	for (auto act : battlersTeam1) {
		delete (act);
	}
	for (auto act : battlersTeam2) {
		delete (act);
	}
}

void Scene_Battle::update(){
    Scene::update();
    //Se não houver um battler ativo, atualiza a estamina
    if (active_battler == NULL){
        update_stamina();
    }
    else { //há um battler ativo
        //Recebe input para o battler
        //Quando finalizar suas ações, passa o active_battler para NULL
    }
}

void Scene_Battle::update_stamina(){
    //Concatena os times de battlers
    std::vector<Actor_Battler*> battlers = battlersTeam1;
    battlers.insert(battlers.end(), battlersTeam2.begin(), battlersTeam2.end());
    //Verifica os battlers que chegaram a 100% da estamina e os marca como prontos
    std::vector<Actor_Battler*> ready_battlers;
    for (auto btlr : battlers){
        if (btlr->get_stamina_percent() >= 100){
            ready_battlers.push_back(btlr);
        }
    }
    //Se não houver mais battlers prontos, volta a fazer update da estamina
    if (ready_battlers.empty ()) {
        for (auto btlr : battlers){
            btlr->update();
        }
    }
    else {
        //Sorteia um entre os ready_battlers para selecionar como battler_active
        active_battler = ready_battlers[rand()%ready_battlers.size()];
    }
}

void Scene_Battle::draw(SDL_Surface *screen){
    //Super
    Scene::draw(screen);
    battleMap.draw(screen, battlersTeam1, battlersTeam2);
    //Desenha o cursor
    if (active_battler != NULL){
        int x = active_battler->get_map_pos().x;
        int y = active_battler->get_map_pos().y;
        apply_surface( (x+0.5)*Screen::TILE_SIZE, y*Screen::TILE_SIZE-40, cursor, screen, NULL, 0.5);
    }
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
    //Se um battler estiver ativo - (e não for controlado por IA)
    if (active_battler != NULL){
        switch(input){
            //Mover
            case SDLK_DOWN:
                active_battler->walk(Direction::DOWN);
                break;
            case SDLK_RIGHT:
                active_battler->walk(Direction::RIGHT);
                break;
            case SDLK_LEFT:
                active_battler->walk(Direction::LEFT);
                break;
            case SDLK_UP:
                active_battler->walk(Direction::UP);
                break;
            //Encerrar turno
            case SDLK_END:
                if ( (int)(active_battler->get_stamina_percent()) == 100 ){
                    active_battler->use_stamina(10); //gasta 10 de estamina
                }
                active_battler = NULL;
        }
    }
    //Other input:
    switch(input){
        default:
            break;
    }
}

void Scene_Battle::load_battlers(Player* player1, Player* player2){

    std::cout << "loading battlers" << std::endl;

    std::vector <Actor*> actors1 = player1->get_actors();
    std::vector <Actor*> actors2 = player2->get_actors();

    //Verifica se os players têm pelo menos 1 actor
    if (actors1.size() < 1 || actors2.size() < 1){
        SceneControl::exitScene(); //ERRO: aborta a batalha
    }

    //Insere os battlers dos actors no grupo de battlers dos seus times
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
