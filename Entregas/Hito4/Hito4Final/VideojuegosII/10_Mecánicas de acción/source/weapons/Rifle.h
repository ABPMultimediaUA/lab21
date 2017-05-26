#ifndef RIFLE_H
#define RIFLE_H

#include <Firearm.h>

class Player;

class Rifle : public Firearm
{
    public:
        Rifle();
        virtual ~Rifle();

        void shoot();
        void reload();

        void render(){};

        virtual void setPut();   // Enfundada
        virtual void setDraw();  // Desenfundada

    protected:

    private:
};

#endif // RIFLE_H
