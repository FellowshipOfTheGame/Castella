#include "soundManager.hpp"

#define PI 3.14159265
#define RELDIST(a, b) ( (a > b) ? (a - b) : (b - a) ) //Calcula a distancia em uma dimensão
#define DISTANCE(x1, y1, x2, y2) sqrt( (double)RELDIST(x1, x2) * RELDIST(x1, x2) + RELDIST(y1, y2) * RELDIST(y1, y2) ) //Calcula a distancia em 2 dimensões
#define degrees(a) ( (int)(a * 180.0/PI ) ) //Converte um ângulo em radianos para graus.
#define REMOVE //

#define DEFAULT_CHUNKSIZE 1024

#ifdef NDEBUG
#define REMOVE
#endif

soundManager::soundManager(){ init(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, DEFAULT_CHUNKSIZE); }
soundManager::soundManager(int frequency, Uint16 format, int superchannels, int chunksize){ init(frequency, format, superchannels, chunksize); }
soundManager::~soundManager(){ this->terminate(); }

void soundManager::init(int frequency, Uint16 format, int channels, int chunksize){
    if ( Mix_OpenAudio( frequency, format, channels, chunksize ) == -1 )
        REMOVE std::cout << "Mixer: Failed to initialize audio.\n";
    this->currentFrequency = frequency;
    this->currentFormat = format;
}

void soundManager::terminate(){
    int i,
        calls = Mix_QuerySpec( NULL, NULL, NULL );
    if ( calls == 0 )
        REMOVE std::cout << "Mixer: Error while attempting to terminate AudioSys.\n";
    for ( i = calls; i > 0; i-- )  Mix_CloseAudio();
}

int soundManager::getFormat(int *calls, int *frequency, Uint16 *format, int *channels){
    int nCalls = Mix_QuerySpec( frequency, format, channels );
    if ( nCalls == 0 ){
        REMOVE std::cout << "Mixer: Error while getting audio format.\n";
        return -1;
    }
    if ( calls != NULL )    *calls = nCalls;
    return nCalls;
}

//CANAS INICIO
void soundManager::allocateChannels(int numchans){    Mix_AllocateChannels(numchans);     }

int soundManager::getChannelNum(){ return Mix_AllocateChannels(-1); }

bool soundManager::isPlaying(int channel){ return Mix_Playing(channel); }
int soundManager::getPlayingCount(){ return Mix_Playing(-1); }

int soundManager::getVol(int channel){ return Mix_Volume(channel, -1); }

int soundManager::reserveChannels(int num){ return Mix_ReserveChannels(num); }

void soundManager::play(Mix_Chunk *chunk){
    if( Mix_PlayChannel(-1, chunk, 0) == -1 )
        REMOVE std::cout << "Mixer: Error while playing chunk.\n";
}

void soundManager::play(Mix_Chunk *chunk, int channel){
    if( Mix_PlayChannel(channel, chunk, 0) == -1 )
        REMOVE std::cout << "Mixer: Error while playing at channel " << channel << ".\n";
}

void soundManager::play(Mix_Chunk *chunk, int channel, int nTimes){
    if( Mix_PlayChannel(channel, chunk, nTimes) == -1)
        REMOVE std::cout << "Mixer: Error while playing at channel " << channel << ".\n";
}

void soundManager::loop(Mix_Chunk *chunk){
    if( Mix_PlayChannel(-1, chunk, -1) == -1)
        REMOVE std::cout << "Mixer: Error while playing chunk.\n";
}

void soundManager::loop(Mix_Chunk *chunk, int nTimes){
    if( Mix_PlayChannel(-1, chunk, nTimes) == -1)
        REMOVE std::cout << "Mixer: Error while playing chunk.\n";
}

void soundManager::pause(int channel){ Mix_Pause(channel); }
void soundManager::pauseAllChannel(){ Mix_Pause(-1); }

void soundManager::resume(int channel){ Mix_Resume(channel); }
void soundManager::resumeAllChannel(){ Mix_Resume(-1); }

void soundManager::stop(int channel){ Mix_HaltChannel(channel); }
void soundManager::stopAllChannel(){ Mix_HaltChannel(-1); }
void soundManager::stopChannelAfter(int channel, int milisec){ Mix_ExpireChannel(channel, milisec); }

void soundManager::fadeOut(int channel, int milisec){ Mix_FadeOutChannel(channel, milisec); }
void soundManager::fadeOutAllChannel(int milisec){ Mix_FadeOutChannel(-1, milisec); }

void soundManager::setVol(int channel, int vol){ Mix_Volume(channel, vol); }
void soundManager::setAllChannelVol(int vol){ Mix_Volume( -1, vol); }

void soundManager::setPos(int channel, Sint16 angle, Uint8 distance){
    if ( Mix_SetPosition( channel, angle, distance ) == 0 )
        REMOVE std::cout << "Mixer: Error while setting channel " << channel << " position.\n";
}

void soundManager::setDefaultPos(int channel){ this->setPos(channel, 0, 0); }

void soundManager::setPanning(int channel, Uint8 pos){
    if ( pos > 254 )   pos = 254;
    if ( Mix_SetPanning( channel, 254 - pos, pos ) == 0 )
        REMOVE std::cout << "Mixer: Error while setting panning for channel " << channel << " .\n";
}

void soundManager::setDefaultPanning(int channel){
    if ( Mix_SetPanning( channel, 255, 255 ) == 0 )
        REMOVE std::cout << "Mixer: Error while setting panning for channel " << channel << " to default.\n";
}

void soundManager::setReverseStereo(int channel, bool activated){
    if ( Mix_SetReverseStereo(channel, (int)activated) == 0 )
        REMOVE std::cout << "Mixer: Error while adjusting reverse stereo on channel " << channel << " .\n";
}
//CANAIS FIM

//CHUNK INICIO
void soundManager::load(Mix_Chunk *chunk, const char *filename){
    chunk = Mix_LoadWAV(filename);
    REMOVE if ( chunk == NULL )    std::cout << "Error loading chunk.\n";
}

void soundManager::free(Mix_Chunk *chunk){
    Mix_FreeChunk(chunk);
    chunk = NULL;
}

int soundManager::getVol(Mix_Chunk *chunk){ return Mix_VolumeChunk(chunk, -1); }

void soundManager::setVol(Mix_Chunk *chunk, int vol){ Mix_VolumeChunk(chunk, vol); }
//CHUNK FIM

//MÚSICAS INICIO
bool soundManager::isPlaying(Mix_Music *music){
    if ( Mix_PlayingMusic() && !Mix_PausedMusic() ) return true;
    return false;
}

void soundManager::load(Mix_Music *pointer, const char *filename){
    pointer = Mix_LoadMUS(filename);
    REMOVE if ( pointer == NULL )  std::cout << "Mixer: Error loading music.\n";
}

void soundManager::free(Mix_Music *pointer){ Mix_FreeMusic(pointer); }

void soundManager::play(Mix_Music *music){ if ( Mix_PlayMusic(music, 1) == -1 )   REMOVE std::cout << "Mixer: Error while playing music.\n"; }

void soundManager::loop(Mix_Music *music, int nTimes){
    if( Mix_PlayMusic(music, nTimes) == -1 )  REMOVE std::cout << "Mixer: Error while playing music " << nTimes << " times\n";
}

void soundManager::loop(Mix_Music *music){ if ( Mix_PlayMusic(music, -1) == -1 )   REMOVE std::cout << "Mixer: Error while looping music.\n"; }

void soundManager::pause(){ Mix_PauseMusic(); }

void soundManager::resume(){ Mix_ResumeMusic(); }

void soundManager::stop(){ Mix_HaltMusic(); }

void soundManager::fadeIn(Mix_Music *music, int nTimes, int milisec){
    if ( Mix_FadeInMusic(music, nTimes, milisec) == -1 )    REMOVE std::cout << "Mixer: Error while fading in music.\n";
}

void soundManager::fadeInLoop(Mix_Music *music, int milisec){ this->fadeIn(music, -1, milisec); }

void soundManager::fadeOut(int milisec){
    if( Mix_FadeOutMusic(milisec) == 0 )    REMOVE std::cout << "Mixer: Error while fading out music.\n";
}

void soundManager::setVol(int vol){ Mix_VolumeMusic(vol); }

int soundManager::getVol(){ return Mix_VolumeMusic(-1); }
//MÚSICAS FIM

int soundManager::getAngle(int xC, int yC, int x2, int y2){
    double rad;
    int angle;
    if ( x2 > xC ){
        rad = atan( (double)RELDIST(y2, yC)/RELDIST(x2, xC) );
        if ( y2 > yC )  angle = 90 + degrees(rad);
        else    angle = 90 - degrees(rad);
    }
    else {
        if( y2 == yC )  rad = 0;
        else    rad = atan( (double)RELDIST(x2, xC)/RELDIST(y2, yC) );
        if ( y2 > yC )  angle = 180 + degrees(rad);
        else    angle = 360 - degrees(rad);
    }
    REMOVE std::cout << "Calculated angle: " << angle << " degrees.\n";
    return angle;
}

int soundManager::getDistance(int xL, int yL, int x2, int y2){
    const SDL_VideoInfo *info = SDL_GetVideoInfo();
    double maxAudibleDist = DISTANCE(info->current_w/2, info->current_h/2, info->current_h, info->current_w);
    int distance = (int)(127.0 * DISTANCE(xL, yL, x2, y2)/maxAudibleDist);

    if ( distance < 1 )    distance = 1;

    REMOVE std::cout << "Calculated distance: " << distance << " distance.\n";

    return distance;
}
