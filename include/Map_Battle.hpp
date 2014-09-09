#ifndef MAP_BATTLE_H
#define MAP_BATTLE_H

#include "MapTile.hpp"
#include "FileContainer.hpp"
#include "Actor_Battler.hpp"


class Map_Battle
{
    public:
        Map_Battle(int width, int height);
        Map_Battle(std::string filename);
        virtual ~Map_Battle();

        void draw(SDL_Surface *screen);

    protected:
        int width, height;
        vector<MapTile> tileMap;
        FileContainer tiles;
        Actor_Battler *battlers[6];

    private:
};

#endif // MAP_BATTLE_H
