/** @file Region.hpp */

#ifndef REGION_HPP
#define REGION_HPP

#include "Structure.hpp"

#include <cmath>
#include <vector>

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
 * Essa distância é calculada usando as coordenadas @ref Region::x "x" e @ref Region::y "y", através da fórmula x² + y²
 * @note Como a distância é arbitrária e não se precisa do valor exato, só comparativo, não usamos a raiz quadrada na fórmula da distância,
 * para assim não precisar de mais _headers_, economizando tamanho no objeto e executável
 */
const int NEIGHBOUR_MAX_DISTANCE = 100;


/** @brief Regiões do @ref World "mundo"
 *
 *	Regiões são os pontos (vértices) do mapa global (grafo).
 *
 *	Há vários tipos de regiões, cada qual com suas
 *	@ref Structure "estruturas" internas e funcionalidades
 */
class Region {
private:
	Region_Type type;	///< tipo do reino
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
	Region (Region_Type new_type);
	/** @brief Vê qual o tipo da região em questão
	 *
	 * @return @ref Region_Type "Tipo" da região
	 */
	Region_Type getType ();
	~Region ();
	int Distance (Region *region);
};



class RegionGraph {
private:
	std::vector<Region*> regions;	///< Vetor de todas as regiões do mundo
	std::vector<std::vector<bool> > adjacency_matrix;	///< Matriz de adjacência de

	/** @brief Acha quantos e quais são os vizinhos da região, os guardando em neighbours e neighbourhood
	 *
	 * São possíveis vizinhos a região que estiver a uma distância absoluta máxima de @ref NEIGHBOUR_MAX_DISTANCE
	 */
	void findLastNeighbours ();

protected:

public:
	RegionGraph ();
	void NewRegion (Region_Type new_type);
};


#endif
