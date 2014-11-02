/** @file Callback.hpp
 * header do controller/Callback.cpp
 */

#ifndef CALLBACK_H
#define CALLBACK_H

#include "LuaWBind.hpp"

class Callback
{
    public:
        Callback();
        virtual ~Callback();

        static void registerCallbacks(lua_State *L);

        static void game_start();
        static void game_load();
        static void game_quit();

        static void start_battle();

		template <class T>
        static std::function<T> callback(int i);
	
	//static const std::string callbackPath;

    protected:
    private:
};

#endif // CALLBACK_H
