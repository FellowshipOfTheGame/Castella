#ifndef ACTOR_H
#define ACTOR_H

#include "FileHandler.hpp"
#include "ScriptHandler.hpp"
#include <Item_Weapon.hpp>

class Actor
{
    public:
        Actor(std::string spritesheetName, int str=5, int intel=5, int agi=5, int vit=5);
        virtual ~Actor();
        int get_id();
        //Constants:
        static const int BASE_PRECISION;
        static const int BASE_HP;
        static const int BASE_STAMINA;
        static const float BASE_STAMINA_REGEN;
        //Methods:
        int get_max_hp();
        int get_max_stamina();
        int get_precision();
        int get_evasion();
        float get_stamina_recovery();
        float get_phys_dmg_amplifier();
        float get_magic_dmg_amplifier();
        float get_phys_dmg_attenuation();
        float get_magic_dmg_attenuation();

        float get_weapon_damage();
		//         Métodos de cálculos variados puxados do Lua       //
        static LuaFunction *Lua_get_max_hp;
        static LuaFunction *Lua_get_max_stamina;
        static LuaFunction *Lua_get_precision;
        static LuaFunction *Lua_get_evasion;
        static LuaFunction *Lua_get_stamina_recovery;
        static LuaFunction *Lua_get_phys_dmg_amplifier;
        static LuaFunction *Lua_get_magic_dmg_amplifier;
        static LuaFunction *Lua_get_phys_dmg_attenuation;
        static LuaFunction *Lua_get_magic_dmg_attenuation;
		/// Registra Actor no Lua
		static void registerOnLua (lua_State *L);

    protected:
        Actor(); //protected default ctor: only the subclass should use it
        int id;
        //Atributos primários:
        int strength;
        int inteligence;
        int agility;
        int vitality;
        //Equipamentos - devem receber o ponteiro de um item do player
        Weapon *mainHand;
        //...
        SDL_Surface* spritesheet;
        //Habilidades
        std::vector<int> skills; // armazena a ID das skills do actor

    private:
        static int idCount;

};
#endif // ACTOR_H
