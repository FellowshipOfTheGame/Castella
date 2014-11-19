#include "World.hpp"

World::World () {}

World* World::get_world(){
    if(world == nullptr){
        world = new World();
		// Cria grafo a partir do Lua
		world->criaGrafo ();
    }
    return world;
}

RegionGraph * World::getRegionGraph () {
	return &regionMap;
}

void World::criaGrafo () {
	ScriptHandler S;

	// loada o script, registra as coisa e roda (gerando o grafo)
	S.load ("script/criaGrafo.lua");
	registerOnLua (S.state ());
	S.run_lua ();
}

void World::registerOnLua (lua_State *L) {
	using namespace luabind;

	module (L) [
		// Grafo
		class_<RegionGraph> ("RegionGraph")
			.def ("novaRegiao", &RegionGraph::newRegion)
			.def ("criaConexoes", &RegionGraph::checkNeighbourhood)
			.def ("get", &RegionGraph::operator[])
			.def ("size", &RegionGraph::size) 
			.enum_("constantes") [
				value ("altura", RegionGraph::graph_height),
				value ("largura", RegionGraph::graph_width),
				value ("tamanho_bloco", RegionGraph::block_size)
			],
		// Regiões
		class_<Region> ("Region")
			.def ("print", &Region::print)
			.def ("getX", &Region::getX)
			.def ("getY", &Region::getY)
	];

	ScriptHandler::send_to_lua<RegionGraph *> (L, 
			get_world ()->getRegionGraph (), "grafo");
}

World * World::world = nullptr;
