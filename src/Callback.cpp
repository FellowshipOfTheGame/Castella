#include <Callback.hpp>

#include <cassert>
#include <stdlib.h>
#include <GameStructure.hpp>
#include <SceneControl.hpp>

Callback::Callback()
{
    //ctor
}

Callback::~Callback()
{
    //dtor
}

/*Button callback methods*/
//Start button
void Callback::game_start(){
    //add condition (is scene a StartMenu?)
    std::cout << "game_start works" << std::endl;
    SceneControl::set_next(Scenes::SCENE_WORLD);
}
//Load button
void Callback::game_load(){
    std::cout << "game_load works" << std::endl;
    SceneControl::set_next(Scenes::SCENE_EDITOR);
}
//Quit button
void Callback::game_quit(){
    std::cout << "game_quit works" << std::endl;
    GameVar::gameState = State::QUIT; //TODO - Use methods in a class to set or get the QUIT state - maybe a GameStateController
}
//Battle
void Callback::start_battle(){
    std::cout << "start_battle works" << std::endl;
    SceneControl::set_next(Scenes::SCENE_BATTLE);
}

void Callback::registerCallbacks( lua_State *L ) {
	assert( L != NULL );
    using namespace luabind;
    module( L ) [
		    def("jogo_iniciar", &Callback::game_start),
		    def("jogo_sair", &Callback::game_quit),
		    def("jogo_carregar", &Callback::game_load),
		    def("batalha_iniciar", &Callback::start_battle)
    ];
}

funcPointer Callback::callback(int i){
    switch(i){
        case 0:
            return game_quit;
        case 1:
            return game_start;
        case 2:
            return game_load;
        case 3:
            return start_battle;
        case 4:
            return NULL;
        case 5:
            return NULL;
        default:
            return NULL;
    }
}

//const std::string Callback::callbackPath("script/callback/");
