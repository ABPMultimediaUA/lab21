#ifndef GUN_H
#define GUN_H

#include <Firearm.h>


class Gun : public Firearm
{
    public:
        Gun();
        virtual ~Gun();

        void shoot();
        void reload();

        void update() {};
        void render(){};

    protected:

    private:
};

#endif // GUN_H
