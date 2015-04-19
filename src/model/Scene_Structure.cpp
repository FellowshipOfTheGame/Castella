#include "Scene_Structure.hpp"
#include "World.hpp"


Scene_Structure::Scene_Structure () {
	SceneControl::set_cur (Scenes::SCENE_STRUCTURE);
	current = (Structure *) Scene::ptr;

	windows.push_back (new Window ("structure.lua", [=] (lua_State *L) {
				World::registerOnLua (L);
				ScriptHandler::send_to_lua<Structure *> (L, "struct", current);
			}));
}


Scene_Structure::~Scene_Structure () {}


void Scene_Structure::update () {
	Scene::update ();
}


void Scene_Structure::redraw () {}


void Scene_Structure::mouseclick (int x, int y) {
	Scene::mouseclick (x, y);
}


void Scene_Structure::escape () {
	SceneControl::exitScene ();
}
