#ifndef ACTOR_H
#define ACTOR_H

class Actor
{
    public:
        Actor();
        virtual ~Actor();
        int get_hp();
        int get_mp();
        int get_stamina();

    protected:
    private:
        static int idCount;
        int id;
        int hp;
        int mp;
        int stamina;
};
#endif // ACTOR_H
