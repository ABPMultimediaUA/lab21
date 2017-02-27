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
        //cout << "TAMAÑO DE LEVELS = " << levels.Size() << endl;
        for(int i=0; i < levels.Size(); i++){
            const Value& se = levels[i]["static-elements"]; //Referencia a todos los "static-elements";
            //cout << "TAMAÑO DE SE = " << se.Size() << endl;
            for(int j=0; j < se.Size(); j++){

                const Value& e = se[j]; //Recorrer cada "element"
                std::string id = e["element-id"].GetString();
                int tx = e["position"]["x"].GetDouble();    int ty = e["position"]["y"].GetDouble();    int tz = e["position"]["z"].GetDouble();
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

            //DOORS
            const Value& de = levels[i]["initial-entity"]; //Referencia a todos los "static-elements";
            for(int j=0; j < de.Size(); j++){

                const Value& e = de[j]; //Recorrer cada "element"
                std::string id = e["element-id"].GetString();
                int tx = e["position"]["x"].GetDouble();    int ty = e["position"]["y"].GetDouble();    int tz = e["position"]["z"].GetDouble();
                int rx = e["rotation"]["x"].GetDouble();    int ry = e["rotation"]["y"].GetDouble();    int rz = e["rotation"]["z"].GetDouble();
                //cout << e["element-id"].GetString() << endl;
                //cout << "pos(" << tx << "," << ty << "," << tz << ") ; rot(" <<  rx << ":" <<  ry << ":" <<  rz << ")"<< endl;
                if(id=="Door"){
                    entities[j]=GEInstance->createDoor(0, true, tx, ty, tz);
                    doorTriggers[j]=GEInstance->createTriggerDoor(tx, ty, tz);
                }
            }

        }
    }
}

/*
    // Creacion de Mundo
    sector[0]=entities[1];



// Generadores
    entities[2]=GEInstance->createGenerator(0, false, -50, 0, -50); // false
    ((Generator*)entities[2])->setSector(sector, 1);

*/

void LoadMap::Update(){
    for(int cont=0; cont<NUM_ENTITIES2; cont++)
    {
        entities[cont]->update();
        doorTriggers[cont]->update(entities[cont]);
    }

}

void LoadMap::Destroy(){
     for(int i=0; i<NUM_ENTITIES; i++){
        delete entities[i];
    }
    delete[] entities;
     /*for(int i=0; i<1; i++){
        delete sector[i];
    }
    delete[] sector;*/
    for(int i=0; i<3; i++){
        delete doorTriggers[i];
    }
    delete[] doorTriggers;

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

