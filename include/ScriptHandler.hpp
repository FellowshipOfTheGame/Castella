#ifndef SCRIPTHANDLER_H
#define SCRIPTHANDLER_H

#include <stdlib.h>
#include <iostream>
#include <memory>
#include <lua.hpp>

//extern "C" {
//    static int l_cppfunction(lua_State *L);
//}

using namespace std;

class ScriptHandler
{
    public:
        ScriptHandler();
        ScriptHandler(std::string script);
        virtual ~ScriptHandler();

        void variable_toLua(double source, const char* target);
        double variable_fromLua(const char* source);
        void* table_element_fromLua(int i, int j);
        void close();

        void run_lua();

        static int teste();

    protected:
        lua_State *L;
    private:
};

#endif // SCRIPTHANDLER_H
