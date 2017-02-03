#include "LeglessStates.h"
#include "Legless.h"

#include <iostream>
using std::cout;



LPatrolState* LPatrolState::Instance()
{
  static LPatrolState instance;

  return &instance;
}


void LPatrolState::Enter(Legless* pLegless)
{
    cout << "\n" << "Legless" << ": " << "Starting to crawl because I have no legs";
}


void LPatrolState::Execute(Legless* pLegless)
{

    cout << "\n" << "Legless" << ": " << "Patrolling. Moving with my arms";

    if(pLegless->getCrawl() == 15)
        pLegless->GetFSM()->ChangeState(LLookingForPlayerState::Instance());
}


void LPatrolState::Exit(Legless* pLegless)
{
  cout << "\n" << "Legless" << ": " << "Hmmmm?";
}

/*******************/

LLookingForPlayerState* LLookingForPlayerState::Instance()
{
  static LLookingForPlayerState instance;

  return &instance;
}

void LLookingForPlayerState::Enter(Legless* pLegless)
{
    cout << "\n" << "Legless" << ": " << "There is something here";
}


void LLookingForPlayerState::Execute(Legless* pLegless)
{
    cout << "\n" << "Legless" << ": " << "Looking for I don't know what";

    if(pLegless->getCrawl() == 10)
        pLegless->GetFSM()->ChangeState(LAttackState::Instance());
}

void LLookingForPlayerState::Exit(Legless* pLegless)
{

    cout << "\n" << "Legless" << ": " << "You, wait!";
}

/*******************/

LAttackState* LAttackState::Instance()
{
  static LAttackState instance;

  return &instance;
}

void LAttackState::Enter(Legless* pLegless)
{
    cout << "\n" << "Legless" << ": " << "I'm gonna catch you and kill you";
}


void LAttackState::Execute(Legless* pLegless)
{
    cout << "\n" << "Legless" << ": " << "'ZAP!'";

    if(pLegless->getCrawl() == 5)
        pLegless->GetFSM()->ChangeState(LPatrolState::Instance());
}

void LAttackState::Exit(Legless* pLegless)
{

    cout << "\n" << "Legless" << ": " << "I'm dying...";
}

