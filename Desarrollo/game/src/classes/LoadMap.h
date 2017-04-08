#ifndef LOADMAP_H
#define LOADMAP_H

#include "GraphicsEngine.h"
#include "Entity.h"
#include "TriggerDoor.h"
#include "TriggerGenerator.h"
#include "Door.h"
#include "Generator.h"
#include "Scene.h"

#include <vector>



/////
#include "Entity.h"
#define NUM_MAP_ENTITIES 100
#define NUM_MAP_ENTITIES2 53

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

        Entity *wallEntities[NUM_MAP_ENTITIES]; // Array de entidades

        // Paredes
        ScenaryElement* wall;

        Entity *entities[NUM_MAP_ENTITIES2]; // Array de entidades
        Generator *generator;
        //Entity *sector[1]; // Sector no funcional que se le asigna a un generador
        //Consumable *ammos[2];
        TriggerDoor *doorTriggers[NUM_MAP_ENTITIES2]; // Triggers
};

#endif // LOADMAP_H
