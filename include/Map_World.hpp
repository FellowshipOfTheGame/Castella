/** @file Map_World.hpp
 * Mapa mundi, com as regiões
 *
 * Header do gamedata/Map_World.cpp
 */

#ifndef MAP_WORLD_HPP
#define MAP_WORLD_HPP

#include <SDL/SDL_gfxPrimitives.h>

#include "MapTile.hpp"
#include "FileContainer.hpp"
#include "RegionGraph.hpp"
#include "World.hpp"

/** @brief Mapa Mundi
 * 
 * É o mapa global, formatado em tiles
 */
class Map_World {
private:

public:
	void draw (SDL_Surface *screen);
	Map_World ();
	Region *getRegion (int x, int y);
	
	// Constantes
	static const int map_height = RegionGraph::graph_height * RegionGraph::block_size;
	static const int map_width = RegionGraph::graph_height * RegionGraph::block_size;
	
protected:
	MapTile tileMap[map_height][map_width];
	FileContainer tiles;
	RegionGraph *graph;
};


#endif
