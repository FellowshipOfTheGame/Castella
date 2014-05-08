#ifndef SCRIPTHANDLER_H
#define SCRIPTHANDLER_H

#include <stdlib.h>
#include <iostream>
#include <memory>
#include <string>
#include <SDL/SDL_image.h>

#include "LuaTable.hpp"

/** TODO:
*   Remover funções que se tornaram desenecessárias.
*/

class ScriptHandler
{
    public:
        ScriptHandler();
        ScriptHandler(std::string script);
        virtual ~ScriptHandler();

        template <typename T> ///<Retrieves a variable from global table, will automatically convert it to type T.
        T get(const char *variableName) { return luabind::object_cast<T>( luabind::globals(L)[variableName] ); }

        template <typename T> ///<Sends a variable or object to the global table, with the name "luaName".
        void send(T element, const char *luaName) { luabind::globals(L)[luaName] = element; }

        template <typename T> ///<Retrieves a variable from a lua table, inside the global table.
        T get(const char *tableName, const char *key) {
            LuaTable table = luabind::gettable(luabind::globals(L), tableName);
            return luabind::object_cast<T>( table[key] );
        }

        LuaTable getTable(const char *tableName); ///<Retrieves table from the global table.

        LuaTable global() const; ///<Returns the global table.

        lua_State *state() const; ///<Returns a pointer to the lua state.

        void variable_toLua(double source, const char* target);
        double variable_fromLua(const char* source);
        void* table_element_fromLua(int i, int j);

        void close();

        void run_lua();

        static int teste();

    protected:
        static lua_State *L;
    private:
};

#endif // SCRIPTHANDLER_H
