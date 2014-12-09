#include "World.hpp"

World::World () {}

World* World::get_world(){
    if(world == nullptr){
        world = new World();
		// Cria grafo a partir do Lua
		world->criaGrafo ();
		// Cria os players
		world->create_players();
		// pega as funções do Lua
		world->getActorFunctions ();
		// Carrega as skills
		world->load_skills();
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

void World::getActorFunctions () {
	Actor_Battler::registerOnLua (Actor::sH.state ());
	Actor::sH.load ("script/actor_funcs.lua");
	Actor::sH.run_lua ();
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
			.def ("getType", &Region::getType)
	];

	ScriptHandler::send_to_lua<RegionGraph *> (L, "grafo",
			get_world ()->getRegionGraph ());
}

void World::create_players(){
    players.push_back(Player ( new Actor("actor2.png", 6, 6, 9, 6) )); //player 0 e seu líder
    players.push_back(Player ( new Actor("actor1.png", 7, 7, 25, 7) )); //player 1 e seu líder
    //Insere mais dois actors para cada um dos dois primeiros players
    for (int i=0; i < 2; i++){
        players[0].add_actor( new Actor("actor1black.png"));
        players[1].add_actor( new Actor("actor1.png"));
    }

    for (int n=0; n<10; n++){
        players.push_back(Player( new Actor("actor1.png") ));
    }
}

Player* World::get_player(int pos){ // utilizar a ID, em vez de posição ou verificar consistência
    return &players[pos];
}

void World::load_skills(){
    Skill::add_skill("attack", "ataque");
}

World * World::world = nullptr;
