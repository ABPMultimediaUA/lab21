#include "LoadMap.h"
#include "GraphicsEngine.h"
#include "ScenaryElement.h"

#include <fstream> //Lectura de ficheros
#include <document.h> //ES UN .H de rapidJSON
using namespace rapidjson;

LoadMap::LoadMap()
{

}

struct TTag2Wall {
    std::string tag;
    std::string model;
};

TTag2Wall mappingWall[] = {
        {"Wall_01_50m"    ,   "unityPared01_50m"  }
    ,   {"Wall_01_100m"   ,   "unityPared01_100m" }
    ,   {"Wall_01_200m"   ,   "unityPared01_200m" }
    ,   {"Wall_01_300m"   ,   "unityPared01_300m" }
    ,   {       "0"       ,             "0"       }
};

struct TTag2Floor {
    std::string tag;
    std::string model;
};

TTag2Floor mappingFloor[] = {
        {"Floor_Hall"      ,   "unitySuelo_Hall"      }
    ,   {"Floor_50x50"     ,   "unitySuelo_50x50"     }
    ,   {"Floor_100x50"    ,   "unitySuelo_100x50"    }
    ,   {"Floor_200x50"    ,   "unitySuelo_200x50"    }
    ,   {"Floor_300x50"    ,   "unitySuelo_300x50"    }
    ,   {"Floor_500x50"    ,   "unitySuelo_500x50"    }
    ,   {"Floor_100x100"   ,   "unitySuelo_100x100"   }
    ,   {"Floor_200x100"   ,   "unitySuelo_200x100"   }
    ,   {"Floor_900x100"   ,   "unitySuelo_900x100"   }
    ,   {"Floor_200x150"   ,   "unitySuelo_200x150"   }
    ,   {"Floor_250x200"   ,   "unitySuelo_250x200"   }
    ,   {"Floor_250x300"   ,   "unitySuelo_250x300"   }
    ,   {"Floor_400x300"   ,   "unitySuelo_400x300"   }
    ,   {       "0"        ,             "0"          }
};

void LoadMap::Init(){
    GEInstance->pop();

    numWalls = 0;
    numFloors = 0;

    Scene* s = Scene::Instance();

    const char* json; //Aqui va a ir todo el archivo
    std::string allText = "";

    //FICHERO
    ifstream fichero ("unityText.json", ios::in | ios::app | ios::binary); //Abro fichero
    if(fichero.is_open()){
        std::string line;

        while( getline(fichero, line)){
            allText += line; //Inserto todas las lineas en un string
        }
        fichero.close();
    }

    json = allText.c_str(); //meter string a json

    //RAPIDJSON
    Document document; //Creacion de documento para rapidJSON

    int contDoorIn = 0; //Se necesita para que el array no se sobreescriba
    int contAmmoIn = 0; //Se necesita para que el array no se sobreescriba
    uint8_t contDoorRotate = 0;

    //RECORRIDO
    if (document.Parse(json).HasParseError() == false) //coger el json y ver si es correcto
    {
        const Value& levels = document["levels"]; //Referencia a todos los "levels"
        //cout << "TAMAÑO DE LEVELS = " << levels.Size() << endl;
        for(size_t i=0; i < levels.Size(); i++){

            //const int levelid =  levels[i]["level-id"].GetInt();
            //cout << "LEVEL-ID = " << levelid << endl;
            const Value& se = levels[i]["static-elements"]; //Referencia a todos los "static-elements";
            //cout << "TAMAÑO DE SE = " << se.Size() << endl;
            for(size_t j=0; j < se.Size(); j++){

                const Value& e = se[j]; //Recorrer cada "element"
                std::string id = e["element-id"].GetString();
                int tx = e["position"]["x"].GetDouble();    int ty = e["position"]["y"].GetDouble();    int tz = (-1)* e["position"]["z"].GetDouble();
                int rx = e["rotation"]["x"].GetDouble();    int ry = e["rotation"]["y"].GetDouble();    int rz = e["rotation"]["z"].GetDouble();
                //cout << e["element-id"].GetString() << endl;
                //cout << "pos(" << tx << "," << ty << "," << tz << ") ; rot(" <<  rx << ":" <<  ry << ":" <<  rz << ")"<< endl;

                //WALLS
                TTag2Wall *next = mappingWall;
                while(next->tag != "0"){
                    if(id==next->tag){
                        walls[numWalls] = GEInstance->createScenaryElement(next->model, "unityPared");
                        walls[numWalls]->setRotation(dwe::vec3f(rx,ry,rz));
                        walls[numWalls]->setPosition(dwe::vec3f(tx,ty,tz));
                        numWalls++;
                       // wall->setLevelId(levelid);
                    };
                    ++next;
                }
                //FLOORS
                TTag2Floor *nextF = mappingFloor;
                while(nextF->tag != "0"){
                        if(id==nextF->tag){
                            floors[numFloors] = GEInstance->createFloor(nextF->model, "unitySuelo_Hall");
                            floors[numFloors]->setRotation(dwe::vec3f(rx,ry,rz));
                            floors[numFloors]->setPosition(dwe::vec3f(tx,ty,tz));
                            numFloors++;
                        }
                    ++nextF;
                }

            }


            //CONSUMABLES
            const Value& ce = levels[i]["initial-consumable"]; //Referencia a todos los "static-elements";
            for(size_t j=0; j < ce.Size(); j++){

                const Value& e = ce[j]; //Recorrer cada "element"
                std::string id = e["element-id"].GetString();
                int tx = e["position"]["x"].GetDouble();    int ty = e["position"]["y"].GetDouble();    int tz = (-1)* e["position"]["z"].GetDouble();
                if(id=="Bullets"){
                    s->createAmmoGun(tx, ty, tz);
                    ++contAmmoIn;
                }
            }



            //DOORS
            const Value& de = levels[i]["initial-entity"]; //Referencia a todos los "static-elements";
            for(size_t j=0; j < de.Size(); j++){

                const Value& e = de[j]; //Recorrer cada "element"
                std::string id = e["element-id"].GetString();
                int tx = e["position"]["x"].GetDouble();    int ty = e["position"]["y"].GetDouble();    int tz = (-1)* e["position"]["z"].GetDouble();
                // SOolo se utiliza rotacion en eje Y    int rx = e["rotation"]["x"].GetDouble();    int rz = e["rotation"]["z"].GetDouble();
                int ry = e["rotation"]["y"].GetDouble();
                uint8_t face = ry / 90; // 0->0, 90->1, 180->2, 270->3
                if(id=="Door"){
                    entities[contDoorIn]=GEInstance->createDoor(face, true, tx, ty, tz);
                    ++contDoorIn;
                }else if(id=="DoorRotate"){ // Puerta giratoria
                    entitiesDoorRotate[contDoorRotate]=GEInstance->createDoorRotate(face, true, tx, ty, tz);
                    ++contDoorRotate;/*/
                    entities[contDoorIn]=GEInstance->createDoor(face, true, tx, ty, tz);
                    ++contDoorIn;*/
                }
            }


        }
        // Generadores
        generator[0]=GEInstance->createGenerator(0, false, -350, 24, -300); // 1 Derecha Habitaciones
        generator[0]->setRotation(dwe::vec3f(0, 180, 0));
        generator[1]=GEInstance->createGenerator(1, false, -750, 24, -280); // 2 Izquierda
        generator[2]=GEInstance->createGenerator(2, false, -690, 24, -470); // 3 Arriba Mother

        // Asignamos puertas a generadores
        Entity **sector = new Entity*[1];
        ((Door*)entities[5])->setInactive();
        sector[0]=entities[5];
        generator[0]->setSector(sector, 1);
        ((Door*)entities[4])->setInactive();
        sector[0]=entities[4];
        generator[1]->setSector(sector, 1);
        sector = new Entity*[2];((Door*)entities[4])->setInactive();
        ((Door*)entities[32])->setInactive();
        ((Door*)entities[33])->setInactive();
        sector[0]=entities[32]; //32
        sector[1]=entities[33]; //33
        generator[2]->setSector(sector, 2);

        // ENVIRONMENT ELEMENTS
        /*nvElements[0] = GEInstance->createScenaryElement("environment_elements/mesahall", "");
        envElements[0]->setPosition(dwe::vec3f(-7, 0, 287));*/
        envElements[0] = GEInstance->createScenaryElement("environment_elements/cama", "environment_elements/cama");
        envElements[0]->setPosition(dwe::vec3f(50, 0, 100));
        envElements[1] = GEInstance->createScenaryElement("environment_elements/especimen", "environment_elements/especimen");
        envElements[1]->setPosition(dwe::vec3f(345, 0, -445));
        envElements[1]->setRotation(dwe::vec3f(0, -30, 0));
        envElements[2] = GEInstance->createScenaryElement("environment_elements/especimen", "environment_elements/especimen");
        envElements[2]->setPosition(dwe::vec3f(345, 0, -365));
        envElements[2]->setRotation(dwe::vec3f(0, -45, 0));
        envElements[3] = GEInstance->createScenaryElement("environment_elements/camilla", "environment_elements/camilla");
        envElements[3]->setPosition(dwe::vec3f(50, 0, 200));
        envElements[4] = GEInstance->createScenaryElement("environment_elements/camadormir", "environment_elements/camadormir");
        envElements[4]->setPosition(dwe::vec3f(745, 0, 835));
        //envElements[4]->setRotation(dwe::vec3f(0, -90, 0)); // No se gira la hitbox
        envElements[5] = GEInstance->createScenaryElement("environment_elements/camadormir", "environment_elements/camadormir");
        envElements[5]->setPosition(dwe::vec3f(1148, 0, 835));
        //envElements[5]->setRotation(dwe::vec3f(0, -90, 0));

        envElements[6] = GEInstance->createScenaryElement("environment_elements/armario", "environment_elements/armario");
        envElements[6]->setPosition(dwe::vec3f(50, 0, 300));

        // Armas
        s->createCShotgun(0, 10, -20);
        s->createCRifle(20, 10, -20);

    }
    GEInstance->push();
}

void LoadMap::Update(){
    if(GEInstance->receiver.isKeyDown(KEY_KEY_C) && !cheats){
        for(int cont=0; cont<NUM_DOORS; cont++){
            ((Door*)entities[cont])->setActive();
        }
        cout<<"CHEAT PUERTAS ABIERTAS"<<endl;
        cheats=true;
    }

    for(uint8_t i=0; i < NUM_MAP_DOORROTATE; i++)
        entitiesDoorRotate[i]->update();  // TODOjoint
    //Scene::updateConsumables(mainPlayer);
}

void LoadMap::Destroy(){
    for(int i=0; i<NUM_WALLS; i++){
        delete walls[i];
    }
    numWalls=0;
    for(int i=0; i<NUM_FLOORS; i++){
        delete floors[i];
    }
    for(int i=0; i<NUM_DOORS; i++){
        delete entities[i];
    }
    for(int i=0; i<NUM_ENVIRONMENT_ELEMENTS; i++){
        delete envElements[i];
    }
    for(int i=0; i<3; i++){
        delete generator[i];
    }
}

LoadMap::~LoadMap()
{
    if(numWalls)
        Destroy();
}

LoadMap* LoadMap::getInstance()
{
  static LoadMap instance;
  return &instance;
}

