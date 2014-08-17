/*
*   O gerenciador de som é responsável por inicializar o sistema de som, alocar canais, obter o formato de som, alocar canais
* e aplicar efeitos sonoros, também calcula distância entre 2 pontos e o ângulo no sentido horário, partindo de "12 horas" para uso na função
* setChannelPostion.
*
*
*
*/

#ifndef _SOUNDMANAGER_HPP_
#define _SOUNDMANAGER_HPP_

#include <cmath>
#include <iostream>
#include <SDL.h>
#include <SDL_mixer.h>

class soundManager{

    private:
        int currentFrequency; //Frequência de saída
        Uint16 currentFormat;  //Formato de som

/* Formatos de som suportados
AUDIO_U8
    Unsigned 8-bit samples
AUDIO_S8
    Signed 8-bit samples
AUDIO_U16LSB
    Unsigned 16-bit samples, in little-endian byte order
AUDIO_S16LSB
    Signed 16-bit samples, in little-endian byte order
AUDIO_U16MSB
    Unsigned 16-bit samples, in big-endian byte order
AUDIO_S16MSB
    Signed 16-bit samples, in big-endian byte order
AUDIO_U16
    same as AUDIO_U16LSB (for backwards compatability probably)
AUDIO_S16
    same as AUDIO_S16LSB (for backwards compatability probably)
AUDIO_U16SYS
    Unsigned 16-bit samples, in system byte order
AUDIO_S16SYS (Padrão, equivale a MIX_DEFAULT_FORMAT)
    Signed 16-bit samples, in system byte order
*/

    public:
        soundManager();
        soundManager(int frequency, Uint16 format, int superchannels, int chunksize);
        ~soundManager();

        void init(int frequency, Uint16 format, int superchannels, int chunksize);
        //Inicializa o sistema de som do SDL_Mixer, "superchannels": 1 é mono e 2 é stereo, chunksize: tamanho ocupado pelos chunks carregados na memória.
        void terminate(); //Finaliza o sistema de som

        int getFormat(int *calls, int *frequency, Uint16 *format, int *channels); //Fornece o formato de som atual do sistema.

        //CANAIS INICIO
        void allocateChannels(int numchans); //Alocar canais de som, neste caso não é mono ou stereo, são os canais que tocam os chunks.

        int getChannelNum(); //Fornece a quantidade de canais

        bool isPlaying(int channel);
        int getPlayingCount();

        int reserveChannels(int num); //Impedir que canais toquem sem ordens diretas (As AllChannel não terão efeito sobre eles)

        void play(Mix_Chunk *chunk);
        void play(Mix_Chunk *chunk, int channel);
        void play(Mix_Chunk *chunk, int channel, int nTimes);

        void loop(Mix_Chunk *chunk);
        void loop(Mix_Chunk *chunk, int nTimes);


        void pause(int channel); //Para temporariamente o som, através de resumeChannel() ela irá continuar a tocar de onde parou
        void pauseAllChannel();

        void resume(int channel);
        void resumeAllChannel();

        void stop(int channel); //Para o som sem retorno e chama Mix_ChannelFinished se necessário.
        void stopAllChannel();
        void stopChannelAfter(int channel, int milisec); //Para o canal após milisec milisegundos

        void fadeOut(int channel, int milisec); //Gradualmente remove o som no tempo milisec
        void fadeOutAllChannel(int milisec);

        int getVol(int channel);
        void setVol(int channel, int vol);
        void setAllChannelVol(int vol);

        void setPos(int channel, Sint16 angle, Uint8 distance); //Define a posição do som em relação ao ouvinte
        void setDefaultPos(int channel); //Desativa o efeito de ṕosição.

        void setPanning(int channel, Uint8 pos); //Define o "panning" do canal, quão intenso o som irá soar em cada canal.
        void setDefaultPanning(int channel); //Desativa o efeito de panning.

        void setReverseStereo(int channel, bool activated); //Inverte os "supercanais" Esq <-> Dir ou  Dir<->Esq

        //CANAIS FIM

        //CHUNK INICIO
        void load(Mix_Chunk *chunk, const char *filename);
        void free(Mix_Chunk *chunk);

        int getVol(Mix_Chunk *chunk);
        void setVol(Mix_Chunk *chunk, int vol);
        //CHUNK FIM

        //MÚSICA INÍCIO
        bool isPlaying(Mix_Music *music);

        void load(Mix_Music *pointer, const char *filename);
        void free(Mix_Music *pointer);

        void play(Mix_Music *music);
        void loop(Mix_Music *music, int nTimes);
        void loop(Mix_Music *music);

        void pause();

        void resume();

        void stop();

        void fadeIn(Mix_Music *music, int nTimes, int milisec); //Faz um fade de duração milisec
        void fadeInLoop(Mix_Music *music, int milisec);

        void fadeOut(int milisec);

        int getVol();
        void setVol(int vol);
        //MÚSICA FIM

        int getAngle(int x1, int y1, int x2, int y2); //Calcula o ângulo em que o som é produzido, a partir das 12 horas, no sentido horário, lembra um pouco coordenadas polares.
        int getDistance(int xL, int yL, int x2, int y2); //Calcula a distância entre o ouvinte (listener) e o local em que ocorreu o som, seria o raio da coordenada polar.

};

#endif
