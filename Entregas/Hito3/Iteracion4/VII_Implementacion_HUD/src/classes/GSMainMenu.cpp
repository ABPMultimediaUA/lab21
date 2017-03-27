#include "GSMainMenu.h"
#include "GSIngame.h"
#include "Scene.h"
//#include "NetGame.h"
#include <unistd.h>
#include <iostream>

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
    playAloneButton = new dwe::Button("Play Alone", SCREEN_WIDTH/2-300, SCREEN_HEIGHT/2-100);
    playOnlineButton = new dwe::Button("Play Online", SCREEN_WIDTH/2-300, SCREEN_HEIGHT/2-50);
    achievementsButton = new dwe::Button("Achievements", SCREEN_WIDTH/2-300, SCREEN_HEIGHT/2);
    optionsButton = new dwe::Button("Options", SCREEN_WIDTH/2-300, SCREEN_HEIGHT/2+50);
    exitButton = new dwe::Button("Exit", SCREEN_WIDTH/2-300, SCREEN_HEIGHT/2+100);
}

GSMainMenu* GSMainMenu::getInstance()
{
    static GSMainMenu instance;
    return &instance;
}


void GSMainMenu::Render(){

    if(page==0){
        if(!m){
            cout<<"/**************************************************/"<<endl;
            cout<<"Menu Principal"<<endl;
            cout<<"Pulsa 1 para iniciar partida 1 jugador"<<endl;
            cout<<"Pulsa 2 para iniciar partida online"<<endl;
            cout<<"Pulsa L para acceder a Logros"<<endl;
            cout<<"Pulsa O  para acceder a Opciones"<<endl;
            cout<<"Pulsa Escape para salir del juego"<<endl;
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
            cout<<"Aqui aparecera una lista de salas a las que unirte"<<endl;
            cout<<"Podras crear tu propia sala"<<endl;
            cout<<"Pulsa B para volver al Menu principal"<<endl;
            m=true;
        }
        menuJugarOnlineFondo->draw();
    }else if(page==2){
        if(!m){
            cout<<"/**************************************************/"<<endl;
            cout<<"Logros"<<endl;
            cout<<"Aqui aparecera una lista de logros conseguidos en el juego"<<endl;
            cout<<"Podras ver informacion de cada logro"<<endl;
            cout<<"Pulsa B para volver al Menu principal"<<endl;
            m=true;
        }
        menuLogrosFondo->draw();
    }else if(page==3){
        if(!m){
            cout<<"/**************************************************/"<<endl;
            cout<<"Menu Opciones"<<endl;
            cout<<"Aqui se modificaran las opciones de juego"<<endl;
            cout<<"Pulsa B para volver al Menu principal"<<endl;
            m=true;
        }
        menuOpcionesFondo->draw();
    }
}

void GSMainMenu::SetPage(int n){
    page = n;
}

void GSMainMenu::HandleEvents(){
    /*
    int mousePosX=sf::Mouse::getPosition().x;
    int mousePosY=sf::Mouse::getPosition().y;
    cout<<"X:"<<mousePosX<<" Y:"<<mousePosY<<endl;
    cout<<sf::Mouse::isButtonPressed(sf::Mouse::Left)<<endl;
    */
    /*sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)/*(GEInstance->receiver.isKeyDown(KEY_KEY_1))
                    sf::Mouse::isButtonPressed(sf::Mouse::Left) &&
                    (mousePosX>originX &&
                    mousePosY>originY &&
                    mousePosX<bWidth  &&
                    mousePosY<bHeight)*/
    switch(page){
        case 0: if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
                {
                    Game::getInstance()->ChangeState(GSIngame::getInstance());
                    GSIngame::getInstance()->Init();
                    m=false;
                    a=false;
                }
                else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
                {
                    page=1;
                    m=false;
                }
                else if(sf::Keyboard::isKeyPressed(sf::Keyboard::L))
                {
                    page=2;
                    m=false;
                }
                else if(sf::Keyboard::isKeyPressed(sf::Keyboard::O)/*(GEInstance->receiver.isKeyDown(KEY_KEY_O))*/)
                {
                    page=3;
                    m=false;
                }
                else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                {
                    Game::getInstance()->setRunning(false);
                }
                break;
        case 1: if(sf::Keyboard::isKeyPressed(sf::Keyboard::B)/*(GEInstance->receiver.isKeyDown(KEY_KEY_B))*/)
                {
                    page=0;
                    m=false;
                }
                break;
        case 2: if(sf::Keyboard::isKeyPressed(sf::Keyboard::B)/*(GEInstance->receiver.isKeyDown(KEY_KEY_B))*/)
                {
                    page=0;
                    m=false;
                }
                break;
        case 3: if(sf::Keyboard::isKeyPressed(sf::Keyboard::B)/*(GEInstance->receiver.isKeyDown(KEY_KEY_B))*/)
                {
                    page=0;
                    m=false;
                }
                break;
    }
}

void GSMainMenu::Update(){
	/****************************/
/*	std::string type;
    getline(cin, type);
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
        GSIngame::getInstance()->Init();
        cout<<"fidel"<<endl;
        m=false;
        a=false;
    }
*/
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
}

