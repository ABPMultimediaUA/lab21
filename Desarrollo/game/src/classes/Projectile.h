#ifndef PROJECTILE_H
#define PROJECTILE_H
#include "Entity.h"

/******************************************************************************
Los proyectiles son los elementos que viajan de una posicion a otra del espacio
y haran una funcion diferente dependiendo del tipo de proyectil que sea.
*******************************************************************************/

class Projectile: public Entity
{
    public:
        Projectile();
        Projectile(int *o, float a); // Proyectil creado por player
        Projectile(int *o, int *d); // Proyectil creado por enemigos
        virtual ~Projectile();
        void moveProjectile();
        bool getCollides();
        double* getPosition();
        virtual void render();
        virtual void update();

    protected:

    private:
        double position[2];
        int speed;
        float angle;
        bool collides;
};

#endif // PROJECTILE_H
