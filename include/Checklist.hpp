/** @file Checklist.hpp
 * header do view/Checklist.cpp
 */

#ifndef CHECKLIST_HPP
#define CHECKLIST_HPP

#include <vector>

#include "ContentTable.hpp"

template <class Content>
class Checklist : public ContentTable<Content> {
private:
	/// Número de valores marcados
	int num_checked {0};
	/// Valores marcados
	vector<bool> checked;
	/// Cor do marcado
	SDL_Color checked_foreground;

public:
	/** Ctor, agora com o checked_foreground: padrão = vermelho */
	Checklist (SDL_Rect *window, int width, int height, int x, int y,
			SDL_Color foreground = {0, 0, 0},
			SDL_Color checked_foreground = {255, 0, 0},
			SDL_Color background = {255, 255, 255});
	/** Ctor, agora com o checked_foreground: padrão = vermelho */
	Checklist (SDL_Rect *window, int width, int height, int x, int y,
			initializer_list<Content *> l,
			SDL_Color foreground = {0, 0, 0},
			SDL_Color checked_foreground = {255, 0, 0},
			SDL_Color background = {255, 255, 255});

	/** @brief Clicou lá
	 *
	 * Se clicar na Checklist, salva o último clicado e marca ou desmarca-o.
	 * Último clicado pode ser acessado depois através da função getContent (),
	 * e todos os marcados através da função getChecked ().
	 */
	bool mouse_try_click (int x, int y);

	/** @brief Adiciona um Content no vector data
	 *
	 * Além do conteúdo em data, esse método adiciona um _false_ em
	 * checked, mostrando que conteúdo ainda não está marcado.
	 *
	 * @note A superfície image é atualizada a cada inserção
	 *
	 * @param[in] cont Conteúdo a ser inserido
	 */
	void addContent (Content *cont);

	/** @brief Redesenha todo o Checklist, mostrando os conteúdos marcados
	 */
	void redraw ();

	/** @brief Pega os conteúdos marcados
	 *
	 * Verifica quais conteúdos estão marcados, e os retorna
	 * em um vector.
	 *
	 * @return Vector com os conteúdos marcados
	 */
	vector<Content *> getChecked ();
};

/* Mesma história do ContentTable, precisa pros template rolar */
#include "Checklist.cpp"

#endif
