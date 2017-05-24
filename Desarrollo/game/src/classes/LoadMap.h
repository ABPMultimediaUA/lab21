#ifndef LOADMAP_H
#define LOADMAP_H

#include "GraphicsEngine.h"
#include "Entity.h"
#include "Door.h"
#include "DoorRotate.h"
#include "Generator.h"
#include "Scene.h"
#include "Floor.h"

#include <vector>

/////
#include "Entity.h"
#define NUM_WALLS           181
#define NUM_FLOORS          53
#define NUM_DOORS           34
#define NUM_GENERATORS      4
#define NUM_MAP_DOORROTATE  1
#define NUM_ENVIRONMENT_ELEMENTS 106 // 85 - Ultima adicion: Cosas random por mapa

class LoadMap {
    public:
        static LoadMap* getInstance();
        LoadMap();
        ~LoadMap();
        void Init();
        void Update();
        void Destroy();
        void cheatDoorOpen();
        void createScenaryElement(const char* s, const dwe::vec3f &pos, const dwe::vec3f &rot, Drawable* parent);

    private:
        // Suelo
        int numFloors;
        Floor *floors[NUM_FLOORS];

        // Elementos de clipping
        ClippingObject* clippingObjects[NUM_FLOORS];

        // Paredes
        int numWalls;
        ScenaryElement *walls[NUM_WALLS];

        // Elementos de escenario
        int numEnvElements;
        ScenaryElement *envElements[NUM_ENVIRONMENT_ELEMENTS];

        int numDoors;
        Entity *entities[NUM_DOORS]; // Array de puertas

        int numGenerators;
        int generatorID;
        Generator *generator[NUM_GENERATORS];

        int numDoorsRotate;
        DoorRotate* entitiesDoorRotate[NUM_MAP_DOORROTATE];

        int magnetKeyCount;
        int magnetKeyID;

        bool cheats;


        void calculateClipping();
};

#endif // LOADMAP_H
