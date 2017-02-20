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
    void MoveUp();
    void MoveDown();
    void SetPage(int n);
    static GSMainMenu* getInstance();

private:
    int page;
    bool a; // Controla cosas
    bool m;

    /***int selectedItemIndex;
    sf::Font *font;
    sf::Text *textSingleplayer;
    sf::Text *textMultiplayer;
    sf::Text *textOptions;
    sf::Text *textExit;
    sf::Texture *mainMenuBG
    sf::Texture *pBackground;
    sf::RectangleShape *bg;;***/
    //gui::IGUIButton* playAloneButton;
};

#endif // GSMAINMENU_H
