#include <Scene_World.hpp>

Scene_World::Scene_World()
{
    SceneControl::set_cur (Scenes::SCENE_WORLD);
    
    map = new Map_World ();
    //~ windows.push_back(new Window("newgame.lua"));
}

Scene_World::~Scene_World()
{
	delete (map);
}

void Scene_World::update() {
	Scene::update ();
}

void Scene_World::draw (SDL_Surface *screen) {
	Scene::draw (screen);
	map->draw (screen);
}

void Scene_World::mouseclick (int x, int y) {
	Scene::mouseclick (x, y);
	
	// Mostra info da região no stdout
	x /= MapTile::TILESIZE;
	y /= MapTile::TILESIZE;
	if (x < Map_World::map_width && y < Map_World::map_height) {
		std::cout << "Clicou no mapa;		X: " << x << " ; Y: " << y << '\n';
		Region *reg = map->getRegion (x, y);
		// se é uma região de fato, escreve as info no stdout e entra na scene dela
		if (reg != nullptr) {
			reg->print ();
			SceneControl::set_next (Scenes::SCENE_REGION);
			Scene::ptr = reg;
		}
	}
}

void Scene_World::escape () {
	SceneControl::exitScene ();
}

void Scene_World::handle_scene_input (int input) {

}
