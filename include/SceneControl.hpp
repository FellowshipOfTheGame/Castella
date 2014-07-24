#ifndef SCENECONTROL_H
#define SCENECONTROL_H

/** @brief Tipo de cenas possíveis
 *
 */
enum class Scenes {
	SCENE_NULL,
	SCENE_START_MENU,
	SCENE_WORLD,
	SCENE_REGION,
	SCENE_BATTLE,
	SCENE_EDITOR,
	SCENE_EXIT,
};

/** @brief Controlador de cenas
 *
 * As mudanças de cenas (transições) tão definidas aqui
 */
class SceneControl
{
    public:

        SceneControl();
        virtual ~SceneControl();

		/** Sai da cena atual e a desempilha 
		 * (chama a popScene, que faz isso de verdade)
		 */
		static void exitScene ();

        static void set_next(Scenes next);
        static Scenes get_next();
        static void set_cur(Scenes cur);
        static Scenes get_cur();
        static void update();

    protected:
    
    private:
		static void popScene ();
        static Scenes nextScene;
        static Scenes curScene;
};

#endif // SCENECONTROL_H
