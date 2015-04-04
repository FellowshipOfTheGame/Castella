#include "Window.hpp"

using namespace std;
using namespace luabind;

Window::Window(){cout << "-ctor Window()" << endl;} //ctor


Window::Window(int x, int y)
{
//    sHandler = NULL; //not to let methods call on unallocated script
}


Window::Window (const string scriptFile, function<void (SDL_Rect *, lua_State *)> registerOnLua)
		: Window (scriptFile, bind (registerOnLua, &rect, placeholders::_1)) {
};


Window::Window (const string scriptFile, function<void (lua_State *)> registerOnLua)
		: sHandler (Window::scriptPath + scriptFile) {

    //Registers the needed variables and runs the code.
    //Warning if the Callbacks are already registered at that lua state bad things may happen.
	registerWindow (sHandler.L);
    registerOnLua (sHandler.L);
    sHandler.send<int>(Screen::WIDTH, "TelaComprimento");
    sHandler.send<int>(Screen::HEIGHT, "TelaAltura");
    sHandler.send<Window *> (this, "Win");
    sHandler.run_lua ();

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


void Window::addWidget (Widget *W) {
	widgetList.push_back (W);
}


void Window::registerWindow (lua_State *L) {
	module (L) [
		class_<Window> ("Window")
			.def ("addWidget", &Window::addWidget)
			.def ("addSliders", &Window::addSliders)
			.def ("addButtons", &Window::addButtons)
			.def ("addTextAreas", &Window::addTextAreas)
			.def ("getPosition", &Window::get_position),
		class_<SDL_Rect> ("SDL_Rect")
	];
}


void Window::addButtons (LuaObject luatable) {
	LuaTable table (luatable);

	// Nomes das imagens
    std::string imgIname, imgAname;
	// As imagens dos botões
    SDL_Surface *imgInactive = NULL, *imgActive = NULL;

	// Pra cada LuaTable, constrói um Button
    for (LuaObject obj : table) {
		LuaTable button (obj);

        imgIname = imgAname = buttonImgPath;
        //Definition of parameters to be passed to the button
        //Get parameters from the window script
        imgIname += button.getString (3);
        imgAname += button.getString (4);

        //Loads the images to SDL_Surface
        imgInactive = files.push ( imgIname );
        imgActive = files.push ( imgAname );

        widgetList.push_back (new Button (&rect, button.getInt(1), 
				button.getInt(2), imgInactive, imgActive,
				button.getLuaType (5) ) );
    }
}


void Window::addSliders (LuaObject luatable) {
	LuaTable table (luatable);

	// Nomes das imagens
    std::string img_back_name, img_selector_name;
	// As imagens, do fundo e do seletor
    SDL_Surface *img_back = NULL, *img_selector = NULL;

	// Pra cada LuaTable, constrói um Slider
	for (LuaObject obj : table) {
		LuaTable slider (obj);

        img_back_name = img_selector_name = sliderImgPath;
        //Definition of parameters to be passed to the button
        //Get parameters from the window script
        img_back_name += slider.getString(3);
        img_selector_name += slider.getString(4);

        //Loads the images to SDL_Surface
        img_selector = files.push (img_selector_name.c_str());
        img_back = files.push (img_back_name.c_str());

        widgetList.push_back (new Slider (&rect,
				slider.getInt(1), slider.getInt(2),
				img_back, img_selector));
	}
}


void Window::addTextAreas (LuaObject luatable) {
	LuaTable table (luatable);

	// Pra cada LuaTable, constrói um TextArea
	for (LuaObject obj : table) {
		LuaTable text_area (obj);

		// pega as tables das cores
		LuaTable fore_table (text_area.getLuaTable (5));
		LuaTable back_table (text_area.getLuaTable (6));
		// e as transforma em SDL_Color, pra usar no construtor
		SDL_Color foreground = {fore_table.get<Uint8> (1),
				fore_table.get<Uint8> (2), fore_table.get<Uint8>  (3)};

		SDL_Color background = {back_table.get<Uint8> (1),
				back_table.get<Uint8> (2), back_table.get<Uint8>  (3)};

        widgetList.push_back (new TextArea (&rect,
				text_area.getInt(1), text_area.getInt(2),
				text_area.getInt(3), text_area.getInt(4),
				foreground, background));
	}
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


SDL_Rect * Window::get_position(){
    return &rect;
}


bool Window::is_mouse_inside(int x, int y){
    //Check given coordinates against window
    if (x >= rect.x && x <= rect.x + rect.w && 
			y >= rect.y && y <= rect.y + rect.h) {
        return true;
    }
    return false;
}


void Window::mouseclick(int x, int y){
	// só roda se tiver dentro da tela, né
    if (is_mouse_inside(x, y)) {
		// assume que clicou em ninguém
		on_focus = nullptr;

		for (auto & widget : widgetList) {
			if (widget->mouse_try_click (x, y)) {
				on_focus = widget;
			}
		}
	}
}


void Window::handle_input (int input) {
	// só 
	if (on_focus) {
		on_focus->handle_input (input);
	}
}


void Window::draw(SDL_Surface *screen){
    //Draw windowskin
    apply_surface(rect.x, rect.y, wSurface, screen);
    //For each window element: draw
    for (auto & widget : widgetList) {
        widget->draw (screen);
    }
}


void Window::update(){
    for (auto & widget : widgetList) {
        widget->update ();
    }
}


const std::string Window::scriptPath ("script/windows/");
const std::string Window::buttonImgPath ("images/buttons/");
const std::string Window::sliderImgPath ("images/sliders/");
