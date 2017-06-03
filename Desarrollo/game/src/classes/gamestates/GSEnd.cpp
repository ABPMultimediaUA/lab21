#include "GSEnd.h"
#include "NetGame.h"
#include "LoadMap.h"
#include "WorldInstance.h"
#include "Game.h"
#include "GUI.h"
#include "AudioEngine.h"
#include "GSMainMenu.h"
#include "GSIngame.h"

#include <iostream>

using namespace std;

GSEnd::GSEnd()
{
    //ctor
    ended = false;
}

GSEnd* GSEnd::getInstance()
{
  static GSEnd instance;

  return &instance;
}

void GSEnd::Init()
{
    endDemoBackground = new dwe::Background("finDemo");
    GEInstance->setOwnCursor(false);
}

void GSEnd::HandleEvents()
{
    //Control cerrado de ventana
    if(GEInstance->getWindowClose())
        Game::getInstance()->setRunning(false);
    /********************************************/
    if(GEInstance->receiver.isKeyDown(KEY_EXIT))
    {
        Game::getInstance()->setRunning(false);
    }
    if(GEInstance->receiver.isKeyDown(KEY_PAUSE))
    {
        AEInstance->StopAllSounds();
        GEInstance->initMenu();
        NetInstance->close();
        Scene::Instance()->Destroy();
        LoadMap::getInstance()->Destroy();
        GSIngame::getInstance()->Destroy();
        Game::getInstance()->ChangeState(GSMainMenu::getInstance());
    }
}

void GSEnd::Update()
{
}

void GSEnd::Render()
{
    endDemoBackground->draw();
}

GSEnd::~GSEnd()
{
    delete endDemoBackground;
}
