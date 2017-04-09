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
    m_clickPermission=false;
    m_pausePermission=false;
    menuPausaFondo = new dwe::Background("menuPausa");
    resumeGameButton = new dwe::Button("Resume game", GEInstance->get_screenWidth()*0.1, GEInstance->get_screenHeight()*0.35);
    helpOptionsButton = new dwe::Button("Help & options", GEInstance->get_screenWidth()*0.1, GEInstance->get_screenHeight()*0.43);
    exitToMainMenuButton = new dwe::Button("Exit to main menu", GEInstance->get_screenWidth()*0.1, GEInstance->get_screenHeight()*0.51);
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
            m = true;
        }
    }
    menuPausaFondo->draw();
    resumeGameButton->draw();
    helpOptionsButton->draw();
    exitToMainMenuButton->draw();
}

void GSPause::SetPage(int n){
    page = n;
}

bool GSPause::buttonCheck(dwe::Button *b)
{
    if(GEInstance->receiver.isLeftButtonPressed()
       &&(mousePosX>b->getXOrigin()
       && mousePosY>b->getYOrigin()
       && mousePosX<b->getWidth()
       && mousePosY<b->getHeight())
    ){return true;}
    return false;
}

void GSPause::HandleEvents(){
    //Control cerrado de ventana
    if(GEInstance->getWindowClose())
        Game::getInstance()->setRunning(false);
    /****************************************************************/
    if(!m_pausePermission && GEInstance->receiver.isKeyUp(KEY_PAUSE)){
        m_pausePermission = true;
    }
    if(!m_clickPermission && GEInstance->receiver.isLeftButtonReleased()){
        m_clickPermission = true;
    }
    /**/
    if(m_pausePermission && GEInstance->receiver.isKeyDown(KEY_PAUSE)){
        resumeGame();
    }else if(m_clickPermission && buttonCheck(resumeGameButton)){
        resumeGame();
    }
    if(m_clickPermission && buttonCheck(exitToMainMenuButton)){
        backToMainMenu();
    }
}

void GSPause::Update()
{
    mousePosX=GEInstance->receiver.getCursorX();
    mousePosY=GEInstance->receiver.getCursorY();
}

GSPause::~GSPause()
{
    delete menuPausaFondo;
    delete resumeGameButton;
    delete helpOptionsButton;
    delete exitToMainMenuButton;
}

void GSPause::resumeGame()
{
    Game::getInstance()->ChangeState(GSIngame::getInstance());
    m = false;
    m_clickPermission = false;
    m_pausePermission = false;
}

void GSPause::backToMainMenu()
{
    Game::getInstance()->ChangeState(GSMainMenu::getInstance());
    NetInstance->close();
    Game::getInstance()->ChangeState(GSMainMenu::getInstance());
    Scene::Instance()->Destroy();
    LoadMap::getInstance()->Destroy();
    m = false;
    m_pausePermission = false;
    m_clickPermission = false;
}
