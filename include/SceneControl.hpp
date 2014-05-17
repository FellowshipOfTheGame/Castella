#ifndef SCENECONTROL_H
#define SCENECONTROL_H

class SceneControl
{
    public:
        enum Scenes{
            SCENE_NULL,
            SCENE_START_MENU,
            SCENE_WORLD,
            SCENE_REGION,
            SCENE_BATTLE,
            SCENE_EDITOR,
            END
        };

        SceneControl();
        virtual ~SceneControl();

        static void set_next(Scenes next);
        static int get_next();
        static void set_cur(Scenes cur);
        static int get_cur();
        static void update();

    protected:
    private:
        static int nextScene;
        static int curScene;
};

#endif // SCENECONTROL_H
