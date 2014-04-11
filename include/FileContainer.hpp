#ifndef FILECONTAINER_H
#define FILECONTAINER_H

#include "FileHandler.hpp"

class FileContainer
{
    public:
        FileContainer();
        virtual ~FileContainer();

        void push(SDL_Surface* surface);
        SDL_Surface* push(string filename);

    protected:
        vector<SDL_Surface*> surfaces;

    private:
};

#endif // FILECONTAINER_H
