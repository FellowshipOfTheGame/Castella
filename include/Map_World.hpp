/** @file Map_World.hpp
 * Mapa mundi, com as regiões
 */

#ifndef MAP_WORLD_HPP
#define MAP_WORLD_HPP

#include <MapTile.hpp>
#include <FileContainer.hpp>
#include <RegionGraph.hpp>
#include <World.hpp>
#include <SDL/SDL_gfxPrimitives.h>

/** @brief Mapa Mundi
 * 
 * É o mapa global, formatado em tiles
 */
class Map_World {
private:
	
protected:
	static const int height = RegionGraph::map_height * RegionGraph::block_size;
	static const int width = RegionGraph::map_height * RegionGraph::block_size;
	
	MapTile tileMap[height][width];
	FileContainer tiles;
	RegionGraph *graph;

public:
	void draw (SDL_Surface *screen);
	Map_World ();
};


#endif
