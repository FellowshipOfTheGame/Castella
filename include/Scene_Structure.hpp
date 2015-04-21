/** @file Scene_Region.hpp
 * header do model/Scene_Structure.cpp
 * Cena das @ref Structure "estruturas"
 */
#ifndef SCENE_STRUCTURE_HPP
#define SCENE_STRUCTURE_HPP

#include "Scene.hpp"
#include "Structure.hpp"

class Scene_Structure : public Scene {
public:
    Scene_Structure ();
	virtual void update ();
	virtual void redraw ();
	virtual void mouseclick (int x, int y);
	virtual void escape();

protected:

private:
	Structure *current;

};

#endif
