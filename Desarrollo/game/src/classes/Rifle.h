#ifndef RIFLE_H
#define RIFLE_H

#include <Firearm.h>


class Rifle : public Firearm
{
    public:
        Rifle();
        virtual ~Rifle();

        void shoot();
        void reload();

        void update() {};
        void render(){};

    protected:

    private:
};

#endif // RIFLE_H
