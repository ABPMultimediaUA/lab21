#include "GSDead.h"
#include "GSMainMenu.h"
#include "GSIngame.h"
#include "NetGame.h"
#include "Scene.h"
#include "LoadMap.h"
#include "WorldInstance.h"

#include <iostream>

using namespace std;

GSDead::GSDead(){

}

GSDead* GSDead::getInstance()
{
  static GSDead instance;

  return &instance;
}


void GSDead::Render(){

}

void GSDead::HandleEvents(){

}

void GSDead::Update(){
    cout<<"MUERTO"<<endl;
    NetInstance->close();
    Game::getInstance()->ChangeState(GSMainMenu::getInstance());
    Scene::Instance()->Destroy();
    LoadMap::getInstance()->Destroy();
    //World->Destroy();
}

GSDead::~GSDead(){}
