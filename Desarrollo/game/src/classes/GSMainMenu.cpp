#include "GSMainMenu.h"
#include "GSIngame.h"
#include "Scene.h"
#include "NetGame.h"
#include <unistd.h>
#include <iostream>

using namespace std;



GSMainMenu::GSMainMenu(){
    page = 0;
    /*s32 buttonWidth = 128;
	s32 buttonHeight = 32;
	s32 screenDimW=800;
	s32 screenDimH=600;*/
    //playAloneButton = gui::addButton(core::rect<s32>((screenDimW/2)-(buttonWidth/2),(screenDimH-400)-buttonHeight, (screenDimW/2)+(buttonWidth/2),screenDimH-400));
}

GSMainMenu* GSMainMenu::getInstance()
{
  static GSMainMenu instance;

  return &instance;
}


void GSMainMenu::Render(){
    if(page==0){
        cout<<"Menu"<<endl;

    }
    if(page==1){
        page=0;
        Game::getInstance()->ChangeState(GSIngame::getInstance());
    }
}

void GSMainMenu::SetPage(int n){
    page = n;
}

void GSMainMenu::HandleEvents(){
    /*if(GEInstance->receiver.isKeyDown(KEY_SPACE)){
        Game::getInstance()->ChangeState(GSIngame::getInstance());
    }*/

}

void GSMainMenu::Update(){
    std::string type;

	/****************************/


    a = false;
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
    }

}
GSMainMenu::~GSMainMenu(){}
