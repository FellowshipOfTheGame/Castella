#include "Animated_Sprite.hpp"
#include <iostream>

Animated_Sprite::Animated_Sprite(std::string filename, int verticalClips, int horizontalClips, int initialIndex)
{
    //Carrega o arquivo de imagem
    spritesheet = FileHandler::load_img(filename);
    //Inicializa o número de clips horizontais e verticais
    clipsHorizontal = horizontalClips;
    clipsVertical = verticalClips;
    //Carrega os clips da spritesheet na memória
    for (int i=0; i < verticalClips*horizontalClips; i++){
        spriteclip.push_back(clip(i));
    }
    //Inicia a imagem no clip correto
    curClipIndex = initialIndex;
    //Inicializa em false os indicadores de animação e tranalação
    animating = false;
    translating = false;
}

Animated_Sprite::~Animated_Sprite()
{
    //dtor
}

SDL_Rect Animated_Sprite::clip(int index){
    SDL_Rect clip;
    clip.w = spritesheet->w/clipsHorizontal;
    clip.h = spritesheet->h/clipsVertical;
    clip.x = index%clipsHorizontal * clip.w;
    clip.y = index/clipsHorizontal * clip.h;
    return clip;
}

void Animated_Sprite::animate(std::vector<int> clips, int period, int cicles){
    animating = true;
    if (period == 0) period = 1; //corrige período para evitar divisão por 0
    //Guarda na memória o período e número total de ciclos de animação
    animationPeriod = period;
    remainingAnimationCicles = cicles;
    //Calcula o tempo para cada frame
    float clipTime = period/clips.size();
    //Insere na lista de animação os clips com seus respectivos tempos
    for (unsigned int i=0; i<clips.size(); i++){
        timedClip tClip;
        tClip.frameTime = i*clipTime;
        tClip.clipIndex = clips.at(i);
        animationClips.push_back(tClip);
    }
    //Reseta os frames da animação
    animationFrame = 0;
}

void Animated_Sprite::update_animation(){
    //Verifica se um período foi cumprido; reseta o contador e atualiza o número restante de ciclos
    std::cout << animationFrame <<"/"<<animationPeriod << std::endl;
    if (animationFrame >= animationPeriod){
        animationFrame %= animationPeriod;
        remainingAnimationCicles--;
        std::cout << "CICLE-- ";
    }
    //Verifica se acabaram os ciclos de animação
    if (remainingAnimationCicles == 0){
        return;
    }
    //Determina o índice do clip da animação
    for (auto c : animationClips){
        if (c.frameTime <= animationFrame){
            curClipIndex = c.clipIndex;
        }
    }
    //Atualiza o frame da animação
    animationFrame++;
}

void Animated_Sprite::translate(int x, int y, int period, int cicles){
    translating = true;
    targetPos.x = x;
    targetPos.y = y;
    if (period == 0) period = 1; //corrige período para evitar divisão por 0
    translationPeriod = period;
    remainingTranslationCicles = cicles;
    translationFrame = 0;
}

void Animated_Sprite::update_translation(){
    //Verifica se um período foi cumprido; reseta o contador e atualiza o número restante de ciclos
    if (translationFrame >= translationPeriod){
        translationFrame %= translationPeriod;
        remainingTranslationCicles--;
    }
    //Verifica se acabaram os ciclos de translação
    if (remainingTranslationCicles == 0){
        return;
    }
    int remainingFrames = translationPeriod - translationFrame;
    int difX = (targetPos.x - this->x) / remainingFrames;
    int difY = (targetPos.y - this->y) / remainingFrames;
    this->x += difX;
    this->y += difY;
    //Atualiza o frame da translação
    translationFrame++;
}

void Animated_Sprite::set_position(int x, int y){
    this->x = x;
    this->y = y;
}

void Animated_Sprite::draw(SDL_Surface *screen){
    if (animating) update_animation();
    if (translating) update_translation();
    apply_surface(x-spriteclip[curClipIndex].w/2, y, spritesheet, screen, &spriteclip[curClipIndex]);
}
