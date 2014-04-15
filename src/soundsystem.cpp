#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <iostream>

#include <SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>

#include "SoundManager.hpp"

#define PI 3.14159265
#define MYCHUNKSIZE 1024
#define RELDIST(a, b) ( (a > b) ? (a - b) : (b - a) )
#define DISTANCE(x1, y1, x2, y2) sqrt( (double)RELDIST(x1, x2) * RELDIST(x1, x2) + RELDIST(y1, y2) * RELDIST(y1, y2) )
#define degrees(a) ( (int)(a * 180.0/PI ) )

SDL_Surface *getImage(const char *filename){
    SDL_Surface *raw = IMG_Load(filename);
    if ( raw == NULL ){
        std::cout << "IMAGE: Failed to load image.\n";
        return NULL;
    }
    SDL_Surface *finalSurface = SDL_DisplayFormat(raw);
    SDL_FreeSurface(raw);
    if ( finalSurface == NULL ){
        std::cout << "IMAGE: Failed to convert image to display format.\n";
        return NULL;
    }
    return finalSurface;
}

class SDLhandler{

    public:
        int initSDL( Uint32 flags ){
            if ( SDL_Init(flags) == -1 ){
                std::cout << "ERROR: SDL failed to initialize.\n";
                return -1;
            }
            return 0;
        }
        int initSubSDL( Uint32 flags ){
            if ( SDL_WasInit(flags) ){
                std::cout << "WARNING: subsystems already initialized.\n";
                return 0;
            }
            else{
                if ( SDL_InitSubSystem(flags) == -1) {
                    std::cout << "ERROR loading susbsystem.\n";
                    return -1;
                }
                return 0;
            }
        }
        int initMixer( int flags ){
            if ( ( Mix_Init(flags) & flags ) != flags ){
                std::cout << "Mixer: Failed to load the required support.\n";
                return -1;
            }
            return 0;
        }
        int initIMG( int flags ){
            if ( ( IMG_Init(flags) & flags ) != flags ){
                std::cout << "IMG: Failed to initialize the required support.\n";
                return -1;
            }
            return 0;
        }
        int initTTF(){
            if ( !TTF_WasInit() && TTF_Init() == -1 ){
                std::cout << "TTF: Error while initializing TTF.\n";
                return -1;
            }
            return 0;
        }
        void terminate(){
            if( IMG_Init(0) != 0 )    Mix_Quit();
            if( Mix_Init(0) != 0 )   IMG_Quit();
            if( TTF_WasInit() )     TTF_Quit();
            SDL_Quit();
        }
};

struct soundEffect{
    Mix_Chunk *chunk;
};

int main(){

    SDLhandler handleSDL;

    if ( handleSDL.initSDL(SDL_INIT_EVERYTHING) == -1 )  return -1;
    if ( handleSDL.initIMG(IMG_INIT_PNG) == -1 )  return -1;
    if ( handleSDL.initMixer(MIX_INIT_MOD) == -1 )   return -1;

    SDL_putenv("SDL_VIDEO_CENTERED=center");
    SDL_putenv("SDL_FBACCEL=1");
    SDL_SetVideoMode(800, 600, 32, SDL_SWSURFACE|SDL_DOUBLEBUF );
    SDL_Surface *display = SDL_GetVideoSurface();
    SDL_WM_SetCaption("Sound System", "Sound System");
    SDL_ShowCursor(SDL_DISABLE);

    SoundManager soundSys;
    SDL_Rect beePos, middlePos;

    if ( soundSys.initAudioSys( MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, MYCHUNKSIZE ) == -1 )    return -1;
    SDL_Event events;
    SDL_Surface *background = SDL_CreateRGBSurface( (display->flags), display->w, display->h, display->format->BitsPerPixel ,display->format->Rmask, display->format->Gmask, display->format->Bmask, display->format->Amask);
    SDL_Surface *beeimg = getImage("bee.png");
    SDL_Surface *middle = getImage("abc.png");
    SDL_SetColorKey( beeimg, SDL_SRCCOLORKEY|SDL_RLEACCEL, SDL_MapRGB(display->format, 255, 255, 255) );
    SDL_FillRect( background, NULL, SDL_MapRGB(background->format, 255, 255, 255) );
    middlePos.w = middlePos.h = 96;
    middlePos.x = display->w/2 - middlePos.w/2; middlePos.y = display->h/2 - middlePos.h/2;
    SDL_BlitSurface(middle, NULL, background, &middlePos);
    SDL_Flip(background);
    SDL_BlitSurface(background, NULL, display, NULL);
    SDL_Flip(display);

    soundEffect bee;
    beePos.w = 32; beePos.h = 42;

    bee.chunk = Mix_LoadWAV("bee.wav");
    bool exit = false,
          cut = false;

//Abelha
    soundSys.setChannelPos(0, soundSys.getAngle(display->w/2, display->h/2, display->w/2 - beePos.w/2, display->h/2 - beePos.h/2), soundSys.getDistance(display->w/2, display->h/2, display->w/2 - beePos.w/2, display->h/2 - beePos.h/2 ) );
    Mix_PlayChannel(0, bee.chunk, -1);

    while( !exit ){
        while( SDL_PollEvent(&events) ){
            //if( !Mix_Playing(0) )   cut = false;
            switch(events.type){
                /*case SDL_MOUSEBUTTONDOWN:
                    //cut = true;
                    soundSys.setChannelPos(0, getAngle(display->w/2, display->h/2, events.button.x, events.button.y), getDistance(display->w/2, display->h/2, events.button.x, events.button.y) );
                    Mix_PlayChannel(0, bee.chunk, -1);
                    break;*/
                case SDL_MOUSEMOTION:
                    //if ( cut ){
                        beePos.x = (events.motion.x - beePos.w/2);
                        beePos.y = (events.motion.y - beePos.h/2);
                        SDL_BlitSurface(background, NULL, display, NULL);
                        SDL_BlitSurface(beeimg, NULL, display, &beePos);
                        SDL_Flip(display);
                        Mix_Pause(0);
                        soundSys.setChannelPos(0, soundSys.getAngle(display->w/2, display->h/2, events.motion.x, events.motion.y), soundSys.getDistance(display->w/2, display->h/2, events.motion.x, events.motion.y) );
                        Mix_Resume(0);
                    //}
                    break;
                case SDL_QUIT:
                    exit = true;
                    break;
                default:
                    break;
            }
        }
    }

    SDL_FreeSurface(background);
    SDL_FreeSurface(beeimg);
    SDL_FreeSurface(middle);
    Mix_FreeChunk(bee.chunk);
    soundSys.terminateAudioSys();
    handleSDL.terminate();

    return 0;
}
