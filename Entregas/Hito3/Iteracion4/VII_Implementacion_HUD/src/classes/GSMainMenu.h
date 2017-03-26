#ifndef GSMAINMENU_H
#define GSMAINMENU_H

#include "GState.h"

class GSMainMenu : public GState{
public:
    GSMainMenu();
    ~GSMainMenu();
    void HandleEvents();
    void Update();
    void Render();
    void MoveUp();
    void MoveDown();
    void SetPage(int n);
    static GSMainMenu* getInstance();

private:
    int page;
    bool a; // Controla cosas
    bool m;

    /**/
    dwe::Background *menuPrincipalFondo;
    dwe::Background *menuJugarOnlineFondo;
    dwe::Background *menuLogrosFondo;
    dwe::Background *menuOpcionesFondo;

    dwe::Button *playAloneButton;
    dwe::Button *playOnlineButton;
    dwe::Button *achievementsButton;
    dwe::Button *optionsButton;
    dwe::Button *exitButton;
    /**/
};

#endif // GSMAINMENU_H
