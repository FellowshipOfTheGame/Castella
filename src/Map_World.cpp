#include <Map_World.hpp>

const int Map_World::factor = MapTile::TILESIZE;

Map_World::Map_World () : height (RegionGraph::map_height), width (RegionGraph::map_width) {
	graph = World::get_world ()->getRegionGraph ();

	SDL_Surface *background = tiles.push("images/tiles/world_background.png");
	SDL_Surface *region = tiles.push("images/tiles/world_region.png");

	for (int i = 0; i < height * RegionGraph::block_size; i++) {
		for (int j = 0; j < width * RegionGraph::block_size; j++) {
			tileMap.push_back (MapTile (j, i, WRLD_BKGD));
			tileMap[tileMap.size () - 1].set_terrain_image (background);
		}
	}

	for (int i = 0; i < height * width; i++) {
		tileMap.push_back (MapTile (graph->get(i)->getX (), graph->get(i)->getY (), WRLD_RGN));
		tileMap[tileMap.size () - 1].set_terrain_image (region);
	}
}


void Map_World::draw (SDL_Surface *screen) {
	// desenha os tiles
	for (unsigned int i = 0; i < tileMap.size (); i++) {
		tileMap[i].draw (screen);
	}
	
	// desenha as linhas que mostram os caminhos entre as regiões
	for (int i = 0; i < width * height; i++) {
		Region *reg = graph->get(i);
		for (int j = 0; j < reg->getAdjQuantity (); j++) {
			Region *neighbour = reg->getNeighbour (j);
			lineColor (screen, reg->getX () * MapTile::TILESIZE + (MapTile::TILESIZE/2), reg->getY () * MapTile::TILESIZE + (MapTile::TILESIZE/2), neighbour->getX () * MapTile::TILESIZE + (MapTile::TILESIZE/2), neighbour->getY () * MapTile::TILESIZE + (MapTile::TILESIZE/2), 0x000000ff);
		}
	}
}
