#include "ScriptHandler.hpp"
#include <string.h>
#include <memory>

ScriptHandler::ScriptHandler(){
    //cout << "-ctor ScriptHandler(string)" << endl;
    //Set a lua state
    L = luaL_newstate();
    //Open lua standard libraries
    luaL_openlibs(L);
    //Open luabind libraries
    luabind::open(L);
}

ScriptHandler::ScriptHandler(std::string script)
{
    //cout << "-ctor ScriptHandler(string)" << endl;
    //If the .lua extension hasn't been passed, concat it into the script string
    if(script.find(".lua") == std::string::npos){
        script += ".lua";
    }
    //Set a lua state
    L = luaL_newstate();
    //Open lua standard libraries
    luaL_openlibs(L);
    //Load the script file and check for error
    if(luaL_loadfile(L, script.c_str())){
        //failed
        std::cerr << lua_tostring(L, -1) << std::endl;
        lua_pop(L, 1);
    }
}

ScriptHandler::~ScriptHandler(){
    //cout << "dtor ScriptHandler" << endl;
    lua_close(L);
    //cout << "dtor ScriptHandler: lua closed" << endl;
} //dtor

LuaTable ScriptHandler::getTable(const char *tableName) { return LuaTable( luabind::gettable( luabind::globals(L), tableName ) ); }

lua_State *ScriptHandler::state() const { return L; }

LuaTable ScriptHandler::global() const { return LuaTable( luabind::globals(L) ); }

void ScriptHandler::close(){ lua_close(L); }

void ScriptHandler::variable_toLua(double source, const char* target) {
    //TODO try to check types here (instead of a double source only), to make a more generic method
    lua_pushnumber(L, source);
    lua_setglobal(L, target);
}

double ScriptHandler::variable_fromLua(const char* source){
    double target;
    lua_getglobal(L, source);
    target = lua_tonumber(L, -1);
    lua_pop(L, 1);
    return target;
}

void* ScriptHandler::table_element_fromLua(int i, int j){
    void* element;
    //Adjust to lua index (starts at 1)
    i++;
    j++;
    //Push function and arguments
    lua_getglobal(L, "get_table_field"); //function to be called
    lua_pushnumber(L, i); //push first arg
    lua_pushnumber(L, j); //push second arg
    //Call (2 arguments, 1 result) and check for error
    if(lua_pcall(L, 2, 1, 0)){ //
        std::cerr << lua_tostring(L, -1) << std::endl;
    }
    //Retrieve result (int or string)
    if(lua_isnumber(L, -1)){
        element = (void*)((int)lua_tonumber(L, -1));
    }
    else{ //lua_isstring(L, -1)
        element = (void*)lua_tostring(L, -1);
    }
    lua_pop(L, 1); //pops returned value
    return element;
}

void ScriptHandler::run_lua(){
    //Execute lua chunk and checks for error
    if(lua_pcall(L, 0, LUA_MULTRET, 0)){
        //Error
        std::cerr << lua_tostring(L, -1) << std::endl;
    }
}

int ScriptHandler::teste(){
    std::cout << "OI" << std::endl;

    // Create new lua state
    lua_State *L = luaL_newstate();
    luaL_openlibs(L);
    if(luaL_loadfile(L, "script/script1.lua")){ //could not load
        std::cerr << "Falha ao carregar script" << std::endl;
        std::cerr << lua_tostring(L, -1) << std::endl;
        lua_pop(L, 1);
    }

    lua_pushnumber(L, 1.1);
    lua_setglobal(L, "cppvar");
    if(lua_pcall(L, 0, LUA_MULTRET, 0)){ //fail
        std::cerr << lua_tostring(L, -1) << std::endl;
        lua_pop(L, 1);
    }

    lua_getglobal(L, "luavar");
    double luavar = lua_tonumber(L, -1);
    lua_pop(L, 1);
    std::cout << "C++ can read the value set from Lua luavar = " << luavar << std::endl;

    return 0;
}

//extern "C" {
//        static int l_cppfunction(lua_State *L){
//        double arg = luaL_checknumber(L, 1);
//        lua_pushnumber(L, arg *0.5);
//        return 1;
//    }
//}
