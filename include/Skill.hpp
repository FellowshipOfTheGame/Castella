#ifndef SKILL_H
#define SKILL_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include <iostream>
#include <string>

#include "ScriptHandler.hpp"

#include "Actor_Battler.hpp"

class Skill
{
    public:
        virtual ~Skill();
        static void add_skill(std::string skillScript, std::string skillName);
        int get_cost(Actor_Battler *battler);
        int get_damage(Actor_Battler *battler);

    protected:
    private:
        //ctor recebe o nome do script das skills e o nome da skill
        Skill(std::string skillScript, std::string skillName);
        static std::vector<Skill*> skills;
        static std::string scriptPath;
        bool weapon_based; //indica se o dano resultante é baseado no dano da arma
        float base_cost; //custo base da habilidade, em porcentagem (a multiplicar o
        float relative_cost; //custo percentual que se multiplicará pela carga da arma
        float damage; // dano base (absoluto ou percentual - dependendo da weapon_based)
        std::string name; //nome da habilidade
        int range; //circular range
        int area; //circular area radius

        void build_skill(LuaTable &skill);
};

#endif // SKILL_H
