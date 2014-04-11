#ifndef MAPTILE_H
#define MAPTILE_H

#include "FileHandler.hpp"
#include "Actor_Battler.hpp"


enum TERRAIN{
    TRR_GRASS = 1,
    TRR_DIRT,
    TRR_STONE,
    TRR_SAND,

};

class MapTile
{
    public:
        MapTile(int x, int y, int type);
        virtual ~MapTile();
        virtual void update();
        virtual void draw(SDL_Surface *screen);
        virtual void set_terrain_image(SDL_Surface *tileImage); //It will be called from Map_Battle; TODO - move surface definition to the constructor, using type; a Global scoped FileContainer (with indexed surfaces) should handle it
        virtual void push_object(SDL_Surface *object);
        virtual void add_unit(Actor_Battler *unit);
        virtual void remove_unit();
        virtual int get_passability(); // use return 0 for not passable at all

        static const short int TILESIZE;

    protected:
    private:
        int posX, posY;
        int type;
        SDL_Surface *terrain; //the terrain image
        list<SDL_Surface*> objects; //opitional objects to be put onto the tile
        Actor_Battler *unit;
        int passability; //make it a 8-value mask
};

#endif // MAPTILE_H
