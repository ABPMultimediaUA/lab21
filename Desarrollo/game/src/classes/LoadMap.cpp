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
    if (document.Parse(json).HasParseError() == false) //coger el json y ver si es correcto
    {
        const Value& elements = document["elements"]; //Referencia a todos los "elements"
        for(int i=0; i < elements.Size(); i++){
            const Value& e = elements[i]; //Recorrer cada "element"
            cout << e["mesh"].GetString() << endl;
            ScenaryElement* wall20 = GEInstance->createWall(e["mesh"].GetString());
            wall20->setPosition(dwe::vec3f(200,   20, 80));
        }
    }



    wall01 = GEInstance->createWall("media/pared01");wall01->setPosition(dwe::vec3f(-35,   36.3, 135.9));
    wall02 = GEInstance->createWall("media/pared02");wall02->setPosition(dwe::vec3f(120.4, 36.3, 135.9));
    wall03 = GEInstance->createWall("media/pared03");wall03->setPosition(dwe::vec3f(42.7,  36.3, -132.2));
    wall04 = GEInstance->createWall("media/pared04");wall04->setPosition(dwe::vec3f(-84.9, 36.3, 2.2));
    wall05 = GEInstance->createWall("media/pared05");wall05->setPosition(dwe::vec3f(170.5, 36.3, 82.6));
    wall06 = GEInstance->createWall("media/pared06");wall06->setPosition(dwe::vec3f(170.5, 36.3, -76.7));
    wall07 = GEInstance->createWall("media/pared07");wall07->setPosition(dwe::vec3f(304.8, 36.3, -132.2));
    wall08 = GEInstance->createWall("media/pared08");wall08->setPosition(dwe::vec3f(304.8, 36.3, 133.8));
    wall09 = GEInstance->createWall("media/pared09");wall09->setPosition(dwe::vec3f(432.7, 36.3, 2.2));
    wall10 = GEInstance->createWall("media/pared10");wall10->setPosition(dwe::vec3f(-84.4, 36.3, 269.9));
    wall11 = GEInstance->createWall("media/pared11");wall11->setPosition(dwe::vec3f(170.8, 36.3, 269.6));
    wall12 = GEInstance->createWall("media/pared12");wall12->setPosition(dwe::vec3f(43.1,  36.3, 399.8));

}

LoadMap::~LoadMap()
{
    delete suelo;
    delete wall01;
    delete wall02;
    delete wall03;
    delete wall04;
    delete wall05;
    delete wall06;
    delete wall07;
    delete wall08;
    delete wall09;
    delete wall10;
    delete wall11;
    delete wall12;
}

LoadMap* LoadMap::getInstance()
{
  static LoadMap instance;

  return &instance;
}

