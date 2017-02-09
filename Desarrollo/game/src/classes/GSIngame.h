#ifndef GSINGAME_H
#define GSINGAME_H

#include "GState.h"
#include "Game.h"

class GSIngame : public GState{
public:
    GSIngame();
    ~GSIngame();
    void HandleEvents();
    void Update();
    void Render();
    static GSIngame* getInstance();
private:
    int page;
    float timeStamp;
    float deltaTime;
};

#endif // GSINGAME_H
