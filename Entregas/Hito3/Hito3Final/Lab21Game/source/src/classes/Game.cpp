#include "Game.h"
#include "GraphicsEngine.h"
#include "NetGame.h"
#include "AudioEngine.h"

Game::Game(){
    running = true;
    GEInstance->init();
    AEInstance->Create();
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
        if(NetInstance->getOpened()){
            NetInstance->close();
        }
        GEInstance->close();
        AEInstance->Drop();
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


