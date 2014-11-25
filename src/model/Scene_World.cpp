#include <Scene_World.hpp>

Scene_World::Scene_World()
{
    SceneControl::set_cur (Scenes::SCENE_WORLD);
    
	//map = new Map_World ();

	// Window: registra regiões no lua
	using namespace luabind;
	windows.push_back (new Window ("world.lua",
			[] (lua_State *L) {
				World::registerOnLua (L);

				ScriptHandler::send_to_lua<int> (L, MapTile::TILESIZE, "tilesize");

				module (L) [
					def ("vaiPraRegiao", &Scene_World::goToRegion)
				];
			}));
}


void Scene_World::goToRegion (Region *reg) {
	reg->print ();
	Scene::ptr = reg;
	SceneControl::set_next (Scenes::SCENE_REGION);
}


Scene_World::~Scene_World()
{
	//delete (map);
}


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
	
	// Mostra info da região no stdout
	//x /= MapTile::TILESIZE;
	//y /= MapTile::TILESIZE;
	//if (x < Map_World::map_width && y < Map_World::map_height) {
		//std::cout << "Clicou no mapa;		X: " << x << " ; Y: " << y << '\n';
		//Region *reg = map->getRegion (x, y);
		//// se é uma região de fato, escreve info no stdout e entra na scene dela
		//if (reg != nullptr) {
			//goToRegion (reg);
		//}
	//}
}


void Scene_World::escape () {
	SceneControl::exitScene ();
}


void Scene_World::handle_scene_input (int input) {

}
