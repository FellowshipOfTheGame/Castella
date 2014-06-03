/** @file Map_World.hpp
 * Mapa mundi, com as regiões
 */

#ifndef MAP_WORLD_HPP
#define MAP_WORLD_HPP

#include <MapTile.hpp>
#include <FileContainer.hpp>
#include <Region.hpp>
#include <World.hpp>
#include <SDL/SDL_gfxPrimitives.h>

/** @brief Mapa Mundi
 * 
 * É o mapa global, formatado em tiles, a partir do tamanho do 
 */
class Map_World {
private:
	static const int factor;
	
protected:
	int height;
	int width;
	
	vector<MapTile> tileMap;
	FileContainer tiles;
	RegionGraph *graph;

public:
	void draw (SDL_Surface *screen);
	Map_World ();
};


#endif
