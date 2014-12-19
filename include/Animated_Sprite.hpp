#ifndef ANIMATED_SPRITE_H
#define ANIMATED_SPRITE_H

#include "FileHandler.hpp"

class Animated_Sprite
{
    public:
        Animated_Sprite(std::string filename, int verticalClips = 1, int horizontalClips = 1, int initialIndex = 0);
        virtual ~Animated_Sprite();

        void animate(std::vector<int> clips, int period, int cicles);
        void translate(int x, int y, int period = 1, int cicles = 1);

        void set_position(int x, int y);
        void draw(SDL_Surface *screen);

    protected:
    private:
        struct timedClip {
            int frameTime; // tempo no qual o clip é ativado
            int clipIndex; // índice do clip ativado no frameTime
        };
        //Atributos fixos - propriedades
        int x;
        int y;
        SDL_Surface *spritesheet;
        std::vector<SDL_Rect> spriteclip;
        int clipsVertical;
        int clipsHorizontal;

        int curClipIndex; //índice do clip do frame atual da animação
        int timer;

        //Controladores da animação
        bool animating;
        int animationFrame; //contador de frames da animação
        int animationPeriod; //número de frames de um ciclo de animação
        int remainingAnimationCicles; //número remanescente de ciclos de animação a serem percorridos
        std::vector<timedClip> animationClips; //armazena os clips e seus respectivos tempos de um ciclo de animação
        void update_animation(); //atualiza as variáveis da animação

        //Controladores de translação:
        bool translating;
        int translationFrame;
        int translationPeriod;
        int remainingTranslationCicles;
        SDL_Rect targetPos;
        void update_translation();

        SDL_Rect clip(int index);

};

#endif // ANIMATED_SPRITE_H
