#include "ContentTable.hpp"

template <class Content>
ContentTable<Content>::ContentTable (SDL_Rect *window, int width, int height, int x, int y, SDL_Color background)
		: Widget (window, width, height, x, y) {
}
