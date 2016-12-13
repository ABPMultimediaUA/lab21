#ifndef DOOR_H
#define DOOR_H
#include <GraphicsEngine.h>
#include "entity.h"

/******************************************************************************
Las puertas bloquean el acceso a una zona. Pueden abrirse o no dependiendo de
si a esa zona le llega energia de un generador o si funcionan desde un principio.

Una vez se termina de abrir la puerta, esta es borrada del juego para ahorrar
memoria y que el juego sea mas eficiente.
*******************************************************************************/

class door: public entity
{
    public:
        door(int i, int u, int f, bool a);
        virtual ~door();
        virtual void setActive();
        void openDoor(); // Llamado desde sector
        void setIsOpening();
        bool getIsOpening(); // La puerta se esta abriendo
        virtual void render();
        virtual void update();
    protected:

    private:
        dwe::Node* _door;
        int x, z;
        int op; //Posicion puerta abierta
        int facing; // 0 1 2 3
        bool active;
        bool isOpening;
        bool isOpened;
        // nodo puerta

};

#endif // DOOR_H
