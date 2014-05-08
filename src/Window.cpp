#include <Window.hpp>
using std::cout;
using std::endl;

Window::Window(){cout << "-ctor Window()" << endl;} //ctor

Window::Window(int x, int y)
{
//    sHandler = NULL; //not to let methods call on unallocated script
}

Window::Window(const char *scriptFile, ScriptHandler &sh ) {
    Callback ok;

    ok.registerCallbacks( sh.state() );
    sh.send<int>(Screen::WIDTH, "ScreenWidth");
    sh.send<int>(Screen::HEIGHT, "ScreenHeight");
    luaL_dofile(sh.state(), scriptFile);

    LuaTable table = sh.getTable("window");
    rect.x = table.getInt("x");
    rect.y = table.getInt("y");
    rect.w = table.getInt("w");
    rect.h = table.getInt("h");

    //Set window skin
    SDL_Surface *windowSkin = NULL;
    windowSkin = files.push("images/windowskin.png");
    wSurface = ImageHandler::make_window(rect, windowSkin);
    //Setup elements
    cout << "start elements-setup(state)" << endl;
    elements_setup(sh);
    cout << "end elements-setup(state)" << endl;
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

/*
void Window::elements_setup(lua_State *state){
    //Get button count from the script
    buttonCount = to_cInt(luabind::globals(state), "buttonCount");
    buttonList = Button::create_button_list(buttonCount);
    //Builds each button on the window

    //Definition of parameters to be passed to the button
    LuaTable button, buttonTable = to_luaTable(luabind::globals(state), "buttons");
    std::string path(buttonImgPath);

    for(int i=0; i<buttonCount; i++){
        //Get parameters from the window script
        button = to_luaTable(buttonTable, i+1);
        path += to_cString(button, 3);
        button[3] = path.c_str();
        path += to_cString(button, 4);
        button[4] = path.c_str();
        button[5] = cbk = to_cInt(button, 5);
        //std::cout << "x: " << x << "  -  y: " << y << "  -  imgI: " << imgIname << "  -  imgA: " << imgAname << "  -  cbk: " << cbk << std::endl;
        //Makes the button and pushes to the list
        buttonList[i] = Button(&rect, button);
    }
}
*/

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
        //std::cout << "x: " << x << " - y: " << y << " - imgI: " << imgIname << " - imgA: " << imgAname << " - cbk: " << cbk << std::endl;
        //Loads the images to SDL_Surface
        SDL_Surface *imgInactive = NULL, *imgActive = NULL;
        imgInactive = files.push(imgIname.c_str()); //load_image(&imgInactive, (char*)imgIname.c_str());
        imgActive = files.push(imgAname.c_str()); //load_image(&imgActive, (char*)imgAname.c_str());
        //Makes the button and pushes to the list
        buttonList[i] = Button(&rect, x, y, imgInactive, imgActive, Callback::callback(cbk));
    }
}

void Window::elements_setup(ScriptHandler &sh){
    //Get button count from the script
    buttonCount = sh.get<int>("buttonCount");
    cout << "count = " << buttonCount << endl;
    buttonList = Button::create_button_list(buttonCount);
    //Builds each button on the window
    std::string imgIname, imgAname;
    //AQint x, y;
    LuaTable button, buttons = sh.getTable("buttons");
    //AQLuaObject cbk;
    SDL_Surface *imgInactive = NULL, *imgActive = NULL;
    cout << "beginning loop" << endl;
    for(int i=0; i<buttonCount; i++) {
        button = buttons.getLuaTable(i+1);
        imgIname = imgAname = buttonImgPath;
        //Definition of parameters to be passed to the button
        //Get parameters from the window script
        /*AQx = button.getInt(1);
        y = button.getInt(2);*/
        imgIname += button.getString(3);
        imgAname += button.getString(4);
        //AQcbk = button.getLuaType(5);
        //AQcout << x << " -> " << y << " -> " << imgIname << " -> " << imgAname << endl;

        //Loads the images to SDL_Surface
        imgInactive = files.push(imgIname.c_str()); //load_image(&imgInactive, (char*)imgIname.c_str());
        imgActive = files.push(imgAname.c_str()); //load_image(&imgActive, (char*)imgAname.c_str());
        //Makes the button and pushes to the list

        buttonList[i] = Button(&rect, button.getInt(1), button.getInt(2), imgInactive, imgActive, button.getLuaType(5) );
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
