#include <Window_StartMenu.hpp>

Window_StartMenu::Window_StartMenu(){}

Window_StartMenu::Window_StartMenu(std::string script) : Window::Window(script){}

Window_StartMenu::~Window_StartMenu()
{
    //dtor
}

//Updates the window
void Window_StartMenu::update(){
    Window::update();
    //Zuera
    rect.x+=3;
    if(rect.x >= Screen::WIDTH - rect.w){
		rect.x = 0;
	}
}

