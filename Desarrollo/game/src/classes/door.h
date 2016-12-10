#ifndef DOOR_H
#define DOOR_H
#include "Entity.h"

/******************************************************************************
Las puertas bloquean el acceso a una zona. Pueden abrirse o no dependiendo de
si a esa zona le llega energia de un generador o si funcionan desde un principio.

Una vez se termina de abrir la puerta, esta es borrada del juego para ahorrar
memoria y que el juego sea mas eficiente.
*******************************************************************************/

class Door: public Entity
{
    public:
        Door(int i, int u, int f, bool a);
        virtual ~Door();
        virtual void setActive();
        void openDoor(); // Llamado desde sector
        void setIsOpening();
        bool getIsOpening(); // La puerta se esta abriendo
        virtual void render();
        virtual void update();

    protected:

    private:
        int x, z;
        int op; //Posicion puerta abierta
        int facing; // 0 1 2 3
        bool active;
        bool isOpening;
        bool isOpened;
};

#endif // DOOR_H
