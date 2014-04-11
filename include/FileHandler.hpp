#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_mixer.h"
#include "simpleSDLfunctions.h"
#include <sstream>
#include <string>
#include <vector>
#include <list>


class FileHandler
{
    public:
        FileHandler();
        static SDL_Surface* load_img(string filename);

    private:
        static const string imagePath;

};

#endif // FILEHANDLER_H
