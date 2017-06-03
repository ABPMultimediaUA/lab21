#include "Game.h"
#include "GraphicsEngine.h"
#include "NetGame.h"
#include "AudioEngine.h"
#include "WorldInstance.h"

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

void Game::Run()
{
    float timeStamp = World->getTimeElapsed();
    float frameRate = 1.0/60.0;
    float deltaTime;

    while(running)
    {
        deltaTime = World->getTimeElapsed() - timeStamp;

        if (deltaTime >= frameRate)
        {
            timeStamp = World->getTimeElapsed();
            GEInstance->isRunning();
            Update();
            HandleEvents();
            Render();
        }
   }
   Quit();
}

void Game::ChangeState(GState *newState, bool initialize){
    CurrentState = newState;
    if (initialize)
        newState->Init();
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


