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
    void UpdateServers();
    static GSMainMenu* getInstance();

private:
    int page;
    int mousePosX, mousePosY;
    bool menuInfo; // Mostrar info de los menus
    bool enterNet;
    bool serverSelection; // Servidor elegido
    bool serverInfo;
    bool lobbySelection; // Lobby elegida
    bool updatedLobbys;

    std::vector<std::string>* gamesIP;
    std::vector<std::string>* servers;
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
    dwe::Button *createLobbyButton;

    dwe::Button *auxButton; // No hacer delete, se borra al borrar los vectores de abajo

    std::vector<dwe::Button>* serversButtons; // Falta delete
    std::vector<dwe::Button>* lobbysButtons; // Falta delete
    /**/
};

#endif // GSMAINMENU_H
