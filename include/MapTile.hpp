#ifndef MAPTILE_H
#define MAPTILE_H

#include "FileHandler.hpp"
#include "Actor_Battler.hpp"


enum TERRAIN {
	NONE = 0,
    TRR_GRASS,
    TRR_DIRT,
    TRR_STONE,
    TRR_SAND,
    // tiles do mapa mundi
	WRLD_BKGD,		///< Fundo do mundo
	WRLD_RGN		///< Regiões, no mundo
};

class MapTile
{
    public:
        MapTile();	///< Ctor default
        MapTile(int x, int y, TERRAIN type);
        void setTile (int x, int y, TERRAIN type);
        virtual ~MapTile();
        virtual void update();
        virtual void draw(SDL_Surface *screen);
        virtual void set_terrain_image(SDL_Surface *tileImage); //It will be called from Map_Battle; TODO - move surface definition to the constructor, using type; a Global scoped FileContainer (with indexed surfaces) should handle it
        virtual void push_object(SDL_Surface *object);
        virtual void add_unit(Actor_Battler *unit);
        virtual void remove_unit();
        virtual int get_passability(); // use return 0 for not passable at all
        /* UserPointer: qualquer coisa pode estar aqui */
        void *getPtr ();
        void setPtr (void *ptr);

        static const short int TILESIZE;

    protected:
    private:
        int posX, posY;
        int type;
        SDL_Surface *terrain; //the terrain image
        list<SDL_Surface*> objects; //opitional objects to be put onto the tile
        void *ptr;	///< Ponteiro opcional (e de qualquer tipo), para por qualquer coisa num tile!
        Actor_Battler *unit;
        int passability; //make it a 8-value mask
};

#endif // MAPTILE_H
