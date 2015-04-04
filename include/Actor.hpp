#ifndef ACTOR_H
#define ACTOR_H

#include "FileHandler.hpp"
#include "ScriptHandler.hpp"
#include "Item_Weapon.hpp"
#include "Animated_Sprite.hpp"

class Actor
{
	friend ostream& operator<< (ostream & os, const Actor & actor);
    public:
        Actor(std::string spritesheetName, int str=5, int intel=5, int agi=5, int vit=5);
        virtual ~Actor();
        int get_id();
        //Constants:
        static const int BASE_PRECISION; // precisão base de acerto, em porcentagem
        static const int BASE_HP;
        static const int BASE_STAMINA;
        static const float BASE_STAMINA_REGEN; // regeneração base de estamina por frame
        //Image constants
        static const int SPRITECLIPS_HOR;  // horizontal spritesheet clips
        static const int SPRITECLIPS_VER;  // vertical spritesheet clips
        static const int SPRITECLIPS_NEUTRAL_HOR_INDEX;    //índice horizontal da posição neutra na spritesheet
        static const int SPRITECLIPS_INITIAL_INDEX;    //clip inicial da spritesheet
        static const std::string IMG_FOLDER;    // pasta das imagens de actors em "images/"
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

		/** @brief Chama alguma função de status do Actor
		 *
		 * Só uma definiçãozinha pra facilitar nossa vida
		 */
		#define CALL_ACTOR_FUNC(func) (luabind::call_function<double> (sH.state (), #func, this))
		/// Registra Actor no Lua
		static void registerOnLua (lua_State *L);

		static ScriptHandler sH;

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
        Animated_Sprite *aSprite;
        //Habilidades
        std::vector<int> skills; // armazena a ID das skills do actor

    private:
        static int idCount;

};
#endif // ACTOR_H
