/** @file ContentTable_Checklist_Factory.hpp
 */

#ifndef CNTTBL_CHKLST_FACTORY_HPP
#define CNTTBL_CHKLST_FACTORY_HPP

#include "Checklist.hpp"
#include "LuaWBind.hpp"
// INCLUDES
#include "Actor.hpp"
// END

class ContentTable_Checklist_Factory {
public:
	template<class T>
	static ContentTable<T> * createContentTable (SDL_Rect *window, int width, int height, int x, int y) {
		return new ContentTable<T> (window, width, height, x, y);
	}

	template<class T>
	static Checklist<T> * createChecklist (SDL_Rect *window, int width, int height, int x, int y) {
		return new Checklist<T> (window, width, height, x, y);
	}

	static void registerOnLua (lua_State *L) {
		using namespace luabind;

		module (L) [
			class_<ContentTable<Actor>> ("ContentTable_Actor")
				.def ("new", (ContentTable<Actor> (*) (SDL_Rect *, int, int, int, int)) &ContentTable_Checklist_Factory::createContentTable<Actor>),
			class_<Checklist<Actor>> ("Checklist_Actor")
				.def ("new", (Checklist<Actor> (*) (SDL_Rect *, int, int, int, int)) &ContentTable_Checklist_Factory::createChecklist<Actor>),
			class_<ContentTable<string>> ("ContentTable_string")
				.def ("new", (ContentTable<string> (*) (SDL_Rect *, int, int, int, int)) &ContentTable_Checklist_Factory::createContentTable<string>),
			class_<Checklist<string>> ("Checklist_string"),
			def ("newChecklist_string", (Checklist<string> (*) (SDL_Rect *, int, int, int, int)) &ContentTable_Checklist_Factory::createChecklist<string>)
		];
	}
};

#endif
