#include <Scene_World.hpp>

Scene_World::Scene_World()
{
    SceneControl::set_cur(SceneControl::SCENE_WORLD);
    
    map = new Map_World ();
    //~ windows.push_back(new Window("newgame.lua"));
}

Scene_World::~Scene_World()
{
	delete (map);
    //dtor
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
	x /= MapTile::TILESIZE;
	y /= MapTile::TILESIZE;
	std::cout << "x: " << x << " ; y: " << y << '\n';
}

void Scene_World::escape () {
	SceneControl::set_next (SceneControl::SCENE_START_MENU);
}

void Scene_World::handle_scene_input (int input) {

}
