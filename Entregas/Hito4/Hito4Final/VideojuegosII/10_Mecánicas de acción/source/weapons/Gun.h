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

        virtual void setPut();   // Enfundada
        virtual void setDraw();  // Desenfundada

    protected:

    private:
};

#endif // GUN_H
