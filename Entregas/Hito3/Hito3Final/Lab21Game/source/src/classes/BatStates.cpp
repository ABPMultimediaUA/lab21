#include "BatStates.h"
#include "Bat.h"

#include <iostream>

using std::cout;


BPatrolState* BPatrolState::Instance()
{
  static BPatrolState instance;

  return &instance;
}


void BPatrolState::Enter(Bat* pBat)
{

}


void BPatrolState::Execute(Bat* pBat)
{
    //if ve al jugador
    //pBat->GetFSM()->ChangeState(BAlarmState::Instance());
}


void BPatrolState::Exit(Bat* pBat)
{

}

/*******************/

BAlarmState* BAlarmState::Instance()
{
  static BAlarmState instance;

  return &instance;
}

void BAlarmState::Enter(Bat* pBat)
{

}


void BAlarmState::Execute(Bat* pBat)
{
    //if deja de ver al jugador
    //pBat->GetFSM()->ChangeState(BPatrolState::Instance());
}

void BAlarmState::Exit(Bat* pBat)
{
    // Bat dies
}

