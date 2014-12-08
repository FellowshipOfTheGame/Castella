#ifndef ACTOR_BATTLER_H
#define ACTOR_BATTLER_H

#include <FileHandler.hpp>
#include "Actor.hpp"


enum class Direction {
    DOWN    = 0,
    LEFT    = 1,
    RIGHT   = 2,
    UP      = 3
};

class Actor_Battler : public Actor
{
    private:
        int allegiance; //id do Player ao qual ele é leal
        int hp;
        float stamina;
        int AI; //fazer enum (ou usar string do script, puxada do actor): none, preset1, preset2, ..., custom - usar scripts (por enquanto IA=false é player)
        Direction direction;
        SDL_Rect spriteclip[12];
        SDL_Rect map_pos; //battler position on the battle map
        //int frame;
        int walking;

    public:
        Actor_Battler(Actor* actor);
        virtual ~Actor_Battler();

        void set_allegiance(int allegiance);

        int get_allegiance();

        bool use_skill(int skill_id);

        bool is_passable();

        void draw(int x, int y, int index, SDL_Surface *screen);

        void set_map_pos(int x, int y);

        void look(Direction direction);

        void walk(Direction direction);

        void set_ai(int ai);

        bool is_player_controlled();

        SDL_Rect get_map_pos();

        void update();

        float get_stamina_percent();

        bool use_stamina(int cost);

		/** @brief Pega funções de controle de batalha do Lua
		 *
		 * Porque xupa hardcoding!
		 */
		static void getFunctionsFromLua (const string script_name);
		/// Registra classe no Lua
		static void registerOnLua (lua_State *L);

    protected:
        bool passable;
        SDL_Rect clip(int index);

		static ScriptHandler sH;
};

#endif // ACTOR_BATTLER_H
