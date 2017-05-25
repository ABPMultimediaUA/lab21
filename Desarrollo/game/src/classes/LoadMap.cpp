#include "LoadMap.h"
#include "GraphicsEngine.h"
#include "ScenaryElement.h"
#include "LoadingScreen.h"
#include "NavGraphNode.h"
#include "NavGraphEdge.h"
#include "NetGame.h"
#include "ClippingObject.h"
#include "dwVectors.h"
#include "WorldInstance.h"
#include "Player.h"

#include <fstream> //Lectura de ficheros
#include <document.h> //ES UN .H de rapidJSON
using namespace rapidjson;

static const bool _clippingActive = true;

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
    numDoors = 0;
    numDoorsRotate = 0;
    numGenerators = 0;
    generatorID = 0;
    numEnvElements = 0;
    magnetKeyCount = 0;
    magnetKeyID = 0;

    cheats = false;

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

    //RECORRIDO
    if (document.Parse(json).HasParseError() == false) //coger el json y ver si es correcto
    {
        const Value& levels = document["levels"]; //Referencia a todos los "levels"
        for(size_t i=0; i < levels.Size()-1; i++){
            const Value& se = levels[i]["static-elements"]; //Referencia a todos los "static-elements";
            Drawable* parentNode = 0;
            for(size_t j=0; j < se.Size(); j++){

                const Value& e = se[j]; //Recorrer cada "element"
                std::string id = e["element-id"].GetString();
                int tx = e["position"]["x"].GetDouble();    int ty = e["position"]["y"].GetDouble();    int tz = (-1)* e["position"]["z"].GetDouble();
                int rx = e["rotation"]["x"].GetDouble();    int ry = e["rotation"]["y"].GetDouble();    int rz = e["rotation"]["z"].GetDouble();
                dwe::vec3f pos(tx, ty, tz);
                dwe::vec3f rot(rx, ry, rz);

                //FLOORS
                // En el json, el primer objeto es el suelo y solo hay 1 por sala
                TTag2Floor *nextF = mappingFloor;
                while (nextF->tag != "0")
                {
                    if(id==nextF->tag)
                    {
                        // Se crea un elemento de clipping por cada suelo, para dividir por salas
                        if (_clippingActive)
                        {
                            clippingObjects[numFloors] = GEInstance->createClippingObject();
                            clippingObjects[numFloors]->setPosClipping(dwe::vec3f(tx,ty,tz));
                            parentNode = clippingObjects[numFloors];
                        }

                        floors[numFloors] = GEInstance->createFloor(nextF->model, "unitySuelo_Hall", parentNode);
                        floors[numFloors]->setRotation(dwe::vec3f(rot));
                        floors[numFloors]->setPosition(dwe::vec3f(pos));

                        numFloors++;
                    }
                    ++nextF;
                }

                //WALLS
                TTag2Wall *next = mappingWall;
                while(next->tag != "0"){
                    if(id==next->tag){
                        walls[numWalls] = GEInstance->createScenaryElement(next->model, "unityPared", parentNode);
                        walls[numWalls]->setRotation(rot);
                        walls[numWalls]->setPosition(pos);
                        numWalls++;
                    }
                    ++next;
                }
                // GENERATORS
                if(id=="Generator"){
                    if(numGenerators==0)
                        generatorID=2;
                    else if(numGenerators==1)
                        generatorID=0;
                    else if(numGenerators==2)
                        generatorID=3;
                    else if(numGenerators==3)
                        generatorID=1;
                    generator[numGenerators]=GEInstance->createGenerator(generatorID, false, parentNode);
                    generator[numGenerators]->setRotation(rot);
                    generator[numGenerators]->setPosition(pos);
                    generator[numGenerators]->SetSensor();
                    numGenerators++;
                }

                static const std::string lugar[23] = {"Cama", "Especimen", "Camilla", "Lavabo", "WC", "CamaDormir", "Barril", "Caja", "Mesa", "MesaHall", "MesaHallObjetos", "Maceta", "Ingeniero", "BicicletaEstatica", "MaquinaCorrer", "MaquinaPesas", "MesaCocina1", "MesaCocina2", "MesaCocina3", "MesaComedor", "SillasComedor"};
                static const std::string cosa[23] = {"cama", "especimen", "camilla", "lavabo", "banyos", "camadormir", "barril", "box", "mesa", "mesahall", "mesahallobjetos", "maceta", "ingeniero", "bicicletaestatica", "maquinacorrer", "maquinapesas", "mesacocina1", "mesacocina2", "mesacocina3", "mesacomedor", "sillacomedor"};
                // ELEMENTOS DEL ENTORNO
                for(unsigned char i=0; i<23; i++){
                    if(id==lugar[i])  createScenaryElement(cosa[i].c_str(), pos, rot, parentNode);
                }

            }

            //CONSUMABLES
            const Value& ce = levels[i]["initial-consumable"]; //Referencia a todos los "static-elements";
            for(size_t j=0; j < ce.Size(); j++){

                const Value& e = ce[j]; //Recorrer cada "element"
                std::string id = e["element-id"].GetString();
                int tx = e["position"]["x"].GetDouble();    int ty = e["position"]["y"].GetDouble();    int tz = (-1)* e["position"]["z"].GetDouble();
                if(id=="Ammo"){
                    s->createAmmo(tx, ty, tz, parentNode);
                } else if(id=="Medkit"){
                    s->createMedkit(tx, ty, tz, parentNode);
                } else if(id=="Adrenalina"){
                    s->createSpeedBoost(tx, ty, tz, parentNode);
                } else if(id=="MagnetKey"){
                    magnetKeyID=4-magnetKeyCount;
                    s->createMagnetKey(magnetKeyID, tx, ty, tz, parentNode);
                    magnetKeyCount++;
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
                    entities[numDoors]=GEInstance->createDoor(face, true, tx, ty, tz, parentNode);
                    ++numDoors;
                }else if(id=="DoorRotate"){ // Puerta giratoria
                    entitiesDoorRotate[numDoorsRotate]=GEInstance->createDoorRotate(face, true, tx, ty, tz, parentNode);
                    ++numDoorsRotate;
                }
            }
        }
        // WAYPOINTS
        const Value& wa = levels[48]["Waypoints"];
        for(size_t j=0; j < wa.Size(); j++){
            const Value& e = wa[j]; //Recorrer cada "element"
            std::string id = e["element-id"].GetString();
            int tx = e["position"]["x"].GetDouble();  int tz = (-1)* e["position"]["z"].GetDouble();
            NavGraphNode node(j, dwe::vec2f(tx, tz));
            s->getNavGraph().addNode(node);
        }
        // ARISTAS
        ifstream edges("edges.txt");

        int a, b;
        while (edges >> a >> b)
        {
            NavGraphEdge edge(a,b, dwu::calculateDistance(s->getNavGraph().getNode(a).getPosition(), s->getNavGraph().getNode(b).getPosition()));
            s->getNavGraph().addEdge(edge);
        }

        // Asignamos puertas a generadores
        Entity **sector = new Entity*[1];
        ((Door*)entities[3])->setInactive();
        sector[0]=entities[3];
        generator[0]->setSector(sector, 1);
        ((Door*)entities[4])->setInactive();
        sector[0]=entities[4];
        generator[1]->setSector(sector, 1);
        ((Door*)entities[1])->setInactive();
        sector[0]=entities[1];
        generator[3]->setSector(sector, 1);
        sector = new Entity*[2];((Door*)entities[4])->setInactive();
        ((Door*)entities[27])->setInactive();
        ((Door*)entities[28])->setInactive();
        sector[0]=entities[27];
        sector[1]=entities[28];
        generator[2]->setSector(sector, 2);


        // Las armas se crean al iniciar partida en ingame

    }
    GEInstance->push();
}

void LoadMap::Update(){
    if(GEInstance->receiver.isKeyDown(KEY_KEY_C) && !cheats)
    {
        NetInstance->sendBroadcast(ID_CHEAT_DOOR_OPEN, 0);
        cheatDoorOpen();
    }

    for(uint8_t i=0; i < NUM_MAP_DOORROTATE; i++)
        entitiesDoorRotate[i]->update();

    if (_clippingActive)
        calculateClipping();


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
    for(uint8_t i=0; i<NUM_FLOORS; i++)
    {
        delete clippingObjects[i];
        clippingObjects[i] = 0;
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

void LoadMap::cheatDoorOpen()
{
    for(int cont=0; cont<NUM_DOORS; cont++){
        ((Door*)entities[cont])->setActive();
    }
    cout<<"CHEAT PUERTAS ABIERTAS"<<endl;
    cheats=true;
}

void LoadMap::calculateClipping()
{
    static const uint16_t _offsetClippingX = 400;
    static const uint16_t _offsetClippingZ = 400;
    dwe::vec3f posPlayer = World->getMainPlayer()->getPosition();
    for (uint16_t i=0; i<NUM_FLOORS; i++)
    {
        dwe::vec3f posClip = clippingObjects[i]->getPosClipping();
        bool activo = ((abs(posClip.x - posPlayer.x) < _offsetClippingX) || (abs(posClip.z - posPlayer.z) < _offsetClippingZ));
        clippingObjects[i]->setActive(activo);
    }
}

void LoadMap::createScenaryElement(const char* s, const dwe::vec3f &pos, const dwe::vec3f &rot, Drawable* parent)
{
    envElements[numEnvElements]=GEInstance->createScenaryElement("environment_elements/"+std::string(s), "environment_elements/"+std::string(s), parent);
    envElements[numEnvElements]->setRotation(rot);
    envElements[numEnvElements]->setPosition(pos);
    numEnvElements++;
}


void LoadMap::createConsumableWeapons()
{
    // Si utilizo dwe::vec3f me da un warning de necesitar c++11
    struct T3d {
        float x;
        float y;
        float z;
    };
    static const T3d posRifles[]  = { {30, 10, -20}, {30, 10, 20}, {30, 10, 40}, {30, 10, 60} };
    static const T3d posShotgun[] = { { 0, 10, -20}, { 0, 10, 20}, { 0, 10, 40}, { 0, 10, 60} };

    uint8_t num = NetInstance->getNumPlayerMates();
    for(uint8_t i=0; i<num; i++)
    {
        Scene::Instance()->createCShotgun(posShotgun[i].x, posShotgun[i].y, posShotgun[i].z);
        Scene::Instance()->createCRifle  (posRifles[i].x, posRifles[i].y, posRifles[i].z);
    }
}
