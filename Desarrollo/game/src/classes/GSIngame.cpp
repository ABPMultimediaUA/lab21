#include "GSIngame.h"
#include "LoadMap.h"
#include "WorldInstance.h"
#include "GSPause.h"
#include "GSDead.h"
#include "NetGame.h"


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
    m=false;
    LoadMap::getInstance()->Init();
    cout<<"Cargado el mapa"<<endl;
    WorldInstance::Instance();
    timeStamp = World->getTimeElapsed();
    Scene::Instance()->Init();
}

void GSIngame::Update(){
    // Esperamos conexion de los demas jugadores
    deltaTime = World->getTimeElapsed() - timeStamp;
    timeStamp = World->getTimeElapsed();
    Scene::Instance()->Update();

    LoadMap::getInstance()->Update();

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
        Game::getInstance()->setRunning(false);
        //GEInstance=0;

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
        //GEInstance->draw();
        hud->draw();
        GEInstance->popGLStates();
    }
}
GSIngame::~GSIngame(){

    cout<<"He borrado el mapa"<<endl;

}
