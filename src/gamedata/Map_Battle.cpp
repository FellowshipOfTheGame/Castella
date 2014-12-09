#include <Map_Battle.hpp>
#include <algorithm>

Map_Battle::Map_Battle(int width, int height)
{
    //Initialize map with the terrain tags
    this->width = width;
    this->height = height;
    //int mapMatrix[width][height];
    SDL_Surface *grass = tiles.push("images/tiles/grass.png");
    SDL_Surface *dirt = tiles.push("images/tiles/dirt.png");
    SDL_Surface *stone = tiles.push("images/tiles/stone.png");
    for(int i=0; i<height; i++){
        for(int j=0; j<width; j++){
            if(i==6 && j==14){ //dirt
                tileMap.push_back(MapTile(j,i,TRR_DIRT));
                tileMap[i*width+j].set_terrain_image(dirt);
                //mapMatrix[i][j] = TRR_DIRT;
            }
            else if(i==0 || i==height-1){
                tileMap.push_back(MapTile(j,i,TRR_STONE));
                tileMap[i*width+j].set_terrain_image(stone);
                //mapMatrix[i][j] = TRR_STONE;
            }
            else{ //grass
                tileMap.push_back(MapTile(j,i,TRR_GRASS));
                tileMap[i*width+j].set_terrain_image(grass);
                //mapMatrix[i][j] = TRR_GRASS;
            }
        }
    }
}

Map_Battle::Map_Battle(std::string filename){
    //load map from file
}

Map_Battle::~Map_Battle()
{
    //dtor
}

void Map_Battle::draw(SDL_Surface *screen, std::vector<Actor_Battler*> battlersTeam1, std::vector<Actor_Battler*> battlersTeam2){
    //Draws map tiles
    for(int i=0; i<height; i++){
        for(int j=0; j<width; j++){
            tileMap[i*width+j].draw(screen);
        }
    }
    //Concatena os vetores dos times
    std::vector<Actor_Battler*> battlers = battlersTeam1;
    battlers.insert(battlers.end(), battlersTeam2.begin(), battlersTeam2.end());
    //Ordena os battlers da menor posição em y para a maior, para desenhá-los com a sobreposição correta
    sort(battlers.begin(), battlers.end(), compare_battler_y);
    //Draws battlers
    for (auto battlersIt : battlers){
        int clip = 7; //deve ser escolhido de acordo com a orientação e com o movimento do actor
        int x = (battlersIt)->get_map_pos().x * MapTile::TILESIZE;
        int y = (battlersIt)->get_map_pos().y * MapTile::TILESIZE;
        (battlersIt)->draw(x+MapTile::TILESIZE/2, y-18, clip, screen);
    }

}

bool compare_battler_y(const void* b1, const void* b2){
    if ( ((Actor_Battler*)b1)->get_map_pos().y < ((Actor_Battler*)b2)->get_map_pos().y){
        return true;
    }
    return false;
}

Actor_Battler* Map_Battle::get_battler_at(SDL_Rect position, std::vector<Actor_Battler*> battlers){
    for (auto btlr : battlers){
        if (btlr->get_map_pos().x == position.x && btlr->get_map_pos().y == position.y){
            return btlr;
        }
    }
    return nullptr;
}
