#ifndef GENERATOR_H
#define GENERATOR_H

#include "Entity.h"

class TriggerGenerator;

/******************************************************************************
Los generadores se encargan de suministrar energia a las luces y puertas de
una zona que se encuentre desactivada.
*******************************************************************************/

class Generator: public Entity
{
    public:
        Generator(int n, bool b);
        virtual ~Generator();
        void setSector(Entity **s, int e);
        void activateGenerator(); // Activa generador
        int getNum();
        bool getIsActive();
        virtual void render();
        virtual void update();

        virtual void setNode(dwe::Node* n);

        void SetSensor();

    protected:

    private:
        int num;
        bool active;
        int entities; // A cuantas entidades esta relacionado
        Entity **sector; // Array de entidades
        TriggerGenerator* m_trigger;
};

#endif // GENERATOR_H
