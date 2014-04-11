#ifndef GAMESTRUCTURE_H
#define GAMESTRUCTURE_H

namespace State {
    enum GameStates{
        NULL_STATE,
        MAIN,
        WORLD,
        DIPLOMACY,
        QUIT
    };
}

class GameVar{
    public:
        static int gameState;
        static bool fpsCap;

};

#endif // GAMESTRUCTURE_H

