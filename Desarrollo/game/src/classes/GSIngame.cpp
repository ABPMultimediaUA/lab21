#include "GSIngame.h"
#include "LoadMap.h"
#include "WorldInstance.h"
#include "GSPause.h"
#include "GSDead.h"

#include <iostream>
using namespace std;

GSIngame::GSIngame(){
    page=0;

    LoadMap::getInstance();
    cout<<"Cargado el mapa"<<endl;
    WorldInstance::Instance();
    timeStamp = World->getTimeElapsed();
    Scene::Instance();
    Scene::Instance()->Init();
}

GSIngame* GSIngame::getInstance()
{
  static GSIngame instance;

  return &instance;
}

void GSIngame::Update(){
    deltaTime = World->getTimeElapsed() - timeStamp;
    timeStamp = World->getTimeElapsed();
}

void GSIngame::HandleEvents(){
    if(GEInstance->receiver.isKeyDown(KEY_F10)){
        Game::getInstance()->ChangeState(GSPause::getInstance());
    }
    else if(GEInstance->receiver.isKeyDown(KEY_F9)){
        Game::getInstance()->ChangeState(GSDead::getInstance());
    }
    else if(GEInstance->receiver.isKeyDown(KEY_ESCAPE))
    {
        GEInstance->close();
        //return 0;
    }
}
void GSIngame::Render(){
    if(page==0){
        GEInstance->draw();
    }

}
GSIngame::~GSIngame(){}
