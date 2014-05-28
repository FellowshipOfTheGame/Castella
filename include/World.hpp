#ifndef WORLD_H
#define WORLD_H


#include <Region.hpp>

/** @brief Mundo do Castella!
 * 
 * É o mapa global, que contém todas as regiões do jogo, que são organizadas em um grafo.
 * Esse mapa foi escrito usando o padrão _Singleton_ de POO, pois não há sentido em haver mais de um mundo.
 * 
 * @todo quem fez o mundo, põe mais coisaí, deve ter =P
 */
class World
{
    public:
        virtual ~World();

        static World* get_world();	///< Método que nos retorna o mundo, o criando se ele ainda não existir
    protected:
    private:
        World();	///< Construtor do World, private pois só constrói um mundo se ele ainda não existir

        static World* world;	///< Ponteiro eterno para o único mundo: NULL, se ainda não existir
        
		RegionGraph regionMap;	///< Grafo contendo todas as regiões do mundo
};

#endif // WORLD_H
