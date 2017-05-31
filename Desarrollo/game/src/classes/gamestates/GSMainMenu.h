#ifndef GSMAINMENU_H
#define GSMAINMENU_H
#include <sstream>

#include "GState.h"

#include <TGUI/TGUI.hpp>

namespace dwe
{
    class Button;
    class Background;
    class Sprite;
    class Slider;
}

class GSMainMenu : public GState{
public:
    GSMainMenu();
    ~GSMainMenu();
    void HandleEvents();
    void Update();
    void Render();
    void SetPage(int n);
    void UpdateLobbys();
    void UpdateServers();
    static GSMainMenu* getInstance();

private:
    static const int _margin    = 40;
    static const int _marginTop = 80;

    int page;
    int mousePosX, mousePosY;
    bool menuInfo; // Mostrar info de los menus
    bool m_clickPermission;
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
    dwe::Background *menuBackground;

    dwe::Sprite *menuMain;
    dwe::Sprite *menuBottom;

    dwe::Button *playAloneButton;
    dwe::Button *playOnlineButton;
    dwe::Button *creditsButton;
    dwe::Button *optionsButton;
    dwe::Button *exitButton;
    dwe::Button *backButton;
    dwe::Button *createLobbyButton;

    tgui::ComboBox::Ptr cbShadows;
    tgui::CheckBox::Ptr cbxFullscreen;
    tgui::CheckBox::Ptr cbxVSync;
    tgui::ComboBox::Ptr cbResolution;

    dwe::Button *auxButton; // No hacer delete, se borra al borrar los vectores de abajo

    std::vector<dwe::Button>* serversButtons; // Falta delete
    std::vector<dwe::Button>* lobbysButtons; // Falta delete
    /**/

    void grabarFicheroOpciones();

};

#endif // GSMAINMENU_H
