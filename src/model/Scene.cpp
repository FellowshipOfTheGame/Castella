#include "Scene.hpp"
#include "Screen.h"

Scene::Scene() : image (create_surface (Screen::WIDTH, Screen::HEIGHT)) {}

Scene::~Scene()
{
    //dtor
    for (auto & win : windows) {
        delete win;
    }
}

void Scene::update(){
    for (auto & win : windows) {
        win->update();
    }
}

void Scene::draw(SDL_Surface *screen){
	if (need_redraw) {
		// limpa background
		fill_surface (screen);
		redraw ();
		apply_surface (0, 0, image, screen);
		need_redraw = false;
	}

	for (auto & win : windows) {
		win->draw(screen);
	}
}

void Scene::mouseclick(int x, int y){
    //If the mouse click was on a window rect, call window->mouseclick()
	for (auto & win : windows) {
        win->mouseclick(x, y);
    }
}

void Scene::escape(){}

//Default generic inputs should be handled here
void Scene::handle_input(){
	do {
		input = Input::get_input();
        switch(input) {
            //Quit
            case Input::QUIT:
                GameVar::gameState = State::QUIT;
                return;
            //F6 - fps cap
            case SDLK_F6:
                GameVar::fpsCap = !GameVar::fpsCap;
                break;
            //ESC
            case SDLK_ESCAPE:
                escape();
                break;
            //Mouseclick - left
            case Input::MOUSE_LEFTCLICK:
                mouseclick(Input::get_mouse_offset().x, Input::get_mouse_offset().y);
                break;

            default:
                //Calls scene-specific input handler
                handle_scene_input(input);
        }
    }
	while(input); // returns 0 when there's no input
}

void Scene::handle_scene_input (int input) {
	for (auto & win : windows) {
		win->handle_input (input);
	}
}

bool Scene::is_key_pressed(SDLKey key){
    return Input::is_key_pressed(key);
}

void Scene::set_need_redraw () {
	need_redraw = true;
}

// definindo as variáveis estáticas
Scene *Scene::scene = nullptr;
void *Scene::ptr = nullptr;
std::stack<Scene *> Scene::scenes;
