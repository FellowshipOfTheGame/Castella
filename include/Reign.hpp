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

private:
	/// As regiões que o reino engloba
	set<Region *> all_regions;
};

#endif
