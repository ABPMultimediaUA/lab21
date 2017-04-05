#include "GuardianStates.h"
#include "Guardian.h"


#include <iostream>
using std::cout;



GPatrolState* GPatrolState::Instance()
{
  static GPatrolState instance;

  return &instance;
}


void GPatrolState::Enter(Guardian* pGuardian)
{
    cout << "\n" << "Guardian" << ": " << "Let's patrol";
}


void GPatrolState::Execute(Guardian* pGuardian)
{

    cout << "\n" << "Guardian" << ": " << "Patrolling here... Nobody can get our things";

}


void GPatrolState::Exit(Guardian* pGuardian)
{
  cout << "\n" << "Guardian" << ": " << "What...?";
}

/*******************/

GLookingForPlayerState* GLookingForPlayerState::Instance()
{
  static GLookingForPlayerState instance;

  return &instance;
}

void GLookingForPlayerState::Enter(Guardian* pGuardian)
{
    cout << "\n" << "Guardian" << ": " << "I heard something";
}


void GLookingForPlayerState::Execute(Guardian* pGuardian)
{
    cout << "\n" << "Guardian" << ": " << "Hey, what are you doing here?";
}

void GLookingForPlayerState::Exit(Guardian* pGuardian)
{

    cout << "\n" << "Guardian" << ": " << "Go away!";
}

/*******************/

GRangedAttackState* GRangedAttackState::Instance()
{
  static GRangedAttackState instance;

  return &instance;
}

void GRangedAttackState::Enter(Guardian* pGuardian)
{
    cout << "\n" << "Guardian" << ": " << "I'll attack you with my acid";
}


void GRangedAttackState::Execute(Guardian* pGuardian)
{
    cout << "\n" << "Guardian" << ": " << "GHHHHHHHSSSS";

}

void GRangedAttackState::Exit(Guardian* pGuardian)
{

    cout << "\n" << "Guardian" << ": " << "Do you want more?";
}

/*******************/

GMeleeAttackState* GMeleeAttackState::Instance()
{
  static GMeleeAttackState instance;

  return &instance;
}

void GMeleeAttackState::Enter(Guardian* pGuardian)
{
    cout << "\n" << "Guardian" << ": " << "Do you really think you can fight me?";
}


void GMeleeAttackState::Execute(Guardian* pGuardian)
{
    cout << "\n" << "Guardian" << ": " << "'PUNCH!'";

}

void GMeleeAttackState::Exit(Guardian* pGuardian)
{

    cout << "\n" << "Guardian" << ": " << "Are you tired?";
}

