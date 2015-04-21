#include "Scene_Battle.hpp"
#include "cstdlib"

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
	displayHUD = true;

	battleMap.set_battlers (battlersTeam1, battlersTeam2);
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
    frame++;
    //Se não houver um battler ativo, atualiza a estamina
    if (active_battler == NULL){
        update_stamina();
		battleMap.set_need_redraw ();
    }
    else { //há um battler ativo
		need_redraw = true;
        //Recebe input para o battler
        //Quando finalizar suas ações, passa o active_battler para NULL
    }
}

void Scene_Battle::update_stamina(){
    //Concatena os times de battlers
    std::vector<Actor_Battler*> battlers = get_battlers();
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

void Scene_Battle::draw (SDL_Surface *screen) {
	// desenha mapa primeiro, depois o resto =]
	battleMap.draw (screen);
	Drawable::draw (screen);
}

void Scene_Battle::redraw(){
    //Desenha o cursor
    if (active_battler != NULL){
        if (!active_battler->is_acting()){
            int x = (active_battler->get_map_pos().x + 0.5) * Screen::TILE_SIZE;
            int y = active_battler->get_map_pos().y * Screen::TILE_SIZE - 40 - frame%16/4;
            apply_surface(x, y, cursor, image, NULL, 0.5);
        }
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
    //Verifica se a tecla shift está pressionada e ajusta a flag
    bool shift = false;
    if (is_key_pressed(SDLK_LSHIFT) || Input::is_key_pressed(SDLK_RSHIFT)){
        shift = true;
    }
    //Se um battler estiver ativo - (e não for controlado por IA)
    if (active_battler != NULL){
        //Mover
        if ( is_key_pressed(SDLK_RIGHT) || is_key_pressed(SDLK_LEFT) || is_key_pressed(SDLK_UP) || is_key_pressed(SDLK_DOWN) ){
            //Verifica a direção
            Direction dir;
            if (is_key_pressed(SDLK_RIGHT)){        //Seta direita
                dir = Direction::RIGHT;
            }
            else if (is_key_pressed(SDLK_LEFT)){    //Seta esquerda
                dir = Direction::LEFT;
            }
            else if (is_key_pressed(SDLK_UP)){      //Seta pra cima
                dir = Direction::UP;
            }
            else{                                   //Seta pra baixo
                dir = Direction::DOWN;
            }
            //Verifica o shift
            if (shift){
                active_battler->look(dir);
            }
            else{
                active_battler->walk(dir);
            }
        }
        else {
            switch(input){
                //Encerrar turno
                case SDLK_END:
                    if ( (int)(active_battler->get_stamina_percent()) == 100 ){
                        active_battler->use_stamina(10); //gasta 10 de estamina
                    }
                    active_battler = NULL;
                    break;
                //Skill
                case SDLK_SPACE:
                    std::cout << "Attack!" << std::endl;
                    if (active_battler->use_skill(0) ){
                        int dmg = active_battler->get_skill_damage_buffer();
                        std::cout << "dmg:" << dmg << std::endl;
                        SDL_Rect tgt = active_battler->get_skill_target_buffer();
                        cause_damage(dmg, tgt);
                    }
                    break;
            }
        }
		battleMap.set_need_redraw ();
    }

    //Inputs gerais da batalha - não dependem de haver battler ativo
    switch (input){
        case SDLK_h: // alterna display da HUD
            displayHUD = !displayHUD;
			battleMap.set_displayHUD (displayHUD);
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

std::vector<Actor_Battler*> Scene_Battle::get_battlers(){
    //Concatena os times de battlers
    std::vector<Actor_Battler*> battlers = battlersTeam1;
    battlers.insert(battlers.end(), battlersTeam2.begin(), battlersTeam2.end());
    return battlers;
}

bool Scene_Battle::cause_damage(int damage, SDL_Rect target){
    Actor_Battler *battler = battleMap.get_battler_at(target, get_battlers());
    if (battler != nullptr){
        battler->take_damage(damage);
        return true;
    }
    else return false;
}

int Scene_Battle::frame = 0;
