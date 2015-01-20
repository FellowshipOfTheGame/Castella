/** @file Checklist.hpp
 * header do view/Checklist.cpp
 */

#ifndef CHECKLIST_HPP
#define CHECKLIST_HPP

#include <vector>
#include <ostream>

#include "ContentTable.hpp"

template <class Content>
class check_item {
	friend ostream& operator<< (ostream& os, const check_item & i) {
		return os << *(i.item.first);
	}
public:
	pair<Content *, bool> item;
	check_item (Content *cont) : item (cont, false) {}
	void flip () {
		item.second = !item.second;
	}
	Content *first () { return item.first; }
	bool second () { return item.second; }
};


/** @brief Checklist: uma ContentTable marcável.
 *
 * Checklist é uma ContentTable onde os conteúdos podem ser marcados,
 * sendo então destacados.
 *
 * Uma Checklist guarda Contents, mas põe na ContentTable um
 * `pair<Content, bool>`, que tem o conteúdo em si, e se ele está ou não
 * marcado.
 */
template <class Content>
class Checklist : public ContentTable<check_item<Content> > {
private:
	/// Número de valores marcados
	int num_checked {0};
	/// Limite. Se 0, ilimitado (padrão)!
	int limit {0};
	/// Cor do marcado
	SDL_Color checked_foreground;
	/// Flipa um conteúdo marcado, fazendo a contagem certa
	void flip (check_item<Content> *target);

public:
	/** Ctor, agora com o checked_foreground: padrão = vermelho */
	Checklist (SDL_Rect *window, int width, int height, int x, int y,
			SDL_Color foreground = PRETO,
			SDL_Color checked_foreground = VERMELHO,
			SDL_Color background = BRANCO);
	/** Ctor, agora com o checked_foreground: padrão = vermelho */
	Checklist (SDL_Rect *window, int width, int height, int x, int y,
			initializer_list<Content *> l,
			SDL_Color foreground = PRETO,
			SDL_Color checked_foreground = VERMELHO,
			SDL_Color background = BRANCO);

	/// Dtor: destrói os pairs dentro da ContentTable
	~Checklist ();

	/// Ajusta o limite
	void setLimit (const int limit);
	/// Pega o limite, vai que precisa
	int getLimit ();

	/** @brief Clicou lá
	 *
	 * Se clicar na Checklist, salva o último clicado e marca ou desmarca-o.
	 * Último clicado pode ser acessado depois através da função getContent (),
	 * e todos os marcados através da função getChecked ().
	 */
	bool mouse_try_click (int x, int y);

	/** @brief Adiciona um Content no vector data
	 *
	 * Além do conteúdo em data, esse método adiciona um check_item 
	 * com _false_, mostrando que conteúdo ainda não está marcado.
	 *
	 * @note A superfície image é atualizada a cada inserção
	 *
	 * @param[in] cont Conteúdo a ser inserido
	 */
	void addContent (Content *cont);

	/** @brief Redesenha todo o Checklist, mostrando os conteúdos marcados
	 *
	 * @note Essa função desenha encima da ContentTable::redraw,
	 * somente reescrevendo os itens marcados.
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
