#ifndef WINDOW_STARTMENU_H
#define WINDOW_STARTMENU_H

#include "Window.hpp"
#include "Button.hpp"

//FIXME - this class is obsolete and will be taken away after it is used for some tests

class Window_StartMenu : public Window
{
    public:
        Window_StartMenu();
        Window_StartMenu(std::string script);
        virtual ~Window_StartMenu();
        void update();
        virtual void elements_setup();

    protected:
    private:
};

#endif // WINDOW_STARTMENU_H
