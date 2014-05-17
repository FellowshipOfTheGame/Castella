#ifndef GAMESTRUCTURE_H
#define GAMESTRUCTURE_H

/*class State {
   public:
*/
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
	
	//int set_State(const int newState);

};

#endif // GAMESTRUCTURE_H

