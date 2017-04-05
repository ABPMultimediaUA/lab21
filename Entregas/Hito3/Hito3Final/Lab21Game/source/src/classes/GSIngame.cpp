#include "GSIngame.h"
#include "LoadMap.h"
#include "WorldInstance.h"
#include "GSPause.h"
#include "GSDead.h"
#include "NetGame.h"
#include "GSEnd.h"
#include "AudioEngine.h"

#include <iostream>
using namespace std;

GSIngame::GSIngame(){


}

GSIngame* GSIngame::getInstance()
{
  static GSIngame instance;

  return &instance;
}

void GSIngame::Init(){
    page = 0;
    m = false;
    m_pausePermission = false;
    LoadMap::getInstance()->Init();
    WorldInstance::Instance();
    timeStamp = World->getTimeElapsed();
    Scene::Instance()->Init();
    hud = new Hud();

    cout<<"Ingame cargado"<<endl;

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

    //Fin del juego
    if(Scene::Instance()->getNumberEnemies()==0){
        Game::getInstance()->ChangeState(GSEnd::getInstance());
        GSEnd::getInstance()->Init();
    }
    AEInstance->UpdateListenerPosition(World->getMainPlayer()->getPosition());
}

void GSIngame::HandleEvents(){
    if(!m_pausePermission && GEInstance->receiver.isKeyUp(KEY_PAUSE))
        m_pausePermission = true;
    if(m_pausePermission && GEInstance->receiver.isKeyDown(KEY_PAUSE)){
        Game::getInstance()->ChangeState(GSPause::getInstance());
        m = false;
        m_pausePermission = false;
    }
    else if(GEInstance->receiver.isKeyDown(KEY_DO_DEAD)){
        Game::getInstance()->ChangeState(GSDead::getInstance());
        m = false;
        m_pausePermission = false;
    }
    else if(GEInstance->receiver.isKeyDown(KEY_EXIT))
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
            cout<<"Pulsa P para pausar el juego"<<endl;
            m=true;
        }
        GEInstance->draw();
        hud->draw();
    }
}
GSIngame::~GSIngame(){

    cout<<"He borrado el mapa"<<endl;

}
