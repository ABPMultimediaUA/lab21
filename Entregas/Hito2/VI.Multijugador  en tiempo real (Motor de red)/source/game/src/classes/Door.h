#ifndef DOOR_H
#define DOOR_H
#include "Entity.h"
#include "EntityPhysics.h"

/******************************************************************************
Las puertas bloquean el acceso a una zona. Pueden abrirse o no dependiendo de
si a esa zona le llega energia de un generador o si funcionan desde un principio.

Una vez se termina de abrir la puerta, esta es borrada del juego para ahorrar
memoria y que el juego sea mas eficiente.
*******************************************************************************/

class Door: public Entity, public EntityPhysics
{
    public:
        Door(int f, bool a);
        virtual ~Door();
        void setActive();
        bool getActive();
        void openDoor(); // Llamado desde sector
        void closeDoor();
        bool getIfOpened();
        void setIsOpening();
        bool getIsOpening(); // La puerta se esta abriendo
        void setIsClosing();
        bool getIsClosing();
        virtual void render();
        virtual void update();
        void setPositionClosed(dwe::vec3f p);
        void setPositionOpened(dwe::vec3f p);

        virtual void setNode(dwe::Node* n);
        virtual void setPosition(dwe::vec3f p);

    protected:

    private:
        float x,y,z;
        int op; //Posicion puerta abierta
        int cl; // Posici�n puerta cerrada
        int facing; // 0 1 2 3
        bool active;
        bool isOpening;
        bool isClosing;
        bool isOpened;
        float speed; // Velocidad de apertura y cierre

};

#endif // DOOR_H
