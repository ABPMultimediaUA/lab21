#ifndef GSDEAD_H
#define GSDEAD_H

#include "GState.h"
#include "Game.h"

class GSDead : public GState{
public:
    GSDead();
    ~GSDead();
    void HandleEvents();
    void Update();
    void Render();
    void SetPage(int n);
    static GSDead* getInstance();

private:

};

#endif // GSDEAD_H
