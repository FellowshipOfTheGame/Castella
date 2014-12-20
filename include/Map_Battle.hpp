#ifndef MAP_BATTLE_H
#define MAP_BATTLE_H

#include "MapTile.hpp"
#include "FileContainer.hpp"
#include "Actor_Battler.hpp"

bool compare_battler_y(const void* b1, const void* b2); //compares battlers y position

class Map_Battle
{
    public:
        Map_Battle(int width, int height);
        Map_Battle(std::string filename);
        virtual ~Map_Battle();
        void draw(SDL_Surface *screen, std::vector<Actor_Battler*> battlersTeam1, std::vector<Actor_Battler*> battlersTeam2, bool displayHUD = true);
        //Recebe a posição no mapa e a lista de battlers a ser pesquisada
        Actor_Battler* get_battler_at(SDL_Rect position, std::vector<Actor_Battler*> battlers);

    protected:
        int width, height;
        vector<MapTile> tileMap;
        FileContainer tiles;
        //Actor_Battler *battlers[6];

    private:
};

#endif // MAP_BATTLE_H
