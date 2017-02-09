#include "GSPause.h"
#include "GSIngame.h"
#include "GSMainMenu.h"

#include <iostream>

using namespace std;

GSPause::GSPause(){
    page = 0;
}

GSPause* GSPause::getInstance()
{
  static GSPause instance;

  return &instance;
}


void GSPause::Render(){
    if(page==0){
        cout<<"Pause"<<endl;
    }

}

void GSPause::SetPage(int n){
    page = n;
}

void GSPause::HandleEvents(){
    if(GEInstance->receiver.isKeyDown(KEY_KEY_P)){
        Game::getInstance()->ChangeState(GSIngame::getInstance());
    }
    if(GEInstance->receiver.isKeyDown(KEY_F9)){
        Game::getInstance()->ChangeState(GSMainMenu::getInstance());
    }
}

void GSPause::Update(){
     //cin>>page;
}
GSPause::~GSPause(){}
