#include "GSEnd.h"
#include "NetGame.h"
#include "LoadMap.h"
#include "WorldInstance.h"
#include "Game.h"
#include "GUI.h"

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
    cout<<"FIN"<<endl;

    endDemoBackground = new dwe::Background("finDemo");
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
}

void GSEnd::Update()
{
    if(!ended){
        ended = true;
        NetInstance->close();
        Scene::Instance()->Destroy();
        LoadMap::getInstance()->Destroy();
    }
}

void GSEnd::Render()
{
    endDemoBackground->draw();
}

GSEnd::~GSEnd()
{
    delete endDemoBackground;
}
