#ifndef LOADMAP_H
#define LOADMAP_H

#include "GraphicsEngine.h"
#include "Entity.h"
#include "TriggerDoor.h"
#include "TriggerGenerator.h"
#include "MagnetKey.h"
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
#define NUM_DOORS           34 //34
#define NUM_MAP_DOORROTATE  1
#define NUM_ENVIRONMENT_ELEMENTS 7

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
        int numFloors;
        Floor *floors[NUM_FLOORS];

        // Paredes
        int numWalls;
        ScenaryElement *walls[NUM_WALLS];

        // Elementos de escenario
        ScenaryElement *envElements[NUM_ENVIRONMENT_ELEMENTS];

        Entity *entities[NUM_DOORS]; // Array de puertas
        Generator *generator[4];
        MagnetKey *MKAux;
        std::vector<MagnetKey*> *magnetKeys;
        //Consumable *ammos[2];

        DoorRotate* entitiesDoorRotate[NUM_MAP_DOORROTATE];

        bool cheats;
};

#endif // LOADMAP_H
