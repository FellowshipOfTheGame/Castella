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

private:
	/// As regiões que o reino engloba
	set<Region *> all_regions;
};

#endif
