#ifndef WINDOW_H
#define WINDOW_H

#include <list>
#include <vector>

#include "FileHandler.hpp"
#include "FileContainer.hpp"
#include "ImageHandler.hpp"

#include "Drawable.hpp"
#include "Widgets.hpp"
#include "Screen.h"
#include "GameStructure.hpp"
#include "SceneControl.hpp"

#include "ScriptHandler.hpp"


// Virtual class parent to each window; holds elements such as buttons and 
// responds to input
class Window : public Drawable
{
    public:
        Window();
        Window(int x, int y); //ctor with window position as parameter
		/** @brief Window Ctor
		 *
		 * Ao construir uma Window, é passado um script lua para uma
		 * inicialização apropriada, e uma função que registra o que
		 * quer que seja que lua_State precise saber.
		 *
		 * @param[in] scriptFile Nome do script lua
		 * @param[in] registerOnLua A função que registra o que o lua_State precisar
		 * Por padrão, a função passada faz nada.
		 */
		Window (const std::string scriptFile, std::function<void (lua_State *)> registerOnLua = [] (lua_State *L) {});
		/** @brief Ctor, chamando a função com o rect
		 * 
		 * Às vezes é preciso
		 */
		Window (const std::string scriptFile, std::function<void (SDL_Rect *, lua_State *)> registerOnLua);

        ~Window();

		/// Adiciona um Widget na Window, o adicionando no vector widgetList
		void addWidget (Widget *W);
		/// Adiciona Sliders a partir de uma Table do lua
		void addSliders (LuaObject luatable);
		/// Adiciona Buttons a partir de uma Table do lua
		void addButtons (LuaObject luatable);
		/// Adiciona TextAreas a partir de uma Table do lua
		void addTextAreas (LuaObject luatable);

		void buttons_setup ();

        //Sets the window position
        void set_position(int x, int y);
        //Gets the window rect
        SDL_Rect * get_position();
        //Runs a mouseclick on the specified coordinates
        void mouseclick(int x, int y);
		/// Gerencia input de teclado
		void handle_input (int input);
        //Draws the window
        void draw(SDL_Surface *screen);
		/// Setta que precisa redesenhar
		void set_need_redraw ();
        //Do an update on the window's and its elements' logic
        void update();

    private:
        std::vector<Widget *> widgetList; //widget lsit
        //Button *buttonList; //a pointer to a list of buttons
        SDL_Rect rect; //the rectangle with coordinates and dimentions of the window
        bool visible; //visibility of the window - to implement
        static const std::string scriptPath;
        static const std::string buttonImgPath;
        static const std::string sliderImgPath;
        ScriptHandler sHandler;

		void redraw ();

        FileContainer files;

		/// Registra Window no estado: função auxiliar ao Ctor
		void registerWindow (lua_State *L);
        //Checks if the mouse is inside the window
        bool is_mouse_inside(int x, int y);

		Widget *on_focus {nullptr};

    protected:
};

#endif // WINDOW_H
