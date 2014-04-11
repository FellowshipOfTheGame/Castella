#ifndef ACTOR_BATTLER_H
#define ACTOR_BATTLER_H


class Actor_Battler
{
    public:
        Actor_Battler();
        virtual ~Actor_Battler();

        bool is_passable();

    protected:
        bool passable;

    private:
};

#endif // ACTOR_BATTLER_H
