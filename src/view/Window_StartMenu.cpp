#include <Window_StartMenu.hpp>

Window_StartMenu::Window_StartMenu(){}

Window_StartMenu::Window_StartMenu(std::string script) : Window (script) {
    // Elementos do StartMenu
}

void Window_StartMenu::elements_setup(){
}

Window_StartMenu::~Window_StartMenu ()
{
    //dtor
}

//Updates the window
void Window_StartMenu::update(){
    Window::update();
}

