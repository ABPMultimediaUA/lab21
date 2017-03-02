#ifndef GUN_H
#define GUN_H

#include <Firearm.h>

class Player;

class Gun : public Firearm
{
    public:
        Gun();
        virtual ~Gun();

        void shoot();
        void reload();
        void onTake(Player* mainPlayer);

        //void update(Player* mainPlayer);
        //void render();

    protected:

    private:
};

#endif // GUN_H
