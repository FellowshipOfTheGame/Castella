/** @file RegionGraph.hpp
 * 
 * @brief Grafo das regiões do mundão
 */

#ifndef REGION_GRAPH_HPP
#define REGION_GRAPH_HPP

#include <Region.hpp>

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

	std::vector<Region*> regions;	///< Vetor de todas as regiões do mundo
	
	/** @brief Acha quantos e quais são os vizinhos da região, os guardando em neighbours e neighbourhood
	 *
	 * São possíveis vizinhos a região que estiver a uma distância absoluta máxima de @ref NEIGHBOUR_MAX_DISTANCE
	 * 
	 * @param R Região a ser checada
	 */
	void checkNeighbourhood (Region *R);
	/** @brief Verifica se duas Regiões se ligam
	 * 
	 * @param[in] A Região A
	 * @param[in] B Região B
	 */
	bool liga (Region *A, Region *B);
	
protected:

public:
	RegionGraph ();		///< Ctor: constrói vértices baseado no tamanho do mapa
	~RegionGraph ();
	int newRegion (int ID, Region_Type new_type, int x, int y);
	void printGraphInfo ();		///< Imprime o grafo na stdout, listando as adjacências
	void printGraph ();		///< Imprime o grafo na stdout, com pontos!
	
	Region *& operator[] (unsigned int i);	///< Acesso ao Vector de regiões; @throws std::out_of_range
	
	// Consts do tilemap
	static const int map_height = 4;	///< Altura do mapa, em blocos
	static const int map_width = 4;	///< Largura do mapa, em bloco
	static const int block_size = 3;	///< Tamanho do lado do bloco, em tiles
};

#endif
