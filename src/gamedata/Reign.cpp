#include "Reign.hpp"

Reign::Reign () {}


Reign::Reign (initializer_list<Region *> regions) : all_regions (regions) {}


bool Reign::addRegion (Region *reg) {
	return all_regions.insert (reg).second;
}


bool Reign::removeRegion (Region *reg) {
	return (bool) all_regions.erase (reg);
}


bool Reign::isRegionIn (Region *reg) {
	return (bool) all_regions.count (reg);
}

void Reign::turn_cycle () {
	add_ouro (2);
}
