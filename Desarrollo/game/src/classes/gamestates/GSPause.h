#ifndef GSPAUSE_H
#define GSPAUSE_H

#include "GState.h"

namespace dwe
{
    class Button;
    class Background;
}

class GSPause : public GState{
public:
    GSPause();
    ~GSPause();
    bool buttonCheck(dwe::Button *b);
    void HandleEvents();
    void Update();
    void Render();
    void SetPage(int n);
    static GSPause* getInstance();
    void resumeGame();
    void backToMainMenu();

private:
    int page;
    int mousePosX, mousePosY;
    bool m;
    bool m_pausePermission; // Booleano para controlar el boton pausa
    bool m_clickPermission; // Control del click

    /****/
    dwe::Background *menuPausaFondo;

    dwe::Button *resumeGameButton;
    dwe::Button *helpOptionsButton;
    dwe::Button *exitToMainMenuButton;
};

#endif // GSPAUSE_H
