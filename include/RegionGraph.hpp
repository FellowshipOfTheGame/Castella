/** @file RegionGraph.hpp
 * @brief Grafo das regiões do mundão.
 *
 * Header do gamedata/RegionGraph.cpp
 */

#ifndef REGION_GRAPH_HPP
#define REGION_GRAPH_HPP

#include <stdexcept>

#include "Region.hpp"


// Só nome, pro RegionGraph saber que existe
class RegionGraphIterator;



/** @brief Grafo das @ref Region "regiões" propriamente dito.
 * 
 * Grafo organizado em um Vector de regiões,
 * implementado usando listas de adjacência.
 */
class RegionGraph {
private:
	// Taxa de aparecimento de cada região no mapa (em porcentagem)
	static const int castle_ratio = 20;
	static const int forest_ratio = 20;
	static const int cave_ratio = 20;
	static const int village_ratio = 20;

	std::vector<Region *> regions;	///< Vetor de todas as regiões do mundo
	
	/** @brief Verifica se duas Regiões se ligam e as ligam
	 * 
	 * @param[in] A Região A
	 * @param[in] B Região B
	 */
	bool liga (Region *A, Region *B);
	
	
protected:

public:
	~RegionGraph ();
	/** @brief Cria uma região e a adiciona ao vector
	 *
	 * @return Região recentemente criada
	 */
	Region * newRegion (int ID, Region_Type new_type, int x, int y);
	void printGraphInfo ();		///< Imprime o grafo na stdout, listando as adjacências
	void printGraph ();		///< Imprime o grafo na stdout, com pontos!

	unsigned int size ();	///< Tamanho do grafo (número de nós)

	/** @brief Acha quantos e quais são os vizinhos da região, os guardando em neighbours e neighbourhood
	 *
	 * São possíveis vizinhos a região que estiver a uma distância absoluta máxima de @ref NEIGHBOUR_MAX_DISTANCE
	 * 
	 * @param R Região a ser checada
	 */
	void checkNeighbourhood (Region *R);

	Region *& operator[] (unsigned int i);	///< Acesso ao Vector de regiões; @throws std::out_of_range
	
	/* Iterador */
	RegionGraphIterator begin () const;
	RegionGraphIterator end () const;
	
	// Consts do tilemap
	static const int graph_height = 4;	///< Altura do mapa, em blocos
	static const int graph_width = 6;	///< Largura do mapa, em bloco
	static const int block_size = 3;	///< Tamanho do lado do bloco, em tiles
};


/** @brief Um iterador para o RegionGraph
 * 
 * É útil para iterarmos por todos as Regiões do grafo
 * usando a notação nova do C++11 (for ranged loops)
 */
class RegionGraphIterator {
private:
	const RegionGraph *graph;
	int pos;

protected:

public:
	RegionGraphIterator (const RegionGraph *graph, int pos);	///< Ctor
	/* Operadores, pra rolar a iteração */
	bool operator!= (const RegionGraphIterator& other) const;
	const RegionGraphIterator& operator++ ();
	Region *& operator* () const;
};

#endif
