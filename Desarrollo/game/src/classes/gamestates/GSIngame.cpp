#include "GSIngame.h"
#include "LoadMap.h"
#include "WorldInstance.h"
#include "GSPause.h"
#include "GSDead.h"
#include "NetGame.h"
#include "GSEnd.h"
#include "AudioEngine.h"
#include "LoadingScreen.h"

#include <iostream>
using namespace std;

GSIngame::GSIngame() :
    m_gameStarted(false)
{
}

GSIngame* GSIngame::getInstance()
{
  static GSIngame instance;

  return &instance;
}

void GSIngame::Init(){
    LoadingScreen::getInstance()->AddProgress();
    page = 0;
    m = false;
    m_pausePermission = false;
    m_clickPermission = false;
    Scene::Instance();
    LoadMap::getInstance()->Init();  // Llamo dentro a AddProgress también
    LoadingScreen::getInstance()->AddProgress();
    WorldInstance::Instance();
    timeStamp = World->getTimeElapsed();
    Scene::Instance()->Init();
    LoadingScreen::getInstance()->AddProgress();
    hud = new Hud();

#ifdef LAB21_DEBUG
    World->startDebugPhysics();
#endif // LAB21_DEBUG

    if (NetInstance->isMultiplayer())
    {
        if (NetInstance->isServer()){
            GEInstance->addMessageLine("Pulsa Intro cuando esten todos los jugadores");
        }else{
            GEInstance->addMessageLine("Esperando a que el servidor de la partida inicie el juego");
        }
    }
    else
        m_gameStarted = true;

    GEInstance->receiver.clearEvents();

    LoadingScreen::getInstance()->Destroy();
}

void GSIngame::Update(){

    if (m_gameStarted)
    {
        // Esperamos conexion de los demas jugadores
        Scene::Instance()->Update();

        LoadMap::getInstance()->Update();

        // Actualizamos físicas box2d
        World->step();
        World->clearForces();
        NetInstance->update();

        //Fin del juego
        AEInstance->UpdateListenerPosition(World->getMainPlayer()->getPosition());
    }
    else
        checkForNetGameStarted();
}

void GSIngame::HandleEvents()
{
    /*******/
    if(GEInstance->receiver.isKeyDown(KEY_KEY_B))
        World->getMainPlayer()->sayPosition();
    /******/
    if(!m_pausePermission && GEInstance->receiver.isKeyUp(KEY_PAUSE))
        m_pausePermission = true;
    if(!m_clickPermission && GEInstance->receiver.isLeftButtonReleased()){
        m_clickPermission = true;
    }
    if(m_pausePermission && GEInstance->receiver.isKeyDown(KEY_PAUSE)){
        Game::getInstance()->ChangeState(GSPause::getInstance());
        GEInstance->setOwnCursor(false);
        m = false;
        m_pausePermission = false;
        m_clickPermission = false;
    }
    else if(GEInstance->receiver.isKeyDown(KEY_DO_DEAD)){
        Game::getInstance()->ChangeState(GSDead::getInstance());
        GEInstance->setOwnCursor(false);
        m = false;
        m_pausePermission = false;
        m_clickPermission = false;
    }
    else if(GEInstance->receiver.isKeyDown(KEY_EXIT) || GEInstance->getWindowClose()) //Control cerrado de ventana
    {
#ifdef LAB21_DEBUG
        World->stopDebugPhysics();
#endif // LAB21_DEBUG
        Game::getInstance()->setRunning(false);
    }
#ifdef LAB21_DEBUG
    if(GEInstance->receiver.isKeyDown(KEY_BEGIN_DEBUG_PHYSICS))
        World->setActiveDebugPhysics(true);
    else if(GEInstance->receiver.isKeyDown(KEY_STOP_DEBUG_PHYSICS))
        World->setActiveDebugPhysics(false);
#endif // LAB21_DEBUG
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

#ifdef LAB21_DEBUG
        World->drawDebugPhysics(GEInstance->getCameraPosition());
#endif // LAB21_DEBUG

        hud->draw();
    }
}
GSIngame::~GSIngame()
{
    cout<<"He borrado el mapa"<<endl;
}

void GSIngame::checkForNetGameStarted()
{
    // Esperamos a que se inicie partida en red
    // En startGame solo se inicia si es el servidor
    NetInstance->update();
    if (NetInstance->isServer())
    {
        if (GEInstance->receiver.isKeyDown(KEY_INIT_GAME))
        {
            m_gameStarted = true;
            NetInstance->startGame();
            GEInstance->addMessageLine("Partida iniciada");
        }
    }
    else
    {
        m_gameStarted = NetInstance->getGameStarted();
    }
}
