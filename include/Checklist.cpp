// Complemento pro Checklist.hpp

template <class Content>
Checklist<Content>::Checklist (SDL_Rect *window, int width, int height,
		int x, int y, SDL_Color foreground, SDL_Color checked_foreground,
		SDL_Color background)
		: Checklist (window, width, height, x, y, {},
				foreground, checked_foreground, background)
		{
}


template <class Content>
Checklist<Content>::Checklist (SDL_Rect *window, int width, int height,
		int x, int y, initializer_list<Content *> l,
		SDL_Color foreground, SDL_Color checked_foreground,
		SDL_Color background)
		: ContentTable<Content> (window, width, height, x, y, l,
				foreground, background),
		checked (this->data.size (), false), checked_foreground (checked_foreground)
		{
}


template <class Content>
void Checklist<Content>::addContent (Content *cont) {
	ContentTable<Content>::addContent (cont);
	checked.push_back (false);
}


template <class Content>
bool Checklist<Content>::mouse_try_click (int x, int y) {
	bool aux = Widget::mouse_try_click (x, y);
	// tá dentro da zona clicável
	if (aux) {
		// verifica a linha clicada
		unsigned int clicado = (y - this->box.y) / DEFAULT_FONT_SIZE;

		// se clicou em algo válido, salva como o último clicado e toggla seu
		// estado;  senão, nullptr neles!
		if (clicado < this->data.size ()) {
			this->ultimo_clicado = this->data[clicado];
			checked[clicado] = !checked[clicado];
			redraw ();
		}
		else {
			this->ultimo_clicado = nullptr;
		}
	}
	else {
		this->ultimo_clicado = nullptr;
	}

	return aux;
}


template <class Content>
vector<Content *> Checklist<Content>::getChecked () {
	// vector de retorno
	vector<Content *> aux;
	// se tá marcado, bota pra retornar
	for (unsigned int i = 0; i < this->data.size (); i++) {
		if (checked[i]) {
			aux.push_back (this->data[i]);
		}
	}

	return aux;
}


template <class Content>
void Checklist<Content>::redraw () {
	fill_surface (this->image, this->background);

	for (unsigned int i = 0; i < this->data.size (); i++) {
		// Escolhe a cor, depende se tá marcado ou não
		SDL_Color *cor = checked[i] ? &checked_foreground : &this->foreground;
		/* Escreve o content na SDL_Surface
		 *
		 * pra isso, usamos a definição de transformar objeto em string
		 * usando ostream (que nem se faz pra poder escrever o trem no cout)
		 */
		ostringstream str;
		str << *(this->data[i]);
		write_text (0, i * DEFAULT_FONT_SIZE, this->image, str.str (), *cor);
		// linha separadora entre cada conteúdo
		hlineRGBA (this->image, 0, this->box.w, (i + 1) * DEFAULT_FONT_SIZE,
				this->foreground.r, this->foreground.g, this->foreground.b, 0xff);
	}
}
