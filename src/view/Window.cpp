#include <Window.hpp>

using std::cout;
using std::endl;

Window::Window(){cout << "-ctor Window()" << endl;} //ctor

Window::Window(int x, int y)
{
//    sHandler = NULL; //not to let methods call on unallocated script
}

Window::Window(const std::string scriptFile) : sHandler(Window::scriptPath + scriptFile) {

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
	string windowSkinPath = table.getString ("windowSkin");

    //Set window skin
	if (windowSkinPath == "") {
		windowSkinPath = "defaultWindowSkin.png";
	}

	SDL_Surface *windowSkin = NULL;
	windowSkin = files.push ("images/" + windowSkinPath);
	wSurface = ImageHandler::make_window (rect, windowSkin);

}

void Window::elements_setup() {
}

Window::~Window(){
    SDL_FreeSurface(wSurface);
    for (auto & widget : widgetList) {
        delete widget;
    }
    cout << "dtor Window" << endl;
}//dtor

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
    // Vê se clica em cada widget
    for (auto & widget : widgetList) {
        widget->mouse_try_click (x,y);
    }
}

void Window::draw(SDL_Surface *screen){
    //Draw windowskin
    apply_surface(rect.x, rect.y, wSurface, screen);
    //For each window element: draw
    //Draw each button
    for (auto & widget : widgetList) {
        widget->draw(screen);
    }
}

void Window::update(){
    for (auto & widget : widgetList) {
        widget->update();
    }
}

const std::string Window::scriptPath("script/windows/");
const std::string Window::buttonImgPath("images/buttons/");
