#ifndef TIMER_H
#define TIMER_H
/*This piece of code was originally from Lazy Foo' Productions
(http://lazyfoo.net/)*/

class Timer
{
    private:
        //The clock time when the timer started
        int startTicks;
        //The ticks stored when the timer was paused
        int pausedTicks;
        //The timer status
        bool started;
        bool paused;

    public:
        //Initializes the variables
        Timer();
        //The various clock actions
        void start();
        void stop();
        void pause();
        void unpause();
        //Gets timer's time
        int get_ticks();
        //Checks the status of the timer
        bool is_started();
        bool is_paused();
};

#endif // TIMER_H

