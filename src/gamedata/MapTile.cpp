#include <MapTile.hpp>

MapTile::MapTile() : MapTile (0, 0, NONE) {}

MapTile::MapTile(int x, int y, TERRAIN type)
{
	setTile (x, y, type);
    if(type >= 0) passability = 0b11111111;
}

void MapTile::setTile (int x, int y, TERRAIN type) {
    posX = x;
    posY = y;
    this->type = type;	
}

MapTile::~MapTile()
{
    //dtor
}

void MapTile::update(){}
void MapTile::draw(SDL_Surface *screen){
    apply_surface(posX*TILESIZE, posY*TILESIZE, terrain, screen);
    //here, iterate through objects and draw them

}

void MapTile::set_terrain_image(SDL_Surface *tileImage){
    terrain = tileImage;
}

void MapTile::push_object(SDL_Surface *object){
    objects.push_back(object);
}

void MapTile::add_unit(Actor_Battler *unit){
    this->unit = unit;
}

void MapTile::remove_unit(){
    unit = NULL;
}

int MapTile::get_passability(){
    if(unit != NULL){
        return (unit->is_passable() & passability);
    }
    else return passability; //TODO: should use a passability mask instead, for the 4 directions, inwards or outwards (8 mask values)
}

/* User Pointer */
void *MapTile::getPtr () {
	return ptr;
}

void MapTile::setPtr (void *ptr) {
	this->ptr = ptr;
}


const short int MapTile::TILESIZE = 64;
