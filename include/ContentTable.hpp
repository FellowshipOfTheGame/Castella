/** @file ContentTable.hpp
 */

#ifndef CONTENTTABLE_HPP
#define CONTENTTABLE_HPP

#include <vector>
#include <sstream>
#include "Widget.hpp"

/** @brief Widget que é uma tabela
 */
template <class Content>
class ContentTable : public Widget {
private:
	/// Vector contendo ponteiros para os conteúdos, que pode ser qualquer coisa
	vector<Content *> data;
	Content *ultimo_clicado {nullptr};

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
	bool mouse_try_click (int x, int y);

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

	/** @brief Destrói os conteúdos
	 *
	 * Destrutor do ContentTable não destrói os conteúdos
	 * apontados no vector data, pois talvez não seja isso
	 * que se quer
	 */
	void destroyContent ();

protected:
};

/* A implementação é incluída aqui no .hpp inline pros templates funcionarem
 * para qualquer classe que quiser! =]
 */
#include "ContentTable.cpp"

#endif
