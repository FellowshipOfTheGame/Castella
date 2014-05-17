#include <Callback.hpp>

#include <cassert>
#include <stdlib.h>
#include <GameStructure.hpp>
#include <SceneControl.hpp>

Callback::Callback()
{
    //ctor
}

Callback::Callback(lua_State *L) {
	assert( L != NULL );
    Callback::registerCallbacks(L);
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
    SceneControl::set_next(SceneControl::SCENE_WORLD);
}
//Load button
void Callback::game_load(){
    std::cout << "game_load works" << std::endl;
    SceneControl::set_next(SceneControl::SCENE_EDITOR);
}
//Quit button
void Callback::game_quit(){
    std::cout << "game_quit works" << std::endl;
    GameVar::gameState = State::QUIT; //TODO - Use methods in a class to set or get the QUIT state - maybe a GameStateController
}
//Battle
void Callback::start_battle(){
    std::cout << "start_battle works" << std::endl;
    SceneControl::set_next(SceneControl::SCENE_BATTLE);
}

void Callback::registerCallbacks( lua_State *L ) {
	assert( L != NULL );
    using namespace luabind;
    module( L ) [
	    /*class_<Callback>("Callback")
		.scope[*/
		    def("game_start", &Callback::game_start),
		    def("game_quit", &Callback::game_quit),
		    def("game_load", &Callback::game_load),
		    def("start_battle", &Callback::start_battle)
		//] 
    ];/*
	class_<State>("State")
	    .enum_("GameStates")[
		value("NULL_STATE", State::NULL_STATE),
		value("MAIN", State::MAIN),
		value("WORLD", State::WORLD),
		value("DIPLOMACY", State::DIPLOMACY),
		value("QUIT", State::QUIT)
	    ],
        class_<SceneControl>("SceneControl")
	    .scope[
		def("set_next", &SceneControl::set_next)
            ]
	    .enum_("Scenes")[
		value("SCENE_NULL", SceneControl::SCENE_NULL),
		value("SCENE_START_MENU", SceneControl::SCENE_START_MENU),
                value("SCENE_WORLD", SceneControl::SCENE_WORLD),
                value("SCENE_REGION", SceneControl::SCENE_REGION),
                value("SCENE_BATTLE", SceneControl::SCENE_BATTLE),
                value("SCENE_EDITOR", SceneControl::SCENE_EDITOR),
                value("END", SceneControl::END)
	    ],
	class_<GameVar>("GameVar")
	    .def("set_State", (int(GameVar::*) (const int)) &GameVar::set_State)
    ];
    std::string file(Callback::callbackPath + "regCallback.lua");
    if( luaL_dofile( L, file.c_str() ) ) std::cout << "Error registering callbacks" << std::endl;*/
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