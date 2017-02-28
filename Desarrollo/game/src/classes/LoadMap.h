#ifndef LOADMAP_H
#define LOADMAP_H

#include "GraphicsEngine.h"
#include "Entity.h"
#include "TriggerDoor.h"
#include "Door.h"

#include <vector>



/////
#include "Entity.h"
#define NUM_ENTITIES 100
#define NUM_ENTITIES2 52

class LoadMap {
    public:
        static LoadMap* getInstance();
        LoadMap();
        ~LoadMap();
        void Init();
        void Update();
        void Destroy();

    private:
        // Suelo
        dwe::Node* suelo;

        Entity *wallEntities[NUM_ENTITIES]; // Array de entidades

        // Paredes
        ScenaryElement* wall;

        Entity *entities[NUM_ENTITIES2]; // Array de entidades
        Entity *sector[1]; // Sector no funcional que se le asigna a un generador
        TriggerDoor *doorTriggers[NUM_ENTITIES2]; // Triggers
};

#endif // LOADMAP_H
