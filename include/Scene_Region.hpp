/** @file Scene_Region.hpp
 *
 * @brief Cena das @ref Region "regiões"
 *
 * Aqui se apresentam as @ref Structure "estruturas" e controle das mesmas (se quiser criar novas).
 */

#ifndef SCENE_REGION_HPP
#define SCENE_REGION_HPP

#include "Scene.hpp"

class Scene_Region : public Scene {
public:
    Scene_Region ();
    virtual ~Scene_Region ();
	virtual void update ();
	virtual void draw (SDL_Surface *screen);

protected:

private:

};

#endif