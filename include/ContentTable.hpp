/** @file ContentTable.hpp
 */

#ifndef CONTENTTABLE_HPP
#define CONTENTTABLE_HPP

#include <vector>
#include <sstream>
#include <iostream>

#include "Widget.hpp"

/** @brief Widget que é uma tabela
 */
template <class Content>
class ContentTable : public Widget {
protected:
	/// Vector contendo ponteiros para os conteúdos, que pode ser qualquer coisa
	vector<Content *> data;
	/// Último conteúdo clicado: nullptr se clicou fora
	Content *ultimo_clicado {nullptr};
	/// Em qual página está a ContentTable
	unsigned int pagina {0};

	SDL_Color foreground;	///< Cor do escrito
	SDL_Color background;	///< Cor do fundo

	/// Altura da Setinha de página próxima/anterior
	static const int arrowHeight = 26;

	/// Quantos conteúdos cabem numa página
	unsigned int maxPagina ();
	/// Qual o deslocamento atual, em relação à página atual
	unsigned int deslocamento ();
	/// A altura das setinhas, Y inicial
	unsigned int setinhas_Y ();
	/// Quantas páginas há nessa Checklist
	unsigned int numPags ();

public:
	/** Ctor, fundo padrão = branco */
	ContentTable (SDL_Rect *window, int width, int height, int x, int y,
			SDL_Color foreground = {0, 0, 0},
			SDL_Color background = {255, 255, 255});
	/** Ctor com inicialização do vector data */
	ContentTable (SDL_Rect *window, int width, int height, int x, int y,
			initializer_list<Content *> l,
			SDL_Color foreground = {0, 0, 0},
			SDL_Color background = {255, 255, 255});

	/** @brief Clica lá
	 *
	 * Se clicar na ContentTable, salva o último clicado, que pode ser
	 * acessado depois através da função getContent ()
	 */
	virtual bool mouse_try_click (int x, int y);

	/** @brief Pega um conteúdo na tabela, retornando um objeto 
	 * do tipo Content, em relação a onde foi clicado na tela.
	 *
	 * @return Ponteiro para o último conteúdo clicado
	 * @return nullptr se tiver clicado fora dos conteúdos
	 */
	Content * getContent ();

	/** @brief Adiciona um Content no vector data
	 *
	 * @note A superfície image é atualizada a cada inserção
	 *
	 * @param[in] cont Conteúdo a ser inserido
	 */
	void addContent (Content *cont);

	/** @brief Redesenha todo o ContentTable
	 */
	virtual void redraw ();

	/** @brief Destrói os conteúdos
	 *
	 * Destrutor do ContentTable não destrói os conteúdos
	 * apontados no vector data, pois talvez não seja isso
	 * que se quer
	 */
	void destroyContent ();
};

/* A implementação é incluída aqui no .hpp inline pros templates funcionarem
 * para qualquer classe que quiser! =]
 */
#include "ContentTable.cpp"

#endif
