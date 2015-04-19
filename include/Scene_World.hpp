/** @file Scene_World.hpp
 *
 * Header do model/Scene_World.cpp
 */
#ifndef SCENE_WORLD_H
#define SCENE_WORLD_H

#include <iostream>

#include "Scene.hpp"
#include "FileContainer.hpp"
#include "MapTile.hpp"
#include "World.hpp"

class Scene_World : public Scene
{
    public:
        Scene_World();
        virtual ~Scene_World();

        virtual void update();

        virtual void redraw();

        virtual void mouseclick(int x, int y);

        virtual void escape();

        virtual void handle_scene_input(int input);

		void goToRegion (Region *reg);

    protected:
    private:
		FileContainer image_container;

		/// Player humano, o cara importante do jogo
		Player *human {World::get_world ()->get_human ()};
};

#endif // SCENE_WORLD_H
