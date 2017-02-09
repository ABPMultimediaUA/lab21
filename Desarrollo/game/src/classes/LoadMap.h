#ifndef LOADMAP_H
#define LOADMAP_H

#include "GraphicsEngine.h"

class LoadMap {
    public:
        static LoadMap* getInstance();
        LoadMap();
        ~LoadMap();
    private:
        // Suelo
        dwe::Node* suelo;

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
