#ifndef GSPAUSE_H
#define GSPAUSE_H

#include "GState.h"

class GSPause : public GState{
public:
    GSPause();
    ~GSPause();
    void HandleEvents();
    void Update();
    void Render();
    void SetPage(int n);
    static GSPause* getInstance();

private:
    int page;
    bool m;
    bool m_pausePermission; // Booleano para controlar el boton pausa
};

#endif // GSPAUSE_H
