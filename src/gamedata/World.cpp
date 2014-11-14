#include <World.hpp>
#include <stdlib.h>

World::World()
{
    //ctor
}

World::~World()
{
    delete world;
    //dtor
}

World* World::get_world(){
    if(world == NULL){
        world = new World();
    }
    return world;
}

World* World::world = NULL;


RegionGraph *World::getRegionGraph () {
	return &regionMap;
}
