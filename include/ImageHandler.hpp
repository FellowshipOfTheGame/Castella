#ifndef IMAGEHANDLER_H
#define IMAGEHANDLER_H

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

class ImageHandler
{
    public:
        ImageHandler();
        virtual ~ImageHandler();

        static SDL_Surface* make_window(SDL_Rect wRect, SDL_Surface *windowSkin);

    protected:
    private:
};

#endif // IMAGEHANDLER_H
