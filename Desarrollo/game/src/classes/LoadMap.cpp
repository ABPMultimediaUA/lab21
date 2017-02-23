#include "LoadMap.h"
#include "GraphicsEngine.h"
#include "ScenaryElement.h"
#include <fstream> //Lectura de ficheros
#include <document.h> //ES UN .H de rapidJSON
using namespace rapidjson;

LoadMap::LoadMap()
{

    suelo = GEInstance->createNode("media/suelo");
    suelo->setPosition(dwe::vec3f(0,0,0));


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

    //THE WALLS
    if (document.Parse(json).HasParseError() == false) //coger el json y ver si es correcto
    {
        const Value& levels = document["levels"]; //Referencia a todos los "levels"
        cout << "TAMAÑO DE LEVELS = " << levels.Size() << endl;
        for(int i=0; i < levels.Size(); i++){
            const Value& se = levels[i]["static-elements"]; //Referencia a todos los "static-elements";
            cout << "TAMAÑO DE SE = " << se.Size() << endl;
            for(int j=0; j < se.Size(); j++){

                const Value& e = se[j]; //Recorrer cada "element"
                std::string id = e["element-id"].GetString();
                int tx = e["position"]["x"].GetDouble();
                int ty = e["position"]["y"].GetDouble();
                int tz = e["position"]["z"].GetDouble();
                int rx = e["rotation"]["x"].GetDouble();
                int ry = e["rotation"]["y"].GetDouble();
                int rz = e["rotation"]["z"].GetDouble();

                cout << e["element-id"].GetString() << endl;
                cout << "pos(" << tx << "," << ty << "," << tz << ") ; rot(" <<  rx << ":" <<  ry << ":" <<  rz << ")"<< endl;

                //cout << e["position"]["x"].GetDouble() << endl;

                if(id=="Wall_01"){
                    ScenaryElement* wall = GEInstance->createWall("media/unityPared01");
                    wall->setRotation(dwe::vec3f(rx,ry,rz));
                    wall->setPosition(dwe::vec3f(tx,ty,tz));
                }else if(id=="Wall_02"){
                    ScenaryElement* wall = GEInstance->createWall("media/unityPared02");
                    wall->setRotation(dwe::vec3f(rx,ry,rz));
                    wall->setPosition(dwe::vec3f(tx,ty,tz));
                }else if(id=="Wall_01_50m"){
                    ScenaryElement* wall = GEInstance->createWall("media/unityPared01_50m");
                    wall->setRotation(dwe::vec3f(rx,ry,rz));
                    wall->setPosition(dwe::vec3f(tx,ty,tz));
                }else if(id=="Wall_01_100m"){
                    ScenaryElement* wall = GEInstance->createWall("media/unityPared01_100m");
                    wall->setRotation(dwe::vec3f(rx,ry,rz));
                    wall->setPosition(dwe::vec3f(tx,ty,tz));
                }else if(id=="Wall_01_200m"){
                    ScenaryElement* wall = GEInstance->createWall("media/unityPared01_200m");
                    wall->setRotation(dwe::vec3f(rx,ry,rz));
                    wall->setPosition(dwe::vec3f(tx,ty,tz));
                }else if(id=="Wall_01_300m"){
                    ScenaryElement* wall = GEInstance->createWall("media/unityPared01_300m");
                    wall->setRotation(dwe::vec3f(rx,ry,rz));
                    wall->setPosition(dwe::vec3f(tx,ty,tz));
                }
            }

        }
    }

}

LoadMap::~LoadMap()
{
    delete suelo;
    delete wall;
}

LoadMap* LoadMap::getInstance()
{
  static LoadMap instance;
  return &instance;
}

