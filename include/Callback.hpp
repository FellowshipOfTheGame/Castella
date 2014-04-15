#ifndef CALLBACK_H
#define CALLBACK_H

#include "LuaWBind.hpp"

typedef void (*funcPointer)();

class Callback
{
    public:
        Callback();
        Callback(lua_State *L);
        virtual ~Callback();

        void registerCallbacks(lua_State *L);

        static void game_start();
        static void game_load();
        static void game_quit();

        static void start_battle();

        static funcPointer callback(int i);

    protected:
    private:
};

#endif // CALLBACK_H
