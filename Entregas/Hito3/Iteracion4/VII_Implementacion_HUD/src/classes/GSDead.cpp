#include "GSDead.h"
#include "GSMainMenu.h"
#include "GSIngame.h"

#include <iostream>

using namespace std;

GSDead::GSDead(){

}

GSDead* GSDead::getInstance()
{
  static GSDead instance;

  return &instance;
}


void GSDead::Render(){

}

void GSDead::HandleEvents(){

}

void GSDead::Update(){
    cout<<"MUERTO"<<endl;
    Game::getInstance()->ChangeState(GSMainMenu::getInstance());
    //World->Destroy();
}

GSDead::~GSDead(){}
