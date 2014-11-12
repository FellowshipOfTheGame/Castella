// Complemento pro ContentTable.hpp

template <class Content>
ContentTable<Content>::ContentTable (SDL_Rect *window, int width, int height,
		int x, int y, SDL_Color foreground, SDL_Color background)
		: ContentTable (window, width, height, x, y, {})  {
}


template <class Content>
ContentTable<Content>::ContentTable (SDL_Rect *window, int width, int height,
		int x, int y, initializer_list<Content> l,
		SDL_Color foreground, SDL_Color background)
		: Widget (window, width, height, x, y) {
	fill_surface (image, background);

	for (Content cont : l) {
		addContent (cont);
	}
}


template <class Content>
bool ContentTable<Content>::mouse_try_click (int x, int y) {
	bool aux = Widget::mouse_try_click (x, y);
	// tá dentro da zona clicável
	if (aux) {
		// verifica a linha clicada
		unsigned int clicado = (y - box.y) / DEFAULT_FONT_SIZE;

		// se clicou em algo válido, salva como o último clicado;
		// senão, nullptr neles!
		ultimo_clicado = clicado < data.size () ? &data[clicado] : nullptr;
	}
	else {
		ultimo_clicado = nullptr;
	}

	return aux;
}


template <class Content>
Content * ContentTable<Content>::getContent () {
	return ultimo_clicado;
}



template <class Content>
void ContentTable<Content>::addContent (Content cont) {
	// Adiciona cont no vector de conteúdos
	data.push_back (cont);

	/* Escreve o novo content na SDL_Surface
	 *
	 * pra isso, usamos a definição de transformar objeto em string
	 * usando ostream (que nem se faz pra poder escrever o trem no cout)
	 */
	ostringstream str;
	str << cont;
	write_text (0, (data.size () - 1) * DEFAULT_FONT_SIZE, image, str.str ());
	// linha separadora entre cada conteúdo
	lineColor (image, 0, data.size () * DEFAULT_FONT_SIZE,
			box.w, data.size () * DEFAULT_FONT_SIZE, 0x000000ff);
}
