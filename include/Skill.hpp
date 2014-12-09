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
		/// Pega todas as skills desde uma table do lua, com tables pra cada Skill
		static void add_skill_table (std::string skillScript, std::string tableName);
        int get_cost(Actor_Battler *battler);
        int get_damage(Actor_Battler *battler);

		/** @brief Destrói todos os skills alocados
		 *
		 * Essa função destrói as skills dentro do @ref Skill::skills,
		 * liberando a memória alocada.
		 *
		 * @warning Lembre-se que, ao chamá-la, as skills não mais existirão,
		 * então chamar qualquer uma delas gera um __segfault__.
		 */
		static void destroy_all_skills ();

    protected:
    private:
		/// ctor padrão, pro add_skill_table
		Skill ();
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
