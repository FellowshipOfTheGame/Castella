#include <Scene.hpp>

Scene::Scene()
{

}

Scene::~Scene()
{
    //dtor
    for(int i = windows.size()-1; i>=0; i--){
        delete windows[i];
    }
}

void Scene::update(){
    for(int i = windows.size()-1; i>=0; i--){
        windows[i]->update();
    }
}

void Scene::draw(SDL_Surface *screen){
    for(int i = windows.size()-1; i>=0; i--){
        windows[i]->draw(screen);
    }
}

void Scene::mouseclick(int x, int y){
    //If the mouse click was on a window rect, call window->mouseclick()
    for(int i = windows.size()-1; i>=0; i--){
        windows[i]->mouseclick(x, y);
    }
}

void Scene::escape(){}

//Default generic inputs should be handled here
void Scene::handle_input(){
    do {
        //Gets next input
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
// definindo as variáveis estáticas
Scene *Scene::scene = nullptr;
void *Scene::ptr = nullptr;
std::stack<Scene*> Scene::scenes;
