#include "GSIngame.h"
#include "LoadMap.h"
#include "WorldInstance.h"
#include "GSPause.h"
#include "GSDead.h"

#include <iostream>
using namespace std;

GSIngame::GSIngame(){
    page=0;
    m=false;
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
    // Esperamos conexion de los demas jugadores
    deltaTime = World->getTimeElapsed() - timeStamp;
    timeStamp = World->getTimeElapsed();
    Scene::Instance()->Update();
    // Actualizamos físicas box2d
    World->step(deltaTime);
    World->clearForces();
    NetInstance->update();
}

void GSIngame::HandleEvents(){
    if(GEInstance->receiver.isKeyDown(KEY_F10)){
        Game::getInstance()->ChangeState(GSPause::getInstance());
        m = false;
    }
    else if(GEInstance->receiver.isKeyDown(KEY_F9)){
        Game::getInstance()->ChangeState(GSDead::getInstance());
        m = false;
    }
    else if(GEInstance->receiver.isKeyDown(KEY_ESCAPE))
    {
        GEInstance->close();
        //return 0;
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
    }
}
GSIngame::~GSIngame(){}
