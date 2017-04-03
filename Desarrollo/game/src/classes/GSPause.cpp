#include "GSPause.h"
#include "GSIngame.h"
#include "GSMainMenu.h"
#include "Scene.h"
#include "LoadMap.h"
#include "NetGame.h"

#include <iostream>

using namespace std;

GSPause::GSPause(){
    page = 0;
    m = false;
    m_pausePermission = false;
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
    if(!m_pausePermission && GEInstance->receiver.isKeyUp(KEY_KEY_P)){
        m_pausePermission = true;
    }
    if(m_pausePermission && GEInstance->receiver.isKeyDown(KEY_KEY_P)){
        Game::getInstance()->ChangeState(GSIngame::getInstance());
        m = false;
        m_pausePermission = false;
    }
    if(GEInstance->receiver.isKeyDown(KEY_F9)){
        Game::getInstance()->ChangeState(GSMainMenu::getInstance());
        NetInstance->close();
        Game::getInstance()->ChangeState(GSMainMenu::getInstance());
        Scene::Instance()->Destroy();
        LoadMap::getInstance()->Destroy();
        m = false;
        m_pausePermission = false;
    }
}

void GSPause::Update(){
     //cin>>page;
}

GSPause::~GSPause(){}
