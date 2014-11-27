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
		: ContentTable<check_item<Content> > (window, width, height, x, y,
				foreground, background), checked_foreground (checked_foreground)
		{
	for (auto cont : l) {
		addContent (cont);
	}
}


template <class Content>
Checklist<Content>::~Checklist () {
	ContentTable<check_item<Content> >::destroyContent ();
}


template <class Content>
void Checklist<Content>::addContent (Content *cont) {
	ContentTable<check_item<Content> >::addContent (new check_item<Content> (cont));
}


template <class Content>
bool Checklist<Content>::mouse_try_click (int x, int y) {
	bool aux = ContentTable<check_item<Content> >::mouse_try_click (x, y);

	if (this->ultimo_clicado) {
		this->ultimo_clicado->flip ();
		redraw ();
	}

	return aux;
}


template <class Content>
vector<Content *> Checklist<Content>::getChecked () {
	// vector de retorno
	vector<Content *> aux;
	// se tá marcado, bota pra retornar
	for (auto & item : this->data) {
		if (item->second ()) {
			aux.push_back (item->first ());
		}
	}

	return aux;
}


template <class Content>
void Checklist<Content>::redraw () {
	ContentTable<check_item<Content> >::redraw ();

	// min entre data.size() e maxPagina()
	const unsigned int parada = this->data.size () - this->deslocamento () < this->maxPagina () ?
			this->data.size () - this->deslocamento () : this->maxPagina ();

	for (unsigned int i = 0; i < parada; i++) {
		check_item<Content> *cont = this->data[this->deslocamento () + i];
		if (cont->second ()) {
			ostringstream str;
			str << *cont;
			write_text (0, i * DEFAULT_FONT_SIZE, this->image, str.str (), checked_foreground);
		}
	}
}
