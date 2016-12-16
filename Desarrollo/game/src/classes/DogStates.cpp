#include "DogStates.h"
#include "Dog.h"

#include <iostream>
using std::cout;


DPatrolState* DPatrolState::Instance()
{
  static DPatrolState instance;

  return &instance;
}


void DPatrolState::Enter(Dog* pDog)
{
    cout << "\n" << "Dog" << ": " << "Going for a walk";
}


void DPatrolState::Execute(Dog* pDog)
{

    cout << "\n" << "Dog" << ": " << "Walking";

    io::path str = "media/dogC1.jpg";
    GEInstance->changeEnemyDogTexture(pDog, str);

    if(pDog->getSteps() == 13)
        pDog->GetFSM()->ChangeState(DLookingForPlayerState::Instance());
}


void DPatrolState::Exit(Dog* pDog)
{
  cout << "\n" << "Dog" << ": " << "!";
}

/*******************/

DLookingForPlayerState* DLookingForPlayerState::Instance()
{
  static DLookingForPlayerState instance;

  return &instance;
}

void DLookingForPlayerState::Enter(Dog* pDog)
{
    cout << "\n" << "Dog" << ": " << "I detected something";
}


void DLookingForPlayerState::Execute(Dog* pDog)
{
    cout << "\n" << "Dog" << ": " << "Trying to locate something strange";

    io::path str = "media/dogC3.jpg";
    GEInstance->changeEnemyDogTexture(pDog, str);

    if(pDog->getSteps() == 10)
        pDog->GetFSM()->ChangeState(DKnockDownState::Instance());
}

void DLookingForPlayerState::Exit(Dog* pDog)
{
    cout << "\n" << "Dog" << ": " << "Locating...";
}

/*******************/

DAsleepState* DAsleepState::Instance()
{
  static DAsleepState instance;

  return &instance;
}

void DAsleepState::Enter(Dog* pDog)
{
    cout << "\n" << "Dog" << ": " << "Going to sleep a bit";
}


void DAsleepState::Execute(Dog* pDog)
{
    cout << "\n" << "Dog" << ": " << "Dreaming with food";

    io::path str = "media/dogC2.jpg";
    GEInstance->changeEnemyDogTexture(pDog, str);


    if(pDog->getSteps() == 16)
        pDog->GetFSM()->ChangeState(DPatrolState::Instance());

    if (pDog->getSteps() == 0)
    {
        pDog->setSteps(19);
        pDog->GetFSM()->ChangeState(DPatrolState::Instance());
    }
}

void DAsleepState::Exit(Dog* pDog)
{
    cout << "\n" << "Dog" << ": " << "Waking up and yawning";
}

/*******************/

DKnockDownState* DKnockDownState::Instance()
{
  static DKnockDownState instance;

  return &instance;
}

void DKnockDownState::Enter(Dog* pDog)
{
    cout << "\n" << "Dog" << ": " << "Jumping";
}


void DKnockDownState::Execute(Dog* pDog)
{
    cout << "\n" << "Dog" << ": " << "Knocked down!";

    io::path str = "media/dogC4.jpg";
    GEInstance->changeEnemyDogTexture(pDog, str);

    if(pDog->getSteps() == 7)
        pDog->GetFSM()->ChangeState(DAttackState::Instance());
}

void DKnockDownState::Exit(Dog* pDog)
{
    cout << "\n" << "Dog" << ": " << "Grr...";
}

/*******************/

DAttackState* DAttackState::Instance()
{
  static DAttackState instance;

  return &instance;
}

void DAttackState::Enter(Dog* pDog)
{
    cout << "\n" << "Dog" << ": " << "I'll bite you";
}


void DAttackState::Execute(Dog* pDog)
{
    cout << "\n" << "Dog" << ": " << "Biting";

    io::path str = "media/dogC5.jpg";
    GEInstance->changeEnemyDogTexture(pDog, str);

    if(pDog->getSteps() == 4)
        pDog->GetFSM()->ChangeState(DRunAwayState::Instance());
}

void DAttackState::Exit(Dog* pDog)
{
    cout << "\n" << "Dog" << ": " << "It hurts!";
}

/*******************/

DRunAwayState* DRunAwayState::Instance()
{
  static DRunAwayState instance;

  return &instance;
}

void DRunAwayState::Enter(Dog* pDog)
{
    cout << "\n" << "Dog" << ": " << "I'm scared";
}


void DRunAwayState::Execute(Dog* pDog)
{
    cout << "\n" << "Dog" << ": " << "Running away";

    io::path str = "media/dogC6.jpg";
    GEInstance->changeEnemyDogTexture(pDog, str);

    if(pDog->getSteps() == 1)
        pDog->GetFSM()->ChangeState(DAsleepState::Instance());
}

void DRunAwayState::Exit(Dog* pDog)
{
    cout << "\n" << "Dog" << ": " << "Bye!";
}

