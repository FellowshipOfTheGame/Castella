/** @file Player.hpp
 *
 * Header do gamedata/Player.cpp
 */
#ifndef PLAYER_H
#define PLAYER_H

#include "Actor.hpp"
#include "Reign.hpp"
#include <vector>

class Player //Possivelmente diferenciar Human e Computer player por subclasses
{
    public:
        Player(Actor* actor);
		/// @brief Ctor com vários Actors
        Player(vector<Actor *> actors);
        virtual ~Player();
        int get_id();
        std::vector<Actor*> get_actors();
        void add_actor(Actor *actor);
        void remove_actor(Actor *actor);
		/// Registra Player no Lua
		static void registerOnLua (lua_State *L);

		/// Verifica que região está o Player
		Region * getRegion ();
		/// Atualiza a Região corrente do Player
		void setRegion (Region *reg);
		/// Getter do reino
		Reign * getReign ();

		/// Atualiza por ciclo. @sa World::turn_cycle
		void turn_cycle ();

    protected:

    private:
		/// Reino controlado pelo Player
		Reign reign;
		/// Região (posição) atual do Player
		Region *current_pos;

        static int idCount;
        int id;
        std::vector<Actor*> actors;
};

#endif // PLAYER_H
