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
    cout << "\n" << "Bat" << ": " << "Starting to patrol";
}


void BPatrolState::Execute(Bat* pBat)
{

    cout << "\n" << "Bat" << ": " << "Paaatrooonus";

    if(pBat->getStepstoalarm() == 15)
        pBat->GetFSM()->ChangeState(BAlarmState::Instance());
}


void BPatrolState::Exit(Bat* pBat)
{
  cout << "\n" << "Bat" << ": " << "I saw the player and I'm gonna follow him while screaming like a crazy kid";
}

/*******************/

BAlarmState* BAlarmState::Instance()
{
  static BAlarmState instance;

  return &instance;
}

void BAlarmState::Enter(Bat* pBat)
{
    cout << "\n" << "Bat" << ": " << "Starting to follow him and scream a lot";
}


void BAlarmState::Execute(Bat* pBat)
{
    cout << "\n" << "Bat" << ": " << "AAAAAAAAAAAAAAAAAAAAH";

    if(pBat->getStepstoalarm() == 5)
        pBat->GetFSM()->ChangeState(BPatrolState::Instance());
}

void BAlarmState::Exit(Bat* pBat)
{
    // Bat dies
    cout << "\n" << "Bat" << ": " << "Dying";
}

