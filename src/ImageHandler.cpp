#include "ImageHandler.hpp"

ImageHandler::ImageHandler()
{
    //ctor
}

ImageHandler::~ImageHandler()
{
    //dtor
}

SDL_Surface* ImageHandler::make_window(SDL_Rect wRect, SDL_Surface *windowSkin){
    SDL_Surface *window = NULL;
    window = SDL_CreateRGBSurface(SDL_SWSURFACE, wRect.w, wRect.h, windowSkin->format->BitsPerPixel, windowSkin->format->Rmask, windowSkin->format->Gmask, windowSkin->format->Bmask, 0); //0xXX00FF00 para tirar o magenta, mas transparece as outras
    if(SDL_MUSTLOCK(window)){
            SDL_LockSurface(window);
    }
    Uint32 *pixelsW = (Uint32*)window->pixels;
    Uint32 *pixelsS = (Uint32*)windowSkin->pixels;

    //Corners
    for(int i=0; i<10; i++){
        for(int j=0; j<10; j++){
            pixelsW[i*window->w +j] = pixelsS[i*windowSkin->w +j];
            pixelsW[(window->h-i-1)*window->w +j] = pixelsS[(windowSkin->w-i-1)*windowSkin->w +j];
            pixelsW[i*window->w + (window->w-j-1)] = pixelsS[i*windowSkin->w + (windowSkin->w-j-1)];
            pixelsW[(window->h-i-1)*window->w + (window->w-j-1)] = pixelsS[(windowSkin->w-i-1)*windowSkin->w + (windowSkin->w-j-1)];
        }
    }
    //Sides
    //Horizontal
    for(int i=10, skinY=10; i < window->h-10; i++, skinY++){
        if(skinY==windowSkin->w-10) skinY = 10;
        for(int j=0; j<10; j++){
            pixelsW[i*window->w +j] = pixelsS[skinY*windowSkin->w +j];
            pixelsW[i*window->w +(window->w-j-1)] = pixelsS[skinY*windowSkin->w +(windowSkin->w-j-1)];
        }
    }
    //Vertical
    for(int j=10, skinX=10; j < window->w-10; j++, skinX++){
        if(skinX==windowSkin->w-10) skinX = 10;
        for(int i=0; i<10; i++){
            pixelsW[i*window->w +j] = pixelsS[i*windowSkin->w +skinX];
            pixelsW[(window->h-i-1)*window->w +j] = pixelsS[(windowSkin->w-i-1)*windowSkin->w + skinX];
        }
    }

    //Window core
    for(int i=10; i < window->h-10; i++){
        for(int j=10; j < window->w-10; j++){
            pixelsW[i*window->w +j] = pixelsS[(windowSkin->w/2)*(windowSkin->w+1)]; //(h/2)*w +w/2 = (w/2)*(w+1)
        }
    }

    //Definir cor chave
    Uint32 corchave = SDL_MapRGB(window->format, 0xFF, 0, 0xFF);
    //Tornar a cor chave transparente
    SDL_SetColorKey(window, SDL_SRCCOLORKEY, corchave);

    return window;
}
