#include <Window_StartMenu.hpp>

Window_StartMenu::Window_StartMenu(){}

Window_StartMenu::Window_StartMenu(std::string script) : Window (script) {
    // Elementos do StartMenu
    cout << "start elements-setup()" << endl;
    elements_setup();
    cout << "end elements-setup()" << endl;
}

void Window_StartMenu::elements_setup(){
    //Get button count from the script
    int buttonCount = sHandler.get<int>("nBotoes");
    cout << "count = " << buttonCount << endl;

    //Build each button on the window
    std::string imgIname, imgAname;
    //Get the buttons table from lua.
    LuaTable button, buttons = sHandler.getTable("botoes");
    SDL_Surface *imgInactive = NULL, *imgActive = NULL;

    cout << "beginning loop" << endl;
    for(int i = 0; i < buttonCount; i++) {
        button = buttons.getLuaTable(i+1);
        imgIname = imgAname = buttonImgPath;
        //Definition of parameters to be passed to the button
        //Get parameters from the window script
        imgIname += button.getString(3);
        imgAname += button.getString(4);

        //Loads the images to SDL_Surface
        imgInactive = files.push( imgIname.c_str() ); //load_image(&imgInactive, (char*)imgIname.c_str());
        imgActive = files.push( imgAname.c_str() ); //load_image(&imgActive, (char*)imgAname.c_str());

        widgetList.push_back(new Button(&rect, button.getInt(1), button.getInt(2), imgInactive, imgActive,
                                                        button.getLuaType(5) ) );
    }
}

Window_StartMenu::~Window_StartMenu ()
{
    //dtor
}

//Updates the window
void Window_StartMenu::update(){
    Window::update();
}

