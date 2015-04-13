/** @file Reign.hpp
 *
 * @brief Abstração do domínio do player, contendo posses de região e recursos
 *
 * Header do gamedata/Reign.cpp
 */
#ifndef REIGN_HPP
#define REIGN_HPP

#include "Region.hpp"
#include <set>

class Reign {
public:
	Reign ();
	Reign (initializer_list<Region *> regions);

	/** @brief Adiciona uma região a @ref all_regions
	 *
	 * @return Região já existia em all_regions?
	 */
	bool addRegion (Region *reg);
	/** @brief Verifica se reg pertence ao conjunto @ref all_regions
	 *
	 * @return "reg" está em all_regions?
	 */
	bool isRegionIn (Region *reg);
	/** @brief Remove uma região do conjunto
	 *
	 * @return Região existia em all_regions?
	 */
	bool removeRegion (Region *reg);
	
	/// Atualiza por ciclo. @sa World::turn_cycle
	void turn_cycle ();

/* GETTER Recursos -> get_recurso (), construído com MACRO; por que não? */
#define get_recurso(recurso) \
	unsigned int get_ ## recurso () { \
		return this->recurso; \
	}
	get_recurso (tecido);
	get_recurso (ouro);
	get_recurso (gemas);
	get_recurso (madeira);
	get_recurso (ervas);
	get_recurso (couro);
	get_recurso (pedra);
	get_recurso (ferro);
#undef get_recurso
/* Adiciona quantidade em recurso -> add_recurso (qtd) */
#define add_recurso(recurso) \
	void add_ ## recurso (unsigned int quantidade) { \
		this->recurso += quantidade; \
	}
	add_recurso (tecido);
	add_recurso (ouro);
	add_recurso (gemas);
	add_recurso (madeira);
	add_recurso (ervas);
	add_recurso (couro);
	add_recurso (pedra);
	add_recurso (ferro);
#undef add_recurso
/* Subtrai quantidade em recurso -> sub_recurso (qtd) */
#define sub_recurso(recurso) \
	void sub_ ## recurso (unsigned int quantidade) { \
		this->recurso -= quantidade; \
	}
	sub_recurso (tecido);
	sub_recurso (ouro);
	sub_recurso (gemas);
	sub_recurso (madeira);
	sub_recurso (ervas);
	sub_recurso (couro);
	sub_recurso (pedra);
	sub_recurso (ferro);
#undef sub_recurso


private:
	/// As regiões que o reino engloba
	set<Region *> all_regions;

	/*    Recursos!    */
	// da Vila
	unsigned int tecido {0};
	unsigned int ouro {0};
	unsigned int gemas {0};
	// da floresta
	unsigned int madeira {0};
	unsigned int ervas {0};
	unsigned int couro {0};
	// da caverna
	unsigned int pedra {0};
	unsigned int ferro {0};
};

#endif
