#ifndef ENEMY_H
#define ENEMY_H

#include "Drawable.h"


class Enemy : public Drawable
{
    public:
        Enemy();
        virtual ~Enemy();

        float getSpeed();

    protected:
        float m_speed;   // Velocidad: hay que actualizarla en el constructor de cada enemigo

    private:
};

#endif // ENEMY_H
