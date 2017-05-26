#ifndef SHOTGUN_H
#define SHOTGUN_H

#include <Firearm.h>

class Player;

class Shotgun : public Firearm
{
    public:
        Shotgun();
        virtual ~Shotgun();

        void shoot();
        void reload();
        void render(){};

        virtual void setPut();   // Enfundada
        virtual void setDraw();  // Desenfundada

    protected:

    private:
};

#endif // SHOTGUN_H
