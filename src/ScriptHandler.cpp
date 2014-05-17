#include <cassert>
#include <ScriptHandler.hpp>
#include <string>
#include <memory>

#define checkState() ( assert( L != NULL ) )

ScriptHandler::ScriptHandler(){
    //Set the main lua state
    L = luaL_newstate();
	openLibs();
}

ScriptHandler::ScriptHandler(std::string script){
    //cout << "-ctor ScriptHandler(string)" << endl;
    L = luaL_newstate();
	openLibs();
    //Load the script file and check for error
    load (script);
}

ScriptHandler::~ScriptHandler(){
    //std::cout << "dtor ScriptHandler" << std::endl;
    close();
    //std::cout << "dtor ScriptHandler: lua closed" << std::endl;
} //dtor

LuaTable ScriptHandler::getTable(const char *tableName) const { 
	checkState();
	return LuaTable( luabind::gettable( luabind::globals(L), tableName ) ); 
}

lua_State *ScriptHandler::state() const { 
	checkState();
	return L; 
}

LuaTable ScriptHandler::global() const { 
	checkState();
	return LuaTable( luabind::globals(L) ); 
}

void ScriptHandler::openLibs(){
	checkState();
    //Open lua standard libraries
    luaL_openlibs(L);
    //Open luabind libraries
    luabind::open(L);
}

void ScriptHandler::load(std::string script){
    //If the .lua extension hasn't been passed, concat it into the script string
    if (script.find (".lua") == std::string::npos) {
        script += ".lua";
    }
	checkState();
    if (luaL_loadfile ( L, script.c_str() ) ) {
        //When an error occurs it is sent to the top of the lua API stack.
        std::cerr << "Error running script: " << lua_tostring(L, -1) << std::endl;
    }

    std::cout << "Loaded: " << script << std::endl;
}

void ScriptHandler::run_lua(){
    //Execute lua chunk and checks for error
	checkState();
    if(lua_pcall(L, 0, LUA_MULTRET, 0)){
        //Error
        std::cerr << "Error trying to run lua" << lua_tostring(L, -1) << std::endl;
    }
}

void ScriptHandler::close(){ 
	if ( L != NULL ){
		lua_close(L);
		L = NULL;
	}
}

#undef checkState()
