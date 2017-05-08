#include "GSMainMenu.h"
#include "GSIngame.h"
#include "Scene.h"
#include "NetGame.h"
#include <unistd.h>
#include <iostream>
#include <sstream>
#include "AudioEngine.h"

#include "GUI.h"

using namespace std;

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
    mainMenuDecoration = new dwe::Sprite("mainMenuDecoration", GEInstance->get_screenWidth()*0.1-67, GEInstance->get_screenHeight()*0.25-7);

    /**Botones**/
    playAloneButton = new dwe::Button("Play Alone", GEInstance->get_screenWidth()*0.1, GEInstance->get_screenHeight()*0.35, true);
    playOnlineButton = new dwe::Button("Play Online", GEInstance->get_screenWidth()*0.1, GEInstance->get_screenHeight()*0.43, true);
    achievementsButton = new dwe::Button("Achievements", GEInstance->get_screenWidth()*0.1, GEInstance->get_screenHeight()*0.51, true);
    optionsButton = new dwe::Button("Options", GEInstance->get_screenWidth()*0.1, GEInstance->get_screenHeight()*0.59, true);
    exitButton = new dwe::Button("Exit", GEInstance->get_screenWidth()*0.1, GEInstance->get_screenHeight()*0.67, true);
    backButton = new dwe::Button("Back", GEInstance->get_screenWidth()*0.8, GEInstance->get_screenHeight()*0.8, false);
    serversButtons = new std::vector<dwe::Button>;
    lobbysButtons = new std::vector<dwe::Button>;
    createLobbyButton = new dwe::Button("Create lobby", GEInstance->get_screenWidth()*0.1, GEInstance->get_screenHeight()*0.8, false);
}

GSMainMenu* GSMainMenu::getInstance()
{
    static GSMainMenu instance;
    return &instance;
}


void GSMainMenu::Render(){
    //GEInstance->clearWindow();
    if(page==0){
        if(!menuInfo){
            cout<<"/**************************************************/"<<endl;
            cout<<"Menu Principal"<<endl;
            menuInfo=true;
        }
        menuBackground->draw();
        playAloneButton->draw();
        playOnlineButton->draw();
        achievementsButton->draw();
        optionsButton->draw();
        exitButton->draw();
        mainMenuDecoration->draw();
    }else if(page==1){
        if(!menuInfo){
            cout<<"/**************************************************/"<<endl;
            cout<<"Menu Jugar Online"<<endl;
            cout<<"Aqui aparecera una lista de servidores a los que unirte"<<endl; // Array de servers
            cout<<"Podras crear tu propia sala"<<endl; // Crear Lobby
            menuInfo=true;
        }
        menuBackground->draw();
        for(unsigned int i=0; i<serversButtons->size(); i++){
            serversButtons->at(i).draw();
        }
        backButton->draw();
    }else if(page==4){
        if(!menuInfo){
            cout<<"/**************************************************/"<<endl;
            cout<<"Menu Seleccionar Lobby"<<endl;
            cout<<"Aqui aparecera una lista de lobbys a las que unirte"<<endl; // Array de lobbys?
            cout<<"Podras crear tu propia sala"<<endl; // Crear Lobby
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
            cout<<"Logros"<<endl;
            cout<<"Aqui aparecera una lista de logros conseguidos en el juego"<<endl;
            cout<<"Podras ver informacion de cada logro"<<endl;
            menuInfo=true;
        }
        menuBackground->draw();
        backButton->draw();
        //GEInstance->achievementsHandler.draw();
    }else if(page==3){
        if(!menuInfo){
            cout<<"/**************************************************/"<<endl;
            cout<<"Menu Opciones"<<endl;
            cout<<"Aqui se modificaran las opciones de juego"<<endl;
            menuInfo=true;
        }
        menuBackground->draw();
        backButton->draw();
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
                    //AEInstance->Play2D("media/gamestarts.wav");
                    NetInstance->open(Scene::Instance(), false);  // Inicializar motor de red
                    menuInfo=false;
                    m_clickPermission=false;
                    Game::getInstance()->ChangeState(GSIngame::getInstance());
                    GSIngame::getInstance()->Init();
                }
                else if(playOnlineButton->buttonCheck(mousePosX, mousePosY) || GEInstance->receiver.isKeyDown(KEY_KEY_2))
                {
                    type="2";
                    enterNet=true;
                    page=1;
                    menuInfo=false;
                    m_clickPermission=false;
                }
                else if(achievementsButton->buttonCheck(mousePosX, mousePosY))
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
        case 1: for(int i=0; i<serversButtons->size(); i++)
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
        case 4: for(int i=0; i<lobbysButtons->size(); i++)
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

    //GEInstance->achievementsHandler.update();

	/****************************/
    if(enterNet && !NetInstance->getOpened()){
        NetInstance->open(Scene::Instance(), (type=="2"));  // Inicializar motor de red
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
        Game::getInstance()->ChangeState(GSIngame::getInstance());
        GSIngame::getInstance()->Init();
        menuInfo=false;
        enterNet=false;
        serverSelection=false;
        serverInfo=false;
        lobbySelection=false;
        updatedLobbys=false;
        page=0;
    }
    if(enterNet && serverSelection && !updatedLobbys)
        UpdateLobbys();
}

void GSMainMenu::UpdateLobbys()
{
    for(int i=0; i<gamesIP->size(); i++)
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

GSMainMenu::~GSMainMenu(){
    /**Borrar Fondos**/
    delete menuBackground;
    /**Borrar Decoraciones**/
    delete mainMenuDecoration;
    /**Borrar Botones**/
    delete playAloneButton;
    delete playOnlineButton;
    delete achievementsButton;
    delete optionsButton;
    delete exitButton;
    delete backButton;
    delete createLobbyButton;
}
