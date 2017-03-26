#include "Game.h"
#include "tag/TAGEngine.h"
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
    while(running){
        GEInstance->isRunning();
        Update();
        HandleEvents();
        Render();
    }
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
        //se cierra el motor
        GEInstance->close();
}

void Game::Update(){
    CurrentState->Update();
}

void Game::HandleEvents(){
    CurrentState->HandleEvents();
}

void Game::Render(){
    GEInstance->clearWindow();
    CurrentState->Render();
    GEInstance->displayWindow();
}


