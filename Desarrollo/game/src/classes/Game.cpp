#include "Game.h"
#include <GraphicsEngine.h>
#include "NetGame.h"

Game::Game(){
    running = true;
}

Game* Game::getInstance()
{
  static Game instance;

  return &instance;
}

Game::~Game(){
}

void Game::Run(){

     while(running){
        GEInstance->isRunning();
        Update();
        HandleEvents();
        Render();
    }cout<<"hadouken"<<endl;
    Quit();
}

void Game::ChangeState(GState *newState){
    CurrentState = newState;
}

void Game::setRunning(bool mRunning){
    running = mRunning;
}
bool Game::getRunning(){
    return running;
}
void Game::Quit(){
cout<<"muffins"<<endl;
        //se cierra el motor
        NetInstance->close();
        cout<<"muffinz"<<endl;
        GEInstance->close();
        cout<<"muggins"<<endl;

}
void Game::Update(){
    CurrentState->Update();
}
void Game::HandleEvents(){
    CurrentState->HandleEvents();
}
void Game::Render(){
    //clear
    CurrentState->Render();
    //display
}


