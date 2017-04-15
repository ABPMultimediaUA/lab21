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
                        ScenaryElement* wall = GEInstance->createWall("media/"+next->model);
                        wall->setRotation(dwe::vec3f(rx,ry,rz));
                        wall->setPosition(dwe::vec3f(tx,ty,tz));
                       // wall->setLevelId(levelid);
                    };
                    ++next;
                }
                //FLOORS
                TTag2Floor *nextF = mappingFloor;
                while(nextF->tag != "0"){
                        if(id==nextF->tag){
                            suelo = GEInstance->createNode("media/"+nextF->model);
                            suelo->setRotation(dwe::vec3f(rx,ry,rz));
                            suelo->setPosition(dwe::vec3f(tx,ty,tz));
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
                    Scene* s = Scene::Instance();
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
                if(id=="Door"){
                        if(ry==0){
                            entities[contDoorIn]=GEInstance->createDoor(0, true, tx, ty, tz);
                        }else if(ry==90){
                            entities[contDoorIn]=GEInstance->createDoor(1, true, tx, ty, tz);
                        }else if(ry==180){
                            entities[contDoorIn]=GEInstance->createDoor(2, true, tx, ty, tz);
                        }else if(ry==270 || ry==-90){
                            entities[contDoorIn]=GEInstance->createDoor(3, true, tx, ty, tz);
                        }
                    //entities[contDoorIn]->setLevelId(levelid);
                    //doorTriggers[contDoorIn]=GEInstance->createTriggerDoor(tx, ty, tz);
                    ++contDoorIn;
                }
            }

        }

        // DEMO
        // Puertas MADRE
        entities[53]=GEInstance->createDoor(2, false, -50, 0, -100);
        //doorTriggers[53]=GEInstance->createTriggerDoor(-29, 0, -100);
        entities[54]=GEInstance->createDoor(0, false, 50, 0, -100);
        //doorTriggers[54]=GEInstance->createTriggerDoor(29, 0, -100);
        entities[55]=GEInstance->createDoor(2, true, -50, 0, -1895);
        //doorTriggers[55]=GEInstance->createTriggerDoor(-29, 0, -1895);
        entities[56]=GEInstance->createDoor(0, true, 50, 0, -1895);
        //doorTriggers[56]=GEInstance->createTriggerDoor(29, 0, -1895);

        ((Door*)entities[2])->setInactive();
        ((Door*)entities[11])->setInactive();
        ((Door*)entities[12])->setInactive();
        ((Door*)entities[51])->setInactive();
        ((Door*)entities[52])->setInactive();

        // Generadores
        generator[0]=GEInstance->createGenerator(0, false, -350, 24, -300); // 1 Derecha Habitaciones
        //generatorTriggers[0]=GEInstance->createTriggerGenerator(-360, 0, -300);
        generator[0]->setRotation(dwe::vec3f(0, 180, 0));
        generator[1]=GEInstance->createGenerator(1, false, -745, 24, -300); // 2 Izquierda
        //generatorTriggers[1]=GEInstance->createTriggerGenerator(-725, 0, -300);
        generator[2]=GEInstance->createGenerator(2, false, -680, 24, -491); // 3 Arriba Mother
        //generatorTriggers[2]=GEInstance->createTriggerGenerator(-660, 0, -491);

        // Asignamos puertas a generadores
        Entity **sector = new Entity*[1];
        ((Door*)entities[5])->setInactive();
        sector[0]=entities[5];
        generator[0]->setSector(sector, 1);
        ((Door*)entities[4])->setInactive();
        sector[0]=entities[4];
        generator[1]->setSector(sector, 1);
        sector = new Entity*[2];
        sector[0]=entities[53];
        sector[1]=entities[54];
        generator[2]->setSector(sector, 2);

        ////////// HACIENDO PRUEBAS CON OTRO TIPO DE BALAS
        //SHOTGUN BULLETS
        for(int i=0; i<1; i++){
            Scene* s = Scene::Instance();
            s->createCShotgun(0, 10, -20*i);
        }
        //RIFLE BULLETS
        for(int i=0; i<1; i++){
            Scene* s = Scene::Instance();
            s->createCRifle(20, 10, -20*i);
        }

    }
    GEInstance->push();
}

void LoadMap::Update(){
    /*for(int cont=0; cont<NUM_MAP_ENTITIES2; cont++){
        entities[cont]->update();
        doorTriggers[cont]->update(entities[cont]);
    }
    for(int cont=0; cont<3; cont++){
        generatorTriggers[cont]->update(generator[cont]);
    }
    if(GEInstance->receiver.isKeyDown(KEY_KEY_C) && !cheats){
        for(int cont=0; cont<NUM_MAP_ENTITIES2; cont++){
            ((Door*)entities[cont])->setActive();
        }
        cout<<"CHEAT PUERTAS ABIERTAS"<<endl;
        cheats=true;
    }

    //Scene::updateConsumables(mainPlayer);*/
}

void LoadMap::Destroy(){
     for(int i=0; i<NUM_MAP_ENTITIES2; i++){
        delete entities[i];
        delete doorTriggers[i];
    }
    for(int i=0; i<3; i++){
        delete generator[i];
        delete generatorTriggers[i];
    }
    delete[] generator;
    delete[] generatorTriggers;
    delete suelo; suelo=0;
    delete wall;
}

LoadMap::~LoadMap()
{
    if(suelo)
        Destroy();
}

LoadMap* LoadMap::getInstance()
{
  static LoadMap instance;
  return &instance;
}

