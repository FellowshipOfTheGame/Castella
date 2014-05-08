#include <Callback.hpp>

#include <stdlib.h>
#include <GameStructure.hpp>
#include <SceneControl.hpp>

Callback::Callback()
{
    //ctor
}

Callback::Callback(lua_State *L) {
    registerCallbacks(L);
}

Callback::~Callback()
{
    //dtor
}

/*Button callback methods*/
//Start button
void Callback::game_start(){
    //add condition (is scene a StartMenu?)
    std::cout << "Funcionando" << std::endl;
    SceneControl::set_next(SceneControl::SCENE_WORLD);
}
//Load button
void Callback::game_load(){
    SceneControl::set_next(SceneControl::SCENE_EDITOR);
}
//Quit button
void Callback::game_quit(){
    GameVar::gameState = State::QUIT; //TODO - Use methods in a class to set or get the QUIT state - maybe a GameStateController
}
//Battle
void Callback::start_battle(){
    SceneControl::set_next(SceneControl::SCENE_BATTLE);
}

void Callback::registerCallbacks( lua_State *L ) {
    using namespace luabind;
    module( L ) [
        def( "game_quit", &Callback::game_quit ),
        def( "game_start", &Callback::game_start ),
        def( "game_load", &Callback::game_load ),
        def( "start_battle", &Callback::start_battle )
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
