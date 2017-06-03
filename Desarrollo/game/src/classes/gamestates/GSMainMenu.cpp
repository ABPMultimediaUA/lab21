#include "GSMainMenu.h"
#include "GSIngame.h"
#include "Scene.h"
#include "NetGame.h"
#include <unistd.h>
#include <sstream>
#include "AudioEngine.h"
#include "GUI.h"
#include "LoadingScreen.h"

#include <iostream>
#include <fstream>

using namespace std;

const int GSMainMenu::_margin    = 40;
const int GSMainMenu::_marginTop = 80;

GSMainMenu::GSMainMenu(){
    page = 0;
    lobby = -1;
    menuInfo = false;
    m_clickPermission = false;
    enterNet = false;
    serverSelection = false;
    serverInfo = false;
    lobbySelection = false;
    updatedLobbys = false;

    /**Fondos**/
    menuBackground = new dwe::Background("menuBackground");

    /**Decoracion**/
    menuMain = new dwe::Sprite("menutop", _margin, _marginTop);
    menuBottom = new dwe::Sprite("menubottom", 0, 0);  // La posición se pone al dibujar

    /**Botones**/
    playAloneButton = new dwe::Button("Play Alone", _margin+66, _marginTop+80, true);
    playOnlineButton = new dwe::Button("Play Online", _margin+66, _marginTop+130, true);
    optionsButton = new dwe::Button("Options", _margin+66, _marginTop+180, true);
    creditsButton = new dwe::Button("Credits", _margin+66, _marginTop+230, true);
    exitButton = new dwe::Button("Exit", _margin+66, _marginTop+280, true);
    backButton = new dwe::Button("Back", 600, 500, false);
    serversButtons = new std::vector<dwe::Button>;
    lobbysButtons = new std::vector<dwe::Button>;
    createLobbyButton = new dwe::Button("Create lobby", _margin+66, _marginTop+280, false);

    tgui::Theme::Ptr theme = tgui::Theme::create("media/gui/Black.txt");

    cbShadows = theme->load("ComboBox");
    cbShadows->addItem("Sin sombras",   "0");
    cbShadows->addItem("Calidad baja",  "1");
    cbShadows->addItem("Calidad media", "2");
    cbShadows->addItem("Calidad alta",  "3");
    cbShadows->setPosition(tgui::Layout2d(40, 80));
    GEInstance->addGUI(cbShadows, "Shadows");

    cbxFullscreen = theme->load("CheckBox");
    cbxFullscreen->setText("Pantalla completa");
    cbxFullscreen->setPosition(tgui::Layout2d(40, 135));
    GEInstance->addGUI(cbxFullscreen, "Fullscreen");

    cbxVSync = theme->load("CheckBox");
    cbxVSync->setText("Activar VSync");
    cbxVSync->setPosition(tgui::Layout2d(40, 175));
    GEInstance->addGUI(cbxVSync, "VSync");

    cbResolution = theme->load("ComboBox");
    cbResolution->addItem("1024x576",  "0");
    cbResolution->addItem("1366x768",  "1");
    cbResolution->addItem("1920x1080", "2");
    cbResolution->setPosition(tgui::Layout2d(40, 210));
    GEInstance->addGUI(cbResolution, "Resolution");

    Init();
}

GSMainMenu* GSMainMenu::getInstance()
{
    static GSMainMenu instance;
    return &instance;
}


void GSMainMenu::Render(){
    if(page==0){
        if(!menuInfo){
            // Menu Principal
            menuInfo=true;
        }
        menuBackground->draw();
        playAloneButton->draw();
        playOnlineButton->draw();
        creditsButton->draw();
        optionsButton->draw();
        exitButton->draw();
        menuMain->draw();
        menuBottom->SetPosition(_margin,_marginTop+310);
        menuBottom->draw();
    }else if(page==1){
        if(!menuInfo){
            // Menu Jugar Online: aparecera lista de servidores. Crear lobby
            menuInfo=true;
        }
        menuBackground->draw();
        for(unsigned int i=0; i<serversButtons->size(); i++){
            serversButtons->at(i).draw();
        }
        backButton->draw();
    }else if(page==4){
        if(!menuInfo){
            // Seleccionar Lobby"<<endl;
            menuInfo=true;
        }
        menuBackground->draw();
        createLobbyButton->draw();
        for(unsigned int i=0; i<lobbysButtons->size(); i++){
            lobbysButtons->at(i).draw();
        }
        backButton->draw();
    }else if(page==2){
        if(!menuInfo){
            cout<<"/**************************************************/"<<endl;
            cout<<"Creditos"<<endl;
            menuInfo=true;
        }
        menuBackground->draw();
        backButton->draw();
    }else if(page==3){
        if(!menuInfo){
            cout<<"/**************************************************/"<<endl;
            cout<<"Menu Opciones"<<endl;
            cout<<"Aqui se modificaran las opciones de juego"<<endl;
            menuInfo=true;
        }
        menuBackground->draw();
        backButton->draw();

        GEInstance->drawGUI();
    }
}

void GSMainMenu::SetPage(int n){
    page = n;
}

void GSMainMenu::HandleEvents(){
    //Control cerrado de ventana
    if(GEInstance->getWindowClose())
        Game::getInstance()->setRunning(false);
    /***************************************************************************************/
    if(!m_clickPermission && GEInstance->receiver.isLeftButtonReleased()){
        m_clickPermission = true;
    }
    if(m_clickPermission)
    {
        switch(page){
        case 0: if(playAloneButton->buttonCheck(mousePosX, mousePosY) || GEInstance->receiver.isKeyDown(KEY_KEY_1))
                {
                    AEInstance->StopAllSounds();
                    NetInstance->open(false);  // Inicializar motor de red
                    menuInfo=false;
                    m_clickPermission=false;
                    grabarFicheroOpciones();
                    Game::getInstance()->ChangeState(GSIngame::getInstance());
                }
                else if(playOnlineButton->buttonCheck(mousePosX, mousePosY) || GEInstance->receiver.isKeyDown(KEY_KEY_2))
                {
                    type="2";
                    enterNet=true;
                    page=1;
                    menuInfo=false;
                    m_clickPermission=false;
                }
                else if(creditsButton->buttonCheck(mousePosX, mousePosY))
                {
                    page=2;
                    menuInfo=false;
                    m_clickPermission=false;
                }
                else if(optionsButton->buttonCheck(mousePosX, mousePosY))
                {
                    page=3;
                    menuInfo=false;
                    m_clickPermission=false;
                }
                else if(exitButton->buttonCheck(mousePosX, mousePosY))
                {
                    Game::getInstance()->setRunning(false);
                }
                break;
        case 1: for(size_t i=0; i<serversButtons->size(); i++)
                {
                    if(!serverSelection && serversButtons->at(i).buttonCheck(mousePosX, mousePosY))
                    {
                        std::stringstream ss;
                        std::string s;
                        ss << i;
                        s = ss.str();
                        page=4;
                        ip=s;
                        serverSelection=true;
                        NetInstance->connectToServer(atoi(ip.c_str()));
                        menuInfo=false;
                        m_clickPermission=false;
                    }
                }
                if(backButton->buttonCheck(mousePosX, mousePosY))
                {
                    page=0;
                    menuInfo=false;
                    m_clickPermission=false;
                }
                break;
        case 4: for(size_t i=0; i<lobbysButtons->size(); i++)
                {
                    if(!lobbySelection && lobbysButtons->at(i).buttonCheck(mousePosX, mousePosY))
                    {
                        std::stringstream ss;
                        std::string s;
                        ss << i+1;
                        s = ss.str();
                        lobby=s;
                        lobbySelection=true;
                        NetInstance->connectToGame(atoi(lobby.c_str()));
                        menuInfo=false;
                        m_clickPermission=false;
                    }
                }
                if(!lobbySelection)
                {
                    if(createLobbyButton->buttonCheck(mousePosX, mousePosY))
                    {
                        lobby="0";
                        lobbySelection=true;
                        NetInstance->connectToGame(atoi(lobby.c_str()));
                    }
                }
                if(backButton->buttonCheck(mousePosX, mousePosY))
                {
                    page=0; // 1 Pero al registrar en diferentes iteraciones el click pasa de lobby -> online -> mainMenu
                    menuInfo=false;
                    updatedLobbys=false;
                    m_clickPermission=false;
                }
                break;
        case 2: if(backButton->buttonCheck(mousePosX, mousePosY))
                {
                    page=0;
                    menuInfo=false;
                    m_clickPermission=false;
                }
                break;
        case 3: if(backButton->buttonCheck(mousePosX, mousePosY))
                {
                    page=0;
                    menuInfo=false;
                    m_clickPermission=false;
                }
                break;
        }
    }
}

void GSMainMenu::Update(){
    mousePosX=GEInstance->receiver.getCursorX();
    mousePosY=GEInstance->receiver.getCursorY();

	/****************************/
    if(enterNet && !NetInstance->getOpened()){
        NetInstance->open((type=="2"));  // Inicializar motor de red
        cout << "//\n// Buscando servidores ";
        if(NetInstance->searchForServers())
        {
            cout << "\n//\n//Servidores de partidas disponibles:\n";
            servers = NetInstance->getServers();

            UpdateServers();

            cout << "// Seleccione el numero de servidor de partidas [0] por defecto";
        }
    }

    if(enterNet && serverSelection && !serverInfo)
    {
        if (NetInstance->getConnectionFailed())
        {
            cout << "No se encuentra el servidor " << ip << ", se inicia el juego en modo 1 jugador.\n";
            cout << "Presione intro para continuar. ";
            //getchar();
        }
        else if (NetInstance->getConnectionRejected())
        {
            NetInstance->setMultiplayer(false);
            cout << "No se puede acceder a la partida seleccionada. Partida llena o empezada, se inicia el juego en modo 1 jugador.\n";
            cout << "Presione intro para continuar. ";
            //getchar();
        }
        else
        {
            // Esperamos por las partidas
            int i=0;
            while (i<5 && !NetInstance->getGamesSearched())
            {
                usleep(40000);
                NetInstance->update();
                i++;
            }

            cout << "//  (1) Crear una nueva partida.\n";

            gamesIP = NetInstance->getGamesIP();
            for(unsigned int j=0; j<gamesIP->size(); j++)
                cout << "//  ("<<j+2<<") Unirse a " << gamesIP->at(j) << "\n";

            cout << "// Selecciona una lobby: ";
        }
        serverInfo=true;
    }

    if(enterNet && serverSelection && serverInfo && lobbySelection)
    {
        grabarFicheroOpciones();
        menuInfo=false;
        enterNet=false;
        serverSelection=false;
        serverInfo=false;
        lobbySelection=false;
        updatedLobbys=false;
        page=0;
        Game::getInstance()->ChangeState(GSIngame::getInstance());
    }
    if(enterNet && serverSelection && !updatedLobbys)
        UpdateLobbys();
}

void GSMainMenu::UpdateLobbys()
{
    for(size_t i=0; i<gamesIP->size(); i++)
    {
        std::stringstream ss;
        std::string s;
        ss << i+1;
        s = ss.str();
        auxButton=new dwe::Button("Lobby "+s, GEInstance->get_screenWidth()*0.1, GEInstance->get_screenHeight()*0.35, true);
        lobbysButtons->push_back(*auxButton);
    }
    updatedLobbys=true;
}

void GSMainMenu::UpdateServers()
{
    for(unsigned int i=0; i<servers->size(); i++){
        cout << "//  ("<<i<<") " << servers->at(i) << "\n";
        std::stringstream ss;
        std::string s;
        ss << i+1;
        s = ss.str();
        auxButton = new dwe::Button("Server "+s, GEInstance->get_screenWidth()*0.1, GEInstance->get_screenHeight()*0.35, true);
        serversButtons->push_back(*auxButton);
    }
}

void GSMainMenu::grabarFicheroOpciones()
{
    ofstream fich("options.ini");
    if (fich.is_open())
    {
        std::string str = cbResolution->getSelectedItemId();
        fich << "res "      << str << "\n";

        str = cbShadows->getSelectedItemId();
        fich << "shadows "  << str << "\n";

        if (cbxFullscreen->isChecked())
            fich << "fullscreen 1\n";
        else
            fich << "fullscreen 0\n";

        if (cbxVSync->isChecked())
            fich << "vsync 1";
        else
            fich << "vsync 0";
        fich.close();
    }
}

void GSMainMenu::Init()
{
    // Leo fichero de opciones
    std::string shadows;
    std::string resolution;
    std::string fullscreen;
    std::string vsync;
    ifstream fich("options.ini");
    if (fich.is_open())
    {
        std::string name;
        std::string value;
        while (fich >> name >> value)
        {
            if (name=="res")
                resolution = value;
            else if (name=="fullscreen")
                fullscreen = value;
            else if (name=="vsync")
                vsync = value;
            else if (name=="shadows")
                shadows = value;
        }
        fich.close();
    }


    if (fullscreen == "1")
        cbxFullscreen->check();
    else
        cbxFullscreen->uncheck();

    if (vsync == "1")
        cbxVSync->check();
    else
        cbxVSync->uncheck();

    cbResolution->setSelectedItemById(resolution);
    cbShadows->setSelectedItemById(shadows);
}

GSMainMenu::~GSMainMenu(){
    /**Borrar Fondos**/
    delete menuBackground;
    /**Borrar Decoraciones**/
    delete menuMain;
    delete menuBottom;
    /**Borrar Botones**/
    delete playAloneButton;
    delete playOnlineButton;
    delete creditsButton;
    delete optionsButton;
    delete exitButton;
    delete backButton;
    delete createLobbyButton;
}
