#ifndef GSMAINMENU_H
#define GSMAINMENU_H
#include <sstream>

#include "GState.h"

namespace dwe
{
    class Button;
    class Background;
    class Achievement;
}

class GSMainMenu : public GState{
public:
    GSMainMenu();
    ~GSMainMenu();
    bool buttonCheck(dwe::Button *b);
    void HandleEvents();
    void Update();
    void Render();
    void SetPage(int n);
    void UpdateLobbys();
    static GSMainMenu* getInstance();

private:
    int page;
    int mousePosX, mousePosY;
    bool menuInfo; // Mostrar info de los menus
    bool enterNet;
    bool serverSelection; // Servidor elegido
    bool serverInfo;
    bool lobbySelection; // Lobby elegida

    std::vector<std::string>* gamesIP;
    std::string type;
    std::string ip;
    std::string lobby;

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
    dwe::Button *backButton;

    dwe::Button *auxButton;

    std::vector<dwe::Button>* serversButtons;
    std::vector<dwe::Button>* lobbysButtons;

    dwe::Button *createLobbyButton;
    /**/
};

#endif // GSMAINMENU_H
