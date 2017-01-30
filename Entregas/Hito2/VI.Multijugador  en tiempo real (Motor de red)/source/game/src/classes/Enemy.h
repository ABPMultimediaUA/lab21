#ifndef ENEMY_H
#define ENEMY_H

#include "Drawable.h"


class Enemy : public Drawable
{
    public:
        Enemy();
        virtual ~Enemy();

        float getSpeed();

        void setNetID(unsigned int netID);

    protected:
        float m_speed;              // Velocidad: hay que actualizarla en el constructor de cada enemigo
        unsigned int m_netID;       // Un ID que debe coincidir con el índice array de entidades que se cree. Se envia junto con cualquier mensaje de red

    private:
};

#endif // ENEMY_H
