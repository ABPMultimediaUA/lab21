#include "GSPause.h"
#include "GSIngame.h"
#include "GSMainMenu.h"

#include <iostream>

using namespace std;

GSPause::GSPause(){
    page = 0;
    m = false;
}

GSPause* GSPause::getInstance()
{
  static GSPause instance;

  return &instance;
}


void GSPause::Render(){
    if(page==0){
        if(!m){
            cout<<"Pause"<<endl;
            cout<<"Pulsa P para volver al juego"<<endl;
            cout<<"Pulsa F9 para volver al menu"<<endl;
            m = true;
        }
    }
}

void GSPause::SetPage(int n){
    page = n;
}

void GSPause::HandleEvents(){
    /*if(GEInstance->receiver.isKeyDown(KEY_KEY_P)){
        Game::getInstance()->ChangeState(GSIngame::getInstance());
        m = false;
    }
    if(GEInstance->receiver.isKeyDown(KEY_F9)){
        Game::getInstance()->ChangeState(GSMainMenu::getInstance());
        NetInstance->close();
        Game::getInstance()->ChangeState(GSMainMenu::getInstance());
        Scene::Instance()->Destroy();
        LoadMap::getInstance()->Destroy();
        m = false;
    }*/
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::P))
    {
        Game::getInstance()->ChangeState(GSIngame::getInstance());
        m = false;
    }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::F9))
    {
        Game::getInstance()->ChangeState(GSMainMenu::getInstance());
        //NetInstance->close();
        //Scene::Instance()->Destroy();
        //LoadMap::getInstance()->Destroy();
        m = false;
    }
}

void GSPause::Update(){
     //cin>>page;
}
GSPause::~GSPause(){}
