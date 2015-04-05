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

World::~World () {
	for (auto P : players) {
		delete P;
	}
}

RegionGraph * World::getRegionGraph () {
	return &regionMap;
}

void World::criaGrafo () {
	// loada o script, registra as coisa e roda (gerando o grafo)
	ScriptHandler S ("script/criaGrafo.lua");
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
		class_<World> ("World")
			.def ("addPlayers", &World::addPlayers),
		// Grafo
		class_<RegionGraph> ("RegionGraph")
			.def ("novaRegiao", &RegionGraph::newRegion)
			.def ("criaConexoes", &RegionGraph::checkNeighbourhood)
			.def ("get", &RegionGraph::operator[])
			.def ("size", &RegionGraph::size)
			.def ("print", &RegionGraph::printGraph)
			.def ("printInfo", &RegionGraph::printGraphInfo)
			.enum_("constantes") [
				value ("altura", RegionGraph::graph_height),
				value ("largura", RegionGraph::graph_width),
				value ("tamanho_bloco", RegionGraph::block_size),
				value ("MaxNeighbours", Region::MaxNeighbours)
			],
		// Regiões
		class_<Region> ("Region")
			.def ("print", &Region::print)
			.def ("getId", &Region::getId)
			.def ("getX", &Region::getX)
			.def ("getY", &Region::getY)
			.def ("getType", &Region::getType)
			.def ("getStructure", &Region::getStructure)
			.def ("getStructureQuantity", &Region::getStructureQuantity)
			.def ("getDistance", &Region::getDistance)
			.def ("getAdjQuantity", &Region::getAdjQuantity)
			.def ("connect", &Region::connect)
			.def ("disconnect", &Region::disconnect)
			.scope [
				def ("getTypeName", &Region::RegionTypeName)
			],
		class_<Structure> ("Structure")
			.def ("getType", &Structure::getType)
			.scope [
				def ("getTypeName", &Structure::StructureTypeName)
			]
	];

	ScriptHandler::send_to_lua<World *> (L, "mundo", get_world ());
	ScriptHandler::send_to_lua<RegionGraph *> (L, "grafo",
			get_world ()->getRegionGraph ());
}

void World::create_players(){
	ScriptHandler S ("script/players.lua");
	registerOnLua (S.state ());
	Player::registerOnLua (S.state ());
	S.run_lua ();

	// Põe player 1 (o humano) na região 0, e a registra em seu reino
	auto human = get_human ();
	auto regionZero = regionMap[0];
	human->setRegion (regionZero);
	human->getReign ()->addRegion (regionZero);

}

void World::addPlayers (LuaObject player_table) {
	LuaTable T (player_table);

	for (LuaObject obj : T) {
		LuaTable player (obj);

		cout << "\tcarregou player: " << player.getString ("nome") << '\n';

		vector<Actor *> actors;

		for (LuaObject act : player.getLuaTable ("actors")) {
			LuaTable A (act);
			actors.push_back (new Actor (A.getString (1),
					A.getInt (2), A.getInt (3), A.getInt (4)));
		}

		players.push_back (new Player (actors));
	}
}

Player * World::get_player(int pos){ // utilizar a ID, em vez de posição ou verificar consistência
    return players[pos];
}

void World::load_skills(){
    Skill::add_skill_table ("attack", "skills");
}

World * World::world = nullptr;
