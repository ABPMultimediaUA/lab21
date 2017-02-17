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
        ScenaryElement* wall01;
        ScenaryElement* wall02;
        ScenaryElement* wall03;
        ScenaryElement* wall04;
        ScenaryElement* wall05;
        ScenaryElement* wall06;
        ScenaryElement* wall07;
        ScenaryElement* wall08;
        ScenaryElement* wall09;
        ScenaryElement* wall10;
        ScenaryElement* wall11;
        ScenaryElement* wall12;
};

#endif // LOADMAP_H
