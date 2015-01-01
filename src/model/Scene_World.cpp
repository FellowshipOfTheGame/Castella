#include "Scene_World.hpp"

Scene_World::Scene_World() : current ((*World::get_world ()->getRegionGraph ())[0])
{
    SceneControl::set_cur (Scenes::SCENE_WORLD);

	// Window: registra regiões no lua
	using namespace luabind;
	windows.push_back (new Window ("world.lua",
			[=] (lua_State *L) {
				World::registerOnLua (L);

				module (L) [
					class_<Scene_World> ("Scene_World")
						.def ("vaiPraRegiao", &Scene_World::goToRegion)
				];

				ScriptHandler::send_to_lua<int> (L, "tilesize", MapTile::TILESIZE);
				ScriptHandler::send_to_lua<Scene_World *> (L, "cena", this);
			}));
}


void Scene_World::goToRegion (Region *reg) {
	if (reg != current) {
		current = reg;
	}
	else {
		reg->print ();
		Scene::ptr = reg;
		SceneControl::set_next (Scenes::SCENE_REGION);
	}
}


Scene_World::~Scene_World() {}


void Scene_World::update() {
	Scene::update ();
}


void Scene_World::draw (SDL_Surface *screen) {
	fill_surface (screen, {0, 100, 0});
	Scene::draw (screen);
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

	write_text (current->getX () * MapTile::TILESIZE,
			current->getY () * MapTile::TILESIZE, screen, "player");
}


void Scene_World::mouseclick (int x, int y) {
	Scene::mouseclick (x, y);
}


void Scene_World::escape () {
	SceneControl::exitScene ();
}


void Scene_World::handle_scene_input (int input) {

}
