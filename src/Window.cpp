#include "Window.hpp"

Window::Window(){cout << "-ctor Window()" << endl;} //ctor

Window::Window(int x, int y)
{
//    sHandler = NULL; //not to let methods call on unallocated script
}

Window::Window(std::string script){
    cout << "-ctor Window(string)" << endl;
    //Set the lua script path
    script = scriptPath+script;
    cout << "start ScriptHandler(script)" << endl;
    sHandler = new ScriptHandler(script);
    cout << "end ScriptHandler(script)" << endl;
    sHandler->variable_toLua(Screen::WIDTH, "ScreenWidth");
    sHandler->variable_toLua(Screen::WIDTH, "ScreenHeight");
    sHandler->run_lua(); //gets lua variables to the table (metatable?)
    rect.x = (int)sHandler->variable_fromLua("wX");
    rect.y = (int)sHandler->variable_fromLua("wY");
    rect.w = sHandler->variable_fromLua("wW");
    rect.h = sHandler->variable_fromLua("wH");
    //Set window skin
    SDL_Surface *windowSkin = NULL;
    windowSkin = files.push("images/windowskin.png");
    wSurface = ImageHandler::make_window(rect, windowSkin);
    //Setup elements
    cout << "start elements-setup()" << endl;
    elements_setup();
    cout << "end elements-setup()" << endl;
    sHandler->~ScriptHandler();
    //sHandler.close(); //FIXME - it may not be necessary
}

Window::~Window(){
    SDL_FreeSurface(wSurface);
    cout << "dtor Window" << endl;
}//dtor

void Window::elements_setup(){
    //Get button count from the script
    buttonCount = (int)sHandler->variable_fromLua("buttonCount");
    buttonList = Button::create_button_list(buttonCount);
    //Builds each button on the window
    for(int i=0; i<buttonCount; i++){
        //Definition of parameters to be passed to the button
        int x, y, cbk;
        std::string imgIname = buttonImgPath;
        std::string imgAname = buttonImgPath;
        //Get parameters from the window script
        x = (int)sHandler->table_element_fromLua(i, 0); //+1: lua starts index from 1
        y = (int)sHandler->table_element_fromLua(i, 1);
        imgIname += (const char*)sHandler->table_element_fromLua(i, 2);
        imgAname += (const char*)sHandler->table_element_fromLua(i, 3);
        cbk = (int)sHandler->table_element_fromLua(i, 4);

        //std::cout << "x: " << x << "  -  y: " << y << "  -  imgI: " << imgIname << "  -  imgA: " << imgAname << "  -  cbk: " << cbk << std::endl;
        //Loads the images to SDL_Surface
        SDL_Surface *imgInactive = NULL, *imgActive = NULL;
        imgInactive = files.push(imgIname.c_str()); //load_image(&imgInactive, (char*)imgIname.c_str());
        imgActive = files.push(imgAname.c_str()); //load_image(&imgActive, (char*)imgAname.c_str());
        //Makes the button and pushes to the list
        buttonList[i] = Button(&rect, x, y, imgInactive, imgActive, Callback::callback(cbk));
    }
}

void Window::set_position(int x, int y){
    rect.x = x;
    rect.y = y;
}

SDL_Rect Window::get_position(){
    return rect;
}

bool Window::is_mouse_inside(int x, int y){
    //Check given coordinates against window
    if (x >= rect.x && x <= rect.x+rect.w && y >= rect.y && y <= rect.y+rect.h){
        return true;
    }
    return false;
}

void Window::mouseclick(int x, int y){
    //Return if the mouse isn't over the window
    if (!is_mouse_inside(x, y)) return;
    //Try click on each button
    for(int i = 0; i < buttonCount; i++){
        buttonList[i].mouse_try_click(x,y);
    }
}

void Window::draw(SDL_Surface *screen){
    //Draw windowskin
    apply_surface(rect.x, rect.y, wSurface, screen);
    //For each window element: draw
    //Draw each button
    for(int i = 0; i < buttonCount; i++){
        buttonList[i].draw(screen);
    }
}

void Window::update(){
//    for (int i=0; i< buttonCount; i++){
//        buttonList[i].update();
//    }
    for(int i = 0; i < buttonCount; i++){
        buttonList[i].update();
    }
}

const std::string Window::scriptPath("script/windows/");
const std::string Window::buttonImgPath("images/buttons/");
