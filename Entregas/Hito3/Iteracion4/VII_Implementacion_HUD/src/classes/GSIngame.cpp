#include "GSIngame.h"
#include "GSPause.h"
#include "GSDead.h"
#include "Hud.h"
#include <iostream>
using namespace std;

GSIngame::GSIngame(){

    hud = new Hud();
}

GSIngame* GSIngame::getInstance()
{
  static GSIngame instance;

  return &instance;
}

void GSIngame::Init(){
    page=0;
}

void GSIngame::Update(){

}

void GSIngame::HandleEvents(){
    /*if(GEInstance->receiver.isKeyDown(KEY_F10)){
        Game::getInstance()->ChangeState(GSPause::getInstance());
        m = false;
    }
    else if(GEInstance->receiver.isKeyDown(KEY_F9)){
        Game::getInstance()->ChangeState(GSDead::getInstance());
        m = false;
    }
    else if(GEInstance->receiver.isKeyDown(KEY_ESCAPE))
    {
        Game::getInstance()->setRunning(false);
        //GEInstance=0;
        //return 0;
    }*/
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::F9))
    {
        Game::getInstance()->ChangeState(GSDead::getInstance());
        m = false;
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::F10))
    {
        Game::getInstance()->ChangeState(GSPause::getInstance());
        m = false;
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    {
        Game::getInstance()->setRunning(false);
    }
}
void GSIngame::Render(){
    if(page==0){
        if(!m){
            cout<<"Ingame"<<endl;
            cout<<"Pulsa F9 para morir"<<endl;
            cout<<"Pulsa F10 para pausar el juego"<<endl;
            m=true;
        }
        GEInstance->draw();
        hud->draw();

    }
}
GSIngame::~GSIngame(){

    cout<<"He borrado el mapa"<<endl;

}
