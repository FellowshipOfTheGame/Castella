#include <simpleSDLfunctions.h>

//################################## FUNÇÔES DE ATALHO ##################################OO
//Funções para facilitar a aplicação de outras funções, otimizando suas utilizações,
//em termos de organização e linhas de código

//---------------------------------- CARREGAR IMAGEM ------------------------------------//
//Função de carregamento de imagem
SDL_Surface *load_image(const char *nome_do_arquivo)
{
    //Ponteiro de armazenamento de imagem
    SDL_Surface *imagemAux = NULL;
    SDL_Surface *imagem = NULL;

    //Carregar imagem
    imagemAux = IMG_Load(nome_do_arquivo);
    //Se a imagem tiver sido carregada corretamente
    if (imagemAux != NULL)
    {
        //Otimizar a imagem
        imagem = SDL_DisplayFormat(imagemAux);
        SDL_FreeSurface(imagemAux);

        //Definir cor chave
        Uint32 corchave = SDL_MapRGB(imagem->format, 0xFF, 0, 0xFF);

        //Tornar a cor chave transparente
        SDL_SetColorKey(imagem, SDL_SRCCOLORKEY, corchave);
    }

    //Retorna a imagem otimizada
    return imagem;
}
//---------------------------------------------------------------------------------------//

//--------------------------------- APLICAR SUPERFICIE ----------------------------------//
//Aplica uma superfície recebendo também suas coordenadas como parâmetros
void apply_surface(int x, int y, SDL_Surface* fonte, SDL_Surface* destino, SDL_Rect* corte, float empurrar)
{
    //Especifica as coordenadas x e y da superfície
    SDL_Rect coordenada;
    coordenada.x = x;
    coordenada.y = y;

    coordenada.x -= fonte->w*empurrar;

    //Transferir superfície para seu destino
    SDL_BlitSurface(fonte, corte, destino, &coordenada);
}
//---------------------------------------------------------------------------------------//

//--------------------------------- ESCREVER TEXTO --------------------------------------//
//Escreve um texto na tela, na posição desejada
void write_text(int x, int y, SDL_Surface *destino, std::string texto)
{
	SDL_Color cor = {0, 0, 0};
	write_text (x, y, destino, texto, cor);
}


void write_text(int x, int y, SDL_Surface *destino, std::string texto, SDL_Color cor)
{
	TTF_Font *fonte = TTF_OpenFont ("DejaVuSansMono.ttf", 20);
	SDL_Surface *mensagem = TTF_RenderText_Solid (fonte, texto.c_str (), cor);

	apply_surface (x, y, mensagem, destino, NULL, 0);

	SDL_FreeSurface (mensagem);
	TTF_CloseFont (fonte);
}
//---------------------------------------------------------------------------------------//
