#ifndef LOADMAP_H
#define LOADMAP_H

#include "GraphicsEngine.h"

/////
#include "Entity.h"
#define NUM_ENTITIES 100

class LoadMap {
    public:
        static LoadMap* getInstance();
        LoadMap();
        ~LoadMap();
    private:
        // Suelo
        dwe::Node* suelo;

        Entity *wallEntities[NUM_ENTITIES]; // Array de entidades


        // Paredes
        ScenaryElement* wall;
};

#endif // LOADMAP_H
