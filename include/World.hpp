/** @file World.hpp
 *
 * Header do gamedata/World.cpp
 */
#ifndef WORLD_H
#define WORLD_H

#include "RegionGraph.hpp"
#include "ScriptHandler.hpp"
#include "Player.hpp"
#include "Actor_Battler.hpp"
#include "Skill.hpp"


/** @brief Mundo do Castella!
 *
 * É o mundo de jogo, que contém todos os objetos, incluindo as regiões, que são organizadas em um grafo.
 * Esse mapa foi escrito usando o padrão _Singleton_ de POO, pois não há sentido em haver mais de um mundo.
 */
class World
{
    public:
        static World* get_world();	///< Método que nos retorna o mundo, o criando se ele ainda não existir

        RegionGraph *getRegionGraph ();	///< Método que retora no grafo das regiões

		Player* get_player(int pos);	///< Retorna Player na posição indicada
		#define get_human() get_player (0)	///< Facilidade pra pegar o player humano (que é sempre o 0)

		/// Adiciona players por uma table do Lua
		void addPlayers (LuaObject player_table);

		/// Registra o mapa do mundo no Lua
		static void registerOnLua (lua_State *L);

		/** @brief Atualiza tudo o que precisar, quando passa um ciclo
		 *
		 * @note Ciclo ocorre quando Player anda, espera ou sai duma batalha
		 */
		void turn_cycle ();

		/// Dtor: destrói todos os Players associados
		~World ();

    protected:

    private:
        World();	///< Construtor do World, private pois só constrói um mundo se ele ainda não existir

		void criaGrafo ();	///< Pede pro lua construir o grafo

		void getActorFunctions ();	///< Pega as funções do actor a partir do Lua

        static World* world;	///< Ponteiro eterno para o único mundo: NULL, se ainda não existir

		RegionGraph regionMap;	///< Grafo contendo todas as regiões do mundo

		vector<Player *> players;

		void create_players();

		void load_skills();
};

#endif // WORLD_H
