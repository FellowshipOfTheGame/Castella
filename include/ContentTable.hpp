/** @file ContentTable.hpp
 * header do view/ContentTable.cpp
 */

#ifndef CONTENTTABLE_HPP
#define CONTENTTABLE_HPP

#include <vector>
#include "Widget.hpp"

/** @brief Widget que é uma tabela
 */
template <class Content>
class ContentTable : public Widget {
private:
	/// Vector contendo ponteiros para os conteúdos, que pode ser qualquer coisa
	vector<Content *> data;

public:
	ContentTable (SDL_Rect *window, int width, int height, int x, int y, SDL_Color background = {255, 255, 255});
	/** @brief Pega um conteúdo na tabela, retornando um objeto 
	 * do tipo Content, em relação a onde foi clicado na tela.
	 * 
	 * @warning Essa função não checa se clicou no Widget. Faça-o
	 * usando a função @ref mouse_try_click.
	 *
	 * @return Referência para o conteúdo clicado.
	 */
	Content & getContent (int x, int y);

protected:
};

#endif
