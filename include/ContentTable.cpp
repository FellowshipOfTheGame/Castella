// Complemento pro ContentTable.hpp

template <class Content>
ContentTable<Content>::ContentTable (SDL_Rect *window, int width, int height,
		int x, int y, SDL_Color foreground, SDL_Color background)
		: ContentTable (window, width, height, x, y, {}, foreground, background)
		{
}


template <class Content>
ContentTable<Content>::ContentTable (SDL_Rect *window, int width, int height,
		int x, int y, initializer_list<Content *> l,
		SDL_Color foreground, SDL_Color background)
		: Widget (window, width, height, x, y), data (l),
		foreground (foreground), background (background) {
	redraw ();
}


template <class Content>
unsigned int ContentTable<Content>::maxPagina () {
	return (box.h - arrowHeight) / DEFAULT_FONT_SIZE;
}


template <class Content>
bool ContentTable<Content>::mouse_try_click (int x, int y) {
	bool aux = Widget::mouse_try_click (x, y);
	// tá dentro da zona clicável
	if (aux) {
		// na altura da setinha
		if (y - box.y < box.h - arrowHeight) {
			// seta pra esquerda, e dá pra voltar página
			if (x - box.x < box.w/2 && pagina > 0) {
				pagina--;
			}
			// pra direita
			else if (pagina < maxPagina ()) {
				pagina++;
			}

			redraw ();
		}
		// ou não, então conteúdo
		else {
			// verifica a linha clicada
			unsigned int clicado = (y - box.y) / DEFAULT_FONT_SIZE;

			// se clicou em algo válido, salva como o último clicado;
			// senão, nullptr neles!
			ultimo_clicado = (clicado < data.size ()) ?
					data[maxPagina () * pagina + clicado] : nullptr;
		}
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
void ContentTable<Content>::addContent (Content *cont) {
	// Adiciona cont no vector de conteúdos
	data.push_back (cont);

	redraw ();
}


template <class Content>
void ContentTable<Content>::redraw () {
	fill_surface (image, background);

	unsigned int parada = data.size () < maxPagina () ?
			data.size () : maxPagina ();

	for (unsigned int i = 0; i < parada; i++) {
		/* Escreve o content na SDL_Surface
		 *
		 * pra isso, usamos a definição de transformar objeto em string
		 * usando ostream (que nem se faz pra poder escrever o trem no cout)
		 */
		ostringstream str;
		str << *data[maxPagina () * pagina + i];
		write_text (0, i * DEFAULT_FONT_SIZE, image, str.str (), foreground);
		// linha separadora entre cada conteúdo
		hlineRGBA (image, 0, box.w, (i + 1) * DEFAULT_FONT_SIZE,
				foreground.r, foreground.g, foreground.b, 0xff);
	}
}
