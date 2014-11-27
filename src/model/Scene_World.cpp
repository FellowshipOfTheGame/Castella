#include "Scene_World.hpp"

Scene_World::Scene_World()
{
    SceneControl::set_cur (Scenes::SCENE_WORLD);

	// Window: registra regiões no lua
	using namespace luabind;
	windows.push_back (new Window ("world.lua",
			[] (lua_State *L) {
				World::registerOnLua (L);

				ScriptHandler::send_to_lua<int> (L, MapTile::TILESIZE, "tilesize");

				module (L) [
					def ("vaiPraRegiao", &Scene_World::goToRegion),
					def ("regionTypeName", &Region::RegionTypeName)
				];
			}));
}


void Scene_World::goToRegion (Region *reg) {
	reg->print ();
	Scene::ptr = reg;
	SceneControl::set_next (Scenes::SCENE_REGION);
}


Scene_World::~Scene_World() {}


void Scene_World::update() {
	Scene::update ();
}


void Scene_World::draw (SDL_Surface *screen) {
	fill_surface (screen, {0, 100, 0});
	Scene::draw (screen);
	//map->draw (screen);
	// desenha as linhas que mostram os caminhos entre as regiões
	for (auto & reg : (*World::get_world ()->getRegionGraph ())) {
		for (auto neighbour : reg->getNeighbourhood ()) {
			lineColor (screen,
					// primeiro ponto
					reg->getX () * MapTile::TILESIZE + (MapTile::TILESIZE/2),
					reg->getY () * MapTile::TILESIZE + (MapTile::TILESIZE/2),
					// segundo ponto
					neighbour->getX () * MapTile::TILESIZE + (MapTile::TILESIZE/2),
					neighbour->getY () * MapTile::TILESIZE + (MapTile::TILESIZE/2),
					// joga aquele preto básico
					0x000000ff);
		}
	}
	
}


void Scene_World::mouseclick (int x, int y) {
	Scene::mouseclick (x, y);
}


void Scene_World::escape () {
	SceneControl::exitScene ();
}


void Scene_World::handle_scene_input (int input) {

}
