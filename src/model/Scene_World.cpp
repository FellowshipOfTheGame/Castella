#include "Scene_World.hpp"

Scene_World::Scene_World()
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
	auto current = human->getRegion ();

	if (current->isNeighbour (reg)) {
		human->setRegion (reg);
		// testezim: add ouro só pra ver o trem trocar
		human->getReign ()->add_ouro (2);
	}
	else if (reg == current) {
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

	auto current = human->getRegion ();
	write_text (current->getX () * MapTile::TILESIZE,
			current->getY () * MapTile::TILESIZE, screen, "player");

	// escreve recursos no canto superior esquerdo da tela
	int i = 0;
	auto reign = human->getReign ();
	ostringstream str;
#define escreve_recurso(recurso) \
	str.str (""); \
	str << #recurso << ' ' << reign->get_ ## recurso (); \
	write_text (0, i, screen, str.str ()); \
	i += DEFAULT_FONT_SIZE
	escreve_recurso (tecido);
	escreve_recurso (ouro);
	escreve_recurso (gemas);
	escreve_recurso (madeira);
	escreve_recurso (ervas);
	escreve_recurso (couro);
	escreve_recurso (pedra);
	escreve_recurso (ferro);
#undef escreve_recurso
}


void Scene_World::mouseclick (int x, int y) {
	Scene::mouseclick (x, y);
}


void Scene_World::escape () {
	SceneControl::exitScene ();
}


void Scene_World::handle_scene_input (int input) {

}
