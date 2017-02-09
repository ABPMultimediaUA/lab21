#include "Game.h"
#include <GraphicsEngine.h>

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
     while(GEInstance->isRunning()){
        Update();
        HandleEvents();
        Render();
        Quit();
    }
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
    if(!running){
        //se cierra el motor
    }
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


