#ifndef CALLBACK_H
#define CALLBACK_H

typedef void (*funcPointer)();

class Callback
{
    public:
        Callback();
        virtual ~Callback();

        static void game_start();
        static void game_load();
        static void game_quit();

        static void start_battle();

        static funcPointer callback(int i);

    protected:
    private:
};

#endif // CALLBACK_H
