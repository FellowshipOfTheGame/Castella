/** @file Region.hpp
 * 
 * @brief Regiões do mundão
 *
 * Header do gamedata/Region.cpp
 */

#ifndef REGION_HPP
#define REGION_HPP

#include "Structure.hpp"

#include <cstdlib>
#include <vector>
#include <set>
#include <iostream>

using namespace std;


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


/** @brief Regiões do @ref World "mundo"
 *
 *	Regiões são os pontos (vértices) do mapa global (grafo).
 *
 *	Há vários tipos de regiões, cada qual com suas
 *	@ref Structure "estruturas" internas e funcionalidades
 */
class Region {
	friend class RegionGraph;

private:
	int ID;	///< ID da região
	Region_Type type;	///< tipo do reino
	string name;	///< nome da região
	int x,	///< coordenada _x_ do reino no mapa global
		y;	///< coordenada _y_ do reino no mapa global
	set<Region *> neighbourhood;	///< vetor de regiões vizinhas; É um set para não haver repetições
	vector<Structure *> inner_structures;	///< estruturas encontradas na região: depende do @ref Region_Type "tipo"
	
	/** @brief Diplomacia é o recurso que simboliza a relação entre o jogador e o lorde/prefeito/dono da região.
	 * 
	 * A diplomacia pode estar boa (positiva), ruim (negativa), ou neutra (zero).
	 */
	int diplomacy {0};

protected:

public:
	Region (int ID, Region_Type new_type, int x, int y);
	~Region ();
	void print ();	///< Imprime região na stdout, com ID, posição e lista de adjacência
	
	/* GETTERS */
	/** @brief Vê qual o tipo da região em questão
	 *
	 * @return @ref Region_Type "Tipo" da região
	 */
	Region_Type getType ();
	int getId ();
	int getX ();
	int getY ();
	vector<Structure *> getStructures ();
	Structure * getStructure (unsigned int index);	///< Retorna a estrutura de índice `index'
	unsigned int getStructureQuantity ();	///< Retorna o tanto de estruturas
	
	unsigned int getAdjQuantity ();		///< Retorna o tanto de vizinhos
	set<Region *> getNeighbourhood ();	///< Retorna o set de vizinhos
	bool isNeighbour (Region *region);	///< Essa região é vizinha de region?
	/// Conecta duas regiões
	void connect (Region *region);
	/** Desconecta duas regiões
	 * @return Desconectou?
	 */
	bool disconnect (Region *region);
	/// Calcula a distância entre duas regiões
	int getDistance (Region *region);

	/** @brief Representação em string dos tipos de regiões
	 * 
	 * @param[in] tipo Tipo da região
	 * 
	 * @return Nome do tipo da região
	 */
	static string RegionTypeName (Region_Type tipo);
	
	/* Constantes */
	/// Número máximo de vizinhos por região
	static const int MaxNeighbours = 4;
	/// Chance de ligar as regiões: bond_chance pra um de ligar
	/// @warning Se puser 1 ou zero nessa, sempre liga
	static const unsigned int bond_chance = 2;
};


#endif
