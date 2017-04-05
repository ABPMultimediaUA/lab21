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

}


void LPatrolState::Execute(Legless* pLegless)
{
    //if ve al jugador
    //pLegless->GetFSM()->ChangeState(LLookingForPlayerState::Instance());
}


void LPatrolState::Exit(Legless* pLegless)
{

}

/*******************/

LLookingForPlayerState* LLookingForPlayerState::Instance()
{
  static LLookingForPlayerState instance;

  return &instance;
}

void LLookingForPlayerState::Enter(Legless* pLegless)
{

}


void LLookingForPlayerState::Execute(Legless* pLegless)
{
    //if cerca del jugador
    //pLegless->GetFSM()->ChangeState(LAttackState::Instance());

    //if deja de ver al jugador
    //pLegless->GetFSM()->ChangeState(LPatrolState::Instance());
}

void LLookingForPlayerState::Exit(Legless* pLegless)
{

}

/*******************/

LAttackState* LAttackState::Instance()
{
  static LAttackState instance;

  return &instance;
}

void LAttackState::Enter(Legless* pLegless)
{

}


void LAttackState::Execute(Legless* pLegless)
{
    //if termina de atacar
    //pLegless->GetFSM()->ChangeState(LLookingForPlayerState::Instance());
}

void LAttackState::Exit(Legless* pLegless)
{
    //muere
}

