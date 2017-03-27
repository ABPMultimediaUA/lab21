#include "GSMainMenu.h"
#include "GSIngame.h"
#include "Scene.h"
#include "NetGame.h"
#include <unistd.h>
#include <iostream>

#include "GUI.h"

using namespace std;

GSMainMenu::GSMainMenu(){
    page = 0;
    m = false;
    a = false;

    /**Fondos**/
    menuPrincipalFondo = new dwe::Background("Principal");
    menuJugarOnlineFondo = new dwe::Background("JugarOnline");
    menuLogrosFondo = new dwe::Background("Logros");
    menuOpcionesFondo = new dwe::Background("Opciones");

    /**Botones**/
    playAloneButton = new dwe::Button("Play Alone", GEInstance->get_screenWidth()*0.1, GEInstance->get_screenHeight()*0.35);
    playOnlineButton = new dwe::Button("Play Online", GEInstance->get_screenWidth()*0.1, GEInstance->get_screenHeight()*0.43);
    achievementsButton = new dwe::Button("Achievements", GEInstance->get_screenWidth()*0.1, GEInstance->get_screenHeight()*0.51);
    optionsButton = new dwe::Button("Options", GEInstance->get_screenWidth()*0.1, GEInstance->get_screenHeight()*0.59);
    exitButton = new dwe::Button("Exit", GEInstance->get_screenWidth()*0.1, GEInstance->get_screenHeight()*0.67);
    back2mainMenuButton = new dwe::Button("Back", GEInstance->get_screenWidth()*0.8, GEInstance->get_screenHeight()*0.8);
}

GSMainMenu* GSMainMenu::getInstance()
{
    static GSMainMenu instance;
    return &instance;
}


void GSMainMenu::Render(){
    //GEInstance->clearWindow();
    if(page==0){
        if(!m){
            cout<<"/**************************************************/"<<endl;
            cout<<"Menu Principal"<<endl;
            m=true;
        }
        menuPrincipalFondo->draw();
        playAloneButton->draw();
        playOnlineButton->draw();
        achievementsButton->draw();
        optionsButton->draw();
        exitButton->draw();
    }else if(page==1){
        if(!m){
            cout<<"/**************************************************/"<<endl;
            cout<<"Menu Jugar Online"<<endl;
            cout<<"Aqui aparecera una lista de salas a las que unirte"<<endl; // Array de lobbys?
            cout<<"Podras crear tu propia sala"<<endl; // Crear Lobby
            m=true;
        }
        menuJugarOnlineFondo->draw();
        back2mainMenuButton->draw();
    }else if(page==2){
        if(!m){
            cout<<"/**************************************************/"<<endl;
            cout<<"Logros"<<endl;
            cout<<"Aqui aparecera una lista de logros conseguidos en el juego"<<endl;
            cout<<"Podras ver informacion de cada logro"<<endl;
            m=true;
        }
        menuLogrosFondo->draw();
        back2mainMenuButton->draw();
        //GEInstance->achievementsHandler.draw();
    }else if(page==3){
        if(!m){
            cout<<"/**************************************************/"<<endl;
            cout<<"Menu Opciones"<<endl;
            cout<<"Aqui se modificaran las opciones de juego"<<endl;
            m=true;
        }
        menuOpcionesFondo->draw();
        back2mainMenuButton->draw();
    }
    //GEInstance->displayWindow();
}

void GSMainMenu::SetPage(int n){
    page = n;
}

bool GSMainMenu::buttonCheck(dwe::Button *b)
{
    if(GEInstance->receiver.isLeftButtonPressed()
       &&(mousePosX>b->getXOrigin()
       && mousePosY>b->getYOrigin()
       && mousePosX<b->getWidth()
       && mousePosY<b->getHeight())
    ){return true;}
    return false;
}

void GSMainMenu::HandleEvents(){
    switch(page){
        case 0: if(buttonCheck(playAloneButton) || GEInstance->receiver.isKeyDown(KEY_KEY_1))
                {
                    type="1";
                    a=true;
                }
                else if(buttonCheck(playOnlineButton) || GEInstance->receiver.isKeyDown(KEY_KEY_2))
                {

                    type="2";
                    a=true;
                    //page=1;
                }
                else if(buttonCheck(achievementsButton))
                {
                    page=2;
                    m=false;
                }
                else if(buttonCheck(optionsButton))
                {
                    page=3;
                    m=false;
                }
                else if(buttonCheck(exitButton))
                {
                    Game::getInstance()->setRunning(false);
                }
                break;
        case 1: if(buttonCheck(back2mainMenuButton))
                {
                    page=0;
                    m=false;
                }
                break;
        case 2: if(buttonCheck(back2mainMenuButton))
                {
                    page=0;
                    m=false;
                }
                break;
        case 3: if(buttonCheck(back2mainMenuButton))
                {
                    page=0;
                    m=false;
                }
                break;
    }
}

void GSMainMenu::Update(){
    mousePosX=GEInstance->receiver.getCursorX();
    mousePosY=GEInstance->receiver.getCursorY();

    //GEInstance->achievementsHandler.update();

	/****************************/
    //getline(cin, type);
    if(a){

        NetInstance->open(Scene::Instance(), (type=="2"));  // Inicializar motor de red
        cout << "//\n// Buscando servidores ";
        if(NetInstance->searchForServers())
        {
            cout << "\n//\n//Servidores de partidas disponibles:\n";
            std::vector<std::string>* servers = NetInstance->getServers();

            for(unsigned int i=0; i<servers->size(); i++)
                cout << "//  ("<<i<<") " << servers->at(i) << "\n";

            cout << "// Seleccione el numero de servidor de partidas [0] por defecto]: ";

            std::string ip;
            getline(cin, ip);

            NetInstance->connectToServer(atoi(ip.c_str()));

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
                std::string seleccion;
                // Esperamos por las partidas
                int i=0;
                while (i<5 && !NetInstance->getGamesSearched())
                {
                    usleep(40000);
                    NetInstance->update();
                    i++;
                }

                cout << "//  (0) Crear una nueva partida.\n";

                std::vector<std::string>* gamesIP = NetInstance->getGamesIP();
                for(unsigned int j=0; j<gamesIP->size(); j++)
                    cout << "//  ("<<j+1<<") Unirse a " << gamesIP->at(j) << "\n";

                cout << "// Selecciona partida: ";
                getline(cin, seleccion);

                NetInstance->connectToGame(atoi(seleccion.c_str()));
            }
        }
        //GEInstance->clearWindow();
        Game::getInstance()->ChangeState(GSIngame::getInstance());
        GSIngame::getInstance()->Init();
        m=false;
        a=false;
    }
}

GSMainMenu::~GSMainMenu(){
    /**Borrar Fondos**/
    delete menuPrincipalFondo;
    delete menuJugarOnlineFondo;
    delete menuLogrosFondo;
    delete menuOpcionesFondo;
    /**Borrar Botones**/
    delete playAloneButton;
    delete playOnlineButton;
    delete achievementsButton;
    delete optionsButton;
    delete exitButton;
    delete back2mainMenuButton;
}
