#include <Map_World.hpp>

Map_World::Map_World () {
	graph = World::get_world ()->getRegionGraph ();

	SDL_Surface *background = tiles.push ("images/tiles/world_background.png");
	SDL_Surface *region = tiles.push ("images/tiles/world_region.png");

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			tileMap[i][j].setTile (j, i, WRLD_BKGD);
			tileMap[i][j].set_terrain_image (background);
		}
	}

	for (int i = 0; i < RegionGraph::map_height * RegionGraph::map_width; i++) {
		int y = (*graph)[i]->getY ();
		int x = (*graph)[i]->getX ();
		// tem uma região aqui
		tileMap[y][x].setPtr ((*graph)[i]);
		tileMap[y][x].setTile (x, y, WRLD_RGN);
		tileMap[y][x].set_terrain_image (region);
	}
}


void Map_World::draw (SDL_Surface *screen) {
	// desenha os tiles
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			tileMap[i][j].draw (screen);
		}
	}
	
	// desenha as linhas que mostram os caminhos entre as regiões
	for (int i = 0; i < RegionGraph::map_height * RegionGraph::map_width; i++) {
		Region *reg = (*graph)[i];
		for (Region *neighbour : reg->getNeighbourhood ()) {
			lineColor (screen, reg->getX () * MapTile::TILESIZE + (MapTile::TILESIZE/2), 
					reg->getY () * MapTile::TILESIZE + (MapTile::TILESIZE/2), 
					neighbour->getX () * MapTile::TILESIZE + (MapTile::TILESIZE/2),
					neighbour->getY () * MapTile::TILESIZE + (MapTile::TILESIZE/2), 0x000000ff);
		}
	}
}
