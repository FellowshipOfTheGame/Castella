#include "FileContainer.hpp"

FileContainer::FileContainer()
{
    //ctor
}

FileContainer::~FileContainer()
{
    for(int i=surfaces.size()-1; i>=0; i--){
        SDL_FreeSurface((surfaces[i]));
    }
}
//Pushes a pointer to a SDL_Surface into the surfaces vector, from a filename
SDL_Surface* FileContainer::push(string filename){
    SDL_Surface* surface = NULL;
    surface = load_image(filename.c_str());
    surfaces.push_back(surface);
    return surface;
}
