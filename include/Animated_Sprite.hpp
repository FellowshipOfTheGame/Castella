#ifndef ANIMATED_SPRITE_H
#define ANIMATED_SPRITE_H

#include "FileHandler.hpp"

class Animated_Sprite
{
    public:
        Animated_Sprite(std::string filename, int horizontalClips = 1, int verticalClips = 1, int initialIndex = 0);
        virtual ~Animated_Sprite();
        //Métodos para iniciar uma animação ou translação
        void animate(std::vector<int> clips, int period, int cicles);
        void translate(int x, int y, int period = 1, int cicles = 1);
        //Determina a posição da imagem
        void set_position(int x, int y);
        //Desenha
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
        SDL_Surface *spritesheet; //armazena a imagem inteira com os clips
        std::vector<SDL_Rect> spriteclip; //armazena os clips da spritesheet na memória em vez de processar o método clip() - TODO: avaliar se esse tradeoff é mesmo interessante
        int clipsHorizontal; //número de clips na horizontal
        int clipsVertical; //número de clips na vertical

        int curClipIndex; //índice do clip do frame atual da animação

        //Controladores da animação
        bool animating; //indica se há uma animação em curso
        int animationFrame; //contador de frames da animação
        int animationPeriod; //número de frames de um ciclo de animação
        int remainingAnimationCicles; //número remanescente de ciclos de animação a serem percorridos
        std::vector<timedClip> animationClips; // armazena os clips e seus respectivos tempos de um ciclo de animação
        void update_animation(); //atualiza as variáveis da animação

        //Controladores de translação:
        bool translating; //indica se h uma translação em curso
        int translationFrame; //contador de frames da translação
        int translationPeriod; //número de frames de um ciclo de translação
        int remainingTranslationCicles; //número remanescente de ciclos de translação - TODO: implementar translações múltiplas
        SDL_Rect targetPos; //posição alvo da translação - TODO: passar um vetor de posições alvo para translações múltiplas
        void update_translation(); //atualiza as variáveis que controlam a translação

        SDL_Rect clip(int index); //retorna o pedaço da spritesheet relativo ao índice

};

#endif // ANIMATED_SPRITE_H
