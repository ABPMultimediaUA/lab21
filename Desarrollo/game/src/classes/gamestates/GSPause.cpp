#include "GSPause.h"
#include "GSIngame.h"
#include "GSMainMenu.h"
#include "Scene.h"
#include "LoadMap.h"
#include "NetGame.h"
#include "GUI.h"
#include "AudioEngine.h"

#include <iostream>

using namespace std;

const int GSPause::_margin    = 40;
const int GSPause::_marginTop = 80;

GSPause::GSPause(){
    page = 0;
    m = false;
    m_clickPermission=false;
    m_pausePermission=false;
    menuPausaFondo = new dwe::Background("menuBackground");
    /**Decoracion**/
    pauseDecoration = new dwe::Sprite("pauseDecoration",_margin, _marginTop);
    optionsDecoration = new dwe::Sprite("optionsDecoration", _margin, _marginTop);

    volumeSlider = new dwe::Slider(_margin, _marginTop+130);

    resumeGameButton = new dwe::Button("Resume game", _margin+66, _marginTop+80, true);
    helpOptionsButton = new dwe::Button("Help & options",  _margin+66, _marginTop+130, true);
    exitToMainMenuButton = new dwe::Button("Exit to main menu",  _margin+66, _marginTop+180, true);
    backButton = new dwe::Button("Back", GEInstance->get_screenWidth()-200, GEInstance->get_screenHeight()-100, false);

}

GSPause* GSPause::getInstance()
{
  static GSPause instance;

  return &instance;
}


void GSPause::Render(){
    if(page==0)
    {
        if(!m){
            cout<<"Pause"<<endl;
            cout<<"Pulsa Esc para volver al juego"<<endl;
            m = true;
        }
        menuPausaFondo->draw();
        resumeGameButton->draw();
        helpOptionsButton->draw();
        exitToMainMenuButton->draw();
        pauseDecoration->draw();
    }
    else if(page==1)
    {
        menuPausaFondo->draw();
        optionsDecoration->draw();
        volumeSlider->draw();
        backButton->draw();
    }

}

void GSPause::SetPage(int n){
    page = n;
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
    switch(page){
        case 0:if(m_pausePermission && GEInstance->receiver.isKeyDown(KEY_PAUSE)){
                    resumeGame();
                    page = 0;
                    m = false;
                }else if(m_clickPermission && resumeGameButton->buttonCheck(mousePosX, mousePosY)){
                    resumeGame();
                    page = 0;
                    m = false;
                }else if(m_clickPermission && helpOptionsButton->buttonCheck(mousePosX, mousePosY)){
                    m_clickPermission = false;
                    page = 1;
                }
                if(m_clickPermission && exitToMainMenuButton->buttonCheck(mousePosX, mousePosY)){
                    backToMainMenu();
                    page = 0;
                    m = false;
                }
                break;
        case 1:volumeSlider->sliderCheck(mousePosX, mousePosY);
                if(backButton->buttonCheck(mousePosX, mousePosY))
                {
                    page=0;
                    m = false;
                    m_clickPermission=false;
                }
                break;
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
    delete pauseDecoration;
    delete optionsDecoration;
    delete volumeSlider;
    delete resumeGameButton;
    delete helpOptionsButton;
    delete exitToMainMenuButton;
    delete backButton;
}

void GSPause::resumeGame()
{
    Game::getInstance()->ChangeState(GSIngame::getInstance(), false);
    GEInstance->receiver.clearEvents();
    GEInstance->setOwnCursor(true);
    m = false;
    m_clickPermission = false;
    m_pausePermission = false;
}

void GSPause::backToMainMenu()
{
    AEInstance->StopAllSounds();
    GEInstance->initMenu();
    Game::getInstance()->ChangeState(GSMainMenu::getInstance());
    NetInstance->close();
    Game::getInstance()->ChangeState(GSMainMenu::getInstance());
    Scene::Instance()->Destroy();
    LoadMap::getInstance()->Destroy();
    GSIngame::getInstance()->Destroy();
    m = false;
    m_pausePermission = false;
    m_clickPermission = false;
}
