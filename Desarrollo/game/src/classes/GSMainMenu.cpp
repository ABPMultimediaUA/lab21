#include "GSMainMenu.h"
#include "GSIngame.h"
#include "Scene.h"
#include "NetGame.h"
#include <unistd.h>
#include <iostream>

using namespace std;



GSMainMenu::GSMainMenu(){
    page = 0;
    m = false;
    a = false;
    /***font = new sf::Font();
    pBackground  = new sf::Texture();
    mainMenuBG = new sf::Texture();
    -cargar la textura de mainMenuBG-
    bg = new sf::RectangleShape();
    pBackground = mainMenuBG;
    bg->setSize(sf::Vector2f(1280,720));
    bg->setTexture(pBackground, true);

    -textos-
    textSingleplayer = new sf::Text();
    textSingleplayer->setFont(*font);
    textSingleplayer->setColor(sf::Color::Red);
    textSingleplayer->setString("Un jugador");
    textSingleplayer->setPosition(225,200);
    textSingleplayer->setCharacterSize(18);

    textMultiplayer = new sf::Text();
    textMultiplayer->setFont(*font);
    textMultiplayer->setColor(sf::Color::White);
    textMultiplayer->setString("Multijugador");
    textMultiplayer->setPosition(225,300);
    textMultiplayer->setCharacterSize(18);

    textOptions = new sf::Text();
    textOptions->setFont(*font);
    textOptions->setColor(sf::Color::White);
    textOptions->setString("Opciones");
    textOptions->setPosition(225,400);
    textOptions->setCharacterSize(18);

    textExit = new sf::Text();
    textExit->setFont(*font);
    textExit->setColor(sf::Color::White);
    textExit->setString("Salir");
    textExit->setPosition(225,500);
    textExit->setCharacterSize(18);

    selectedItemIndex = 0;
    ***/
}

GSMainMenu* GSMainMenu::getInstance()
{
    static GSMainMenu instance;
    return &instance;
}


void GSMainMenu::Render(){
    if(page==0){
        /***pBackground = menuPrincipalFondo;
        bg->setTexture(pBackground, true);***/
        if(!m){
            cout<<"Menu"<<endl;
            cout<<"Pulsa 1 para iniciar partida 1 jugador"<<endl;
            cout<<"Pulsa 2 para iniciar partida 2 jugadores"<<endl;
            //cout<<"Pulsa Escape para salir del juego"<<endl;
            m=true;
        }
    }
}

void GSMainMenu::SetPage(int n){
    page = n;
}

void GSMainMenu::HandleEvents(){

}

void GSMainMenu::Update(){
    std::string type;
	/****************************/
    //getline(cin, type);
    if(GEInstance->receiver.isKeyDown(KEY_KEY_1)){
        type=1;
        a = true;
    }
    if(GEInstance->receiver.isKeyDown(KEY_KEY_2)){
        type=2;
        a = true;
    }
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

        Game::getInstance()->ChangeState(GSIngame::getInstance());
        m=false;
        a=false;
    }

}
GSMainMenu::~GSMainMenu(){}
