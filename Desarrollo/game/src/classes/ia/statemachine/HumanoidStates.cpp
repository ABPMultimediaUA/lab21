#include "HumanoidStates.h"
#include "Humanoid.h"

#include <iostream>
using std::cout;

/*
HPatrolState* HPatrolState::Instance()
{
  static HPatrolState instance;

  return &instance;
}


void HPatrolState::Enter(Humanoid* pHumanoid)
{
    cout << "\n" << "Humanoid" << ": " << "Let's walk around here";
}


void HPatrolState::Execute(Humanoid* pHumanoid)
{

    cout << "\n" << "Humanoid" << ": " << "Walking, all good";

    if(pHumanoid->getSteps() == 17)
        pHumanoid->GetFSM()->ChangeState(HLookingForPlayerState::Instance());
}


void HPatrolState::Exit(Humanoid* pHumanoid)
{
  cout << "\n" << "Humanoid" << ": " << "!!!";
}

/*******************/
/*
HLookingForPlayerState* HLookingForPlayerState::Instance()
{
  static HLookingForPlayerState instance;

  return &instance;
}

void HLookingForPlayerState::Enter(Humanoid* pHumanoid)
{
    cout << "\n" << "Humanoid" << ": " << "I think I heard something strange";
}


void HLookingForPlayerState::Execute(Humanoid* pHumanoid)
{
    cout << "\n" << "Humanoid" << ": " << "Looking for a intruder";

    if(pHumanoid->getSteps() == 14)
        pHumanoid->GetFSM()->ChangeState(HMeleeAttackState::Instance());
}

void HLookingForPlayerState::Exit(Humanoid* pHumanoid)
{
    cout << "\n" << "Humanoid" << ": " << "Let's take a look over here...";
}

/*******************/
/*
HMeleeAttackState* HMeleeAttackState::Instance()
{
  static HMeleeAttackState instance;

  return &instance;
}

void HMeleeAttackState::Enter(Humanoid* pHumanoid)
{
    cout << "\n" << "Humanoid" << ": " << "Come here!";
}


void HMeleeAttackState::Execute(Humanoid* pHumanoid)
{
    cout << "\n" << "Humanoid" << ": " << "Consecutive normal punches";

    if(pHumanoid->getSteps() == 8)
        pHumanoid->GetFSM()->ChangeState(HRangedAttackState::Instance());
}

void HMeleeAttackState::Exit(Humanoid* pHumanoid)
{
    cout << "\n" << "Humanoid" << ": " << "Low health!";
}

/*******************/
/*
HRangedAttackState* HRangedAttackState::Instance()
{
  static HRangedAttackState instance;

  return &instance;
}

void HRangedAttackState::Enter(Humanoid* pHumanoid)
{
    cout << "\n" << "Humanoid" << ": " << "I'll walk away and attack with acid";
}


void HRangedAttackState::Execute(Humanoid* pHumanoid)
{
    cout << "\n" << "Humanoid" << ": " << "Throwing acid!";

    if(pHumanoid->getSteps() == 5)
        pHumanoid->GetFSM()->ChangeState(HRunAwayState::Instance());
}

void HRangedAttackState::Exit(Humanoid* pHumanoid)
{
    cout << "\n" << "Humanoid" << ": " << "I'm so low...";
}

/*******************/

/*
HRunAwayState* HRunAwayState::Instance()
{
  static HRunAwayState instance;

  return &instance;
}

void HRunAwayState::Enter(Humanoid* pHumanoid)
{
    cout << "\n" << "Humanoid" << ": " << "O.K. I'll go away and try to find help";
}


void HRunAwayState::Execute(Humanoid* pHumanoid)
{
    cout << "\n" << "Humanoid" << ": " << "Running away! HELP HERE!";

    if(pHumanoid->getSteps() == 2)
        pHumanoid->GetFSM()->ChangeState(HPatrolState::Instance());
}

void HRunAwayState::Exit(Humanoid* pHumanoid)
{
    cout << "\n" << "Humanoid" << ": " << "I think I'm safe now...";
}

*/
