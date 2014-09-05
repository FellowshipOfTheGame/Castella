#include <Scene_Region.hpp>

Scene_Region::Scene_Region () {
	SceneControl::set_cur (Scenes::SCENE_REGION);
	current = (Region*) Scene::ptr;
}

Scene_Region::~Scene_Region () {}

void Scene_Region::update () {
	Scene::update ();
}

void Scene_Region::draw (SDL_Surface *screen) {	
	SDL_Color cor = {0, 255, 0};
	int i = 0;
	for (Structure *S : current->getStructures ()) {
		write_text (0, i * 20, screen, Structure_TypeName (S->getType ()), cor);
		i++;
	}

	Scene::draw (screen);
}

void Scene_Region::mouseclick (int x, int y) {
	Scene::mouseclick (x, y);
}

void Scene_Region::escape () {
	SceneControl::exitScene ();
}


void Scene_Region::handle_scene_input (int input) {
	
}
