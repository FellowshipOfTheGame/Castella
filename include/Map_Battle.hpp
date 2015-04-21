#ifndef MAP_BATTLE_H
#define MAP_BATTLE_H

#include "Drawable.hpp"
#include "MapTile.hpp"
#include "FileContainer.hpp"
#include "Actor_Battler.hpp"

bool compare_battler_y(const void* b1, const void* b2); //compares battlers y position

class Map_Battle : public Drawable
{
    public:
        Map_Battle(int width, int height);
        Map_Battle(std::string filename);
        ~Map_Battle();

        void redraw ();
        //Recebe a posição no mapa e a lista de battlers a ser pesquisada
        Actor_Battler * get_battler_at(SDL_Rect position, std::vector<Actor_Battler*> battlers);

		/// Setta os battlers, a ser feito no começo da batalha
		void set_battlers (vector<Actor_Battler*> battlersTeam1, vector<Actor_Battler*> battlersTeam2);

		/// Setta se precisa mostrar o HUD
		void set_displayHUD (bool displayHUD);

    protected:
        int width, height;
        vector<MapTile> tileMap;
        FileContainer tiles;
		vector<Actor_Battler *> battlers;

		bool displayHUD;

    private:
};

#endif // MAP_BATTLE_H
