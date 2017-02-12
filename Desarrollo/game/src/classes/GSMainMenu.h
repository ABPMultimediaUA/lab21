#ifndef GSMAINMENU_H
#define GSMAINMENU_H

#include "GState.h"
/**/
//#include <irrlicht.h>

//using namespace irr;
/***/

class GSMainMenu : public GState{
public:
    GSMainMenu();
    ~GSMainMenu();
    void HandleEvents();
    void Update();
    void Render();
    void SetPage(int n);
    static GSMainMenu* getInstance();

private:
    int page;
    bool a; // Controla cosas
    bool m;
    //gui::IGUIButton* playAloneButton;
};

#endif // GSMAINMENU_H
