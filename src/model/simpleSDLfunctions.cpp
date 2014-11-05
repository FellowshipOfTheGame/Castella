#include <simpleSDLfunctions.h>

//################################## FUNÇÔES DE ATALHO ##################################OO
//Funções para facilitar a aplicação de outras funções, otimizando suas utilizações,
//em termos de organização e linhas de código

//---------------------------------- CARREGAR IMAGEM ------------------------------------//
//Função de carregamento de imagem
SDL_Surface *load_image (std::string nome_do_arquivo)
{
    //Ponteiro de armazenamento de imagem
    SDL_Surface *imagemAux = NULL;
    SDL_Surface *imagem = NULL;

    //Carregar imagem
    imagemAux = IMG_Load (nome_do_arquivo.c_str ());
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

//--------------------------------- CRIAR SUPERFICIE --------------------------/
// Função que cria uma superfície vazia
SDL_Surface *create_surface (int width, int height) {
	return SDL_CreateRGBSurface (SDL_SWSURFACE, width, height, 32,
			RMASK, GMASK, BMASK, AMASK);
}
//

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

// Preenche o fundo de uma superfície: padrão = preto
void fill_surface (SDL_Surface *target, SDL_Rect *dstrect, SDL_Color cor) {
	// mapeia 'cor' em Uint32, pra ser usado no fill
	Uint32 my_uint32 = SDL_MapRGB (target->format, cor.r, cor.g, cor.b);
	SDL_FillRect (target, dstrect, my_uint32);
}
//---------------------------------------------------------------------------------------//

//--------------------------------- ESCREVER TEXTO --------------------------------//
//Escreve um texto na tela, na posição desejada

void write_text(int x, int y, SDL_Surface *destino, std::string texto, unsigned char R, unsigned char G, unsigned char B)
{
	SDL_Color cor = {R, G, B};
	write_text (x, y, destino, texto, cor);
}


void write_text(int x, int y, SDL_Surface *destino, std::string texto, SDL_Color cor)
{
	TTF_Font *fonte = TTF_OpenFont ("DejaVuSansMono.ttf", 20);
	SDL_Surface *mensagem = TTF_RenderText_Solid (fonte, texto.c_str (), cor);

	apply_surface (x, y, mensagem, destino);

	SDL_FreeSurface (mensagem);
	TTF_CloseFont (fonte);
}
//---------------------------------------------------------------------------------------//
