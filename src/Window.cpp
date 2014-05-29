#include <Window.hpp>
using std::cout;
using std::endl;

Window::Window(){cout << "-ctor Window()" << endl;} //ctor

Window::Window(int x, int y)
{
//    sHandler = NULL; //not to let methods call on unallocated script
}

Window::Window(const std::string scriptFile) : sHandler(Window::scriptPath + scriptFile){

    //Registers the needed variables and runs the code.
    //Warning if the Callbacks are already registered at that lua state bad things may happen.
    Callback::registerCallbacks(sHandler.L);
    sHandler.send<int>(Screen::WIDTH, "TelaComprimento");
    sHandler.send<int>(Screen::HEIGHT, "TelaAltura");
    sHandler.run_lua();

    //Creates a rect from the window table
    LuaTable table = sHandler.getTable("janela");
    rect.x = table.getInt("x");
    rect.y = table.getInt("y");
    rect.w = table.getInt("c");
    rect.h = table.getInt("a");

    //Set window skin
    SDL_Surface *windowSkin = NULL;
    windowSkin = files.push("images/windowskin.png");
    wSurface = ImageHandler::make_window(rect, windowSkin);
    //Setup elements
    cout << "start elements-setup()" << endl;
    elements_setup();
    cout << "end elements-setup()" << endl;
}

Window::~Window(){
    SDL_FreeSurface(wSurface);
    delete [] buttonList;
    cout << "dtor Window" << endl;
}//dtor

void Window::elements_setup(){
    //Get button count from the script
    buttonCount = sHandler.get<int>("nBotoes");
    cout << "count = " << buttonCount << endl;
    
    //Allocate memory for the buttonlist
    buttonList = Button::create_button_list(buttonCount);
    
    //Build each button on the window
    std::string imgIname, imgAname;
    //Get the buttons table from lua.
    LuaTable button, buttons = sHandler.getTable("botoes");
    SDL_Surface *imgInactive = NULL, *imgActive = NULL;
    
    cout << "beginning loop" << endl;
    for(int i=0; i<buttonCount; i++) {
        button = buttons.getLuaTable(i+1);
        imgIname = imgAname = buttonImgPath;
        //Definition of parameters to be passed to the button
        //Get parameters from the window script
        imgIname += button.getString(3);
        imgAname += button.getString(4);

        //Loads the images to SDL_Surface
        imgInactive = files.push( imgIname.c_str() ); //load_image(&imgInactive, (char*)imgIname.c_str());
        imgActive = files.push( imgAname.c_str() ); //load_image(&imgActive, (char*)imgAname.c_str());

        buttonList[i] = Button(&rect, button.getInt(1), button.getInt(2), imgInactive, imgActive, 
                                        button.getLuaType(5) );
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
