/** @file Region.hpp
 * 
 * @brief Regiões do mundão
 */

#ifndef REGION_HPP
#define REGION_HPP

#include <Structure.hpp>

#include <cmath>
#include <cstdlib>
#include <vector>
#include <iostream>


/** Enum do tipo da região */
enum Region_Type {
	/** @brief __Castelo__, lar dos Lordes
	 *
	 * Castelos são lugares onde há reis/lordes. Têm as estruturas de uma @ref Village "vila" e mais a sala do trono.
	 */
	castle,
	/** @brief __Vilas__, lugar do povo
	 *
	 * Vilas são @ref Castle "castelos" sem um rei/lorde e, em geral, mais simples (com menos @ref Structure "estruturas").
	 */
	village,
	/** @brief __Florestas__, lugar de recursos naturais
	 *
	 * Florestas são boas por conter recursos como madeira (tem mais coisa?).
	 * Acontece também de encontrar nativos a protegê-las, então cuidado!
	 */
	forest,
	/** @brief __Cavernas__, lugar de recursos outros recursos naturais
	 *
	 * Cavernas contêm mateis, como ouro e aço.
	 * Cuidado com os _Zubats_! xP
	 */
	cave
};


/** Constante: distância absoluta máxima entre regiões consideradas vizinhas.
 * 
 * Essa distância é calculada usando as coordenadas @ref Region::x "x" e @ref Region::y "y", através da fórmula x² + y²
 * @note Como a distância é arbitrária e não se precisa do valor exato, só comparativo, não usamos a raiz quadrada na fórmula da distância,
 * para assim não precisar de mais _headers_, economizando tamanho no objeto e executável
 */
const int NEIGHBOUR_MAX_DISTANCE = 70;


/** @brief Regiões do @ref World "mundo"
 *
 *	Regiões são os pontos (vértices) do mapa global (grafo).
 *
 *	Há vários tipos de regiões, cada qual com suas
 *	@ref Structure "estruturas" internas e funcionalidades
 * 
 * @todo Dtor
 */
class Region {
	friend class RegionGraph;
private:
	Region_Type type;	///< tipo do reino
	int ID;	///< ID da região
	char *name;	///< nome da região
	int x,	///< coordenada _x_ do reino no mapa global
		y;	///< coordenada _y_ do reino no mapa global
	std::vector<Region*> neighbourhood;	///< vetor de regiões vizinhas
	std::vector<Structure*> inner_structures;	///< estruturas encontradas na região: depende do @ref Region_Type "tipo"
	//Actor *owner;	///< personagem (ainda não sei o nome da classe) dono da região; se NULL, não há dono
	
	/** @brief Diplomacia é o recurso que simboliza a relação entre o jogador e o lorde/prefeito/dono da região.
	 * 
	 * A diplomacia pode estar boa (positiva), ruim (negativa), ou neutra (zero).
	 */
	int diplomacy;

protected:

public:
	Region (int ID, Region_Type new_type, int x, int y);
	/** @brief Vê qual o tipo da região em questão
	 *
	 * @return @ref Region_Type "Tipo" da região
	 */
	Region_Type getType ();
	~Region ();
	int getDistance (Region *region);	///< Calcula a distância entre duas regiões
	void print ();	///< Imprime região na stdout, com ID, posição e lista de adjacência
	int getAdjQuantity ();
};




/** @brief Grafo das @ref Region "regiões" propriamente dito.
 * 
 * Grafo organizado em um Vector de regiões,
 * implementado usando listas de adjacência.
 * 
 * @todo ligar os vértices ao criar
 * @todo Dtor
 * @todo DFS
 */
class RegionGraph {
private:
	// Consts do tilemap
	static const int map_height = 10;	///< Altura do mapa, em blocos
	static const int map_width = 10;	///< Largura do mapa, em bloco
	static const int block_size = 4;	///< Tamanho do lado do bloco, em tiles
	
	// Taxa de aparecimento de cada região no mapa (em porcentagem)
	static const int castle_ratio = 20;
	static const int forest_ratio = 20;
	static const int cave_ratio = 20;
	static const int village_ratio = 20;

	std::vector<Region*> regions;	///< Vetor de todas as regiões do mundo
	
	/** @brief Acha quantos e quais são os vizinhos da região, os guardando em neighbours e neighbourhood
	 *
	 * São possíveis vizinhos a região que estiver a uma distância absoluta máxima de @ref NEIGHBOUR_MAX_DISTANCE
	 * 
	 * @param R Região a ser checada
	 */
	void checkNeighbourhood (Region *R);
	
protected:

public:
	RegionGraph ();		///< Ctor: constrói vértices baseado no tamanho do mapa
	~RegionGraph ();
	int newRegion (int ID, Region_Type new_type, int x, int y);
	void printGraphInfo ();		///< Imprime o grafo na stdout, listando as adjacências
	void printGraph ();		///< Imprime o grafo na stdout, com pontos!
};


#endif
