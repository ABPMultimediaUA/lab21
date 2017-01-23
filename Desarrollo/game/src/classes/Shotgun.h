#ifndef SHOTGUN_H
#define SHOTGUN_H

#include <Firearm.h>


class Shotgun : public Firearm
{
    public:
        Shotgun();
        virtual ~Shotgun();

        void shoot();
        void reload();

        void update() {};
        void render(){};


    protected:

    private:
};

#endif // SHOTGUN_H
