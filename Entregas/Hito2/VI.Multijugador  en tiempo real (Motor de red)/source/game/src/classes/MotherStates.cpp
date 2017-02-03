#include "MotherStates.h"
#include "Mother.h"

#include <iostream>
using std::cout;


/*#ifdef TEXTOUTPUT
#include <fstream>
extern std::ofstream os;
#define cout os
#endif*/

//

StillState* StillState::Instance()
{
  static StillState instance;

  return &instance;
}


void StillState::Enter(Mother* pMother)
{
    pMother->setTimeBetweenCreations(0);
    cout << "\n" << "Mother" << ": " << "Im going to rest a bit";
}


void StillState::Execute(Mother* pMother)
{

    cout << "\n" << "Mother" << ": " << "ZZzzZzZzZ...";

    if(pMother->getTimeBetweenCreations() == 4)
        pMother->GetFSM()->ChangeState(CreatingState::Instance());
}


void StillState::Exit(Mother* pMother)
{
  cout << "\n" << "Mother" << ": " << "I woke up because that guy is trying to attack me";
}

/*******************/

CreatingState* CreatingState::Instance()
{
  static CreatingState instance;

  return &instance;
}

void CreatingState::Enter(Mother* pMother)
{
    cout << "\n" << "Mother" << ": " << "Gonna create a few more children to fight him";
}


void CreatingState::Execute(Mother* pMother)
{
    cout << "\n" << "Mother" << ": " << "NNNNNNNNFFFF";

    if(pMother->getTimeBetweenCreations() == 8)
        pMother->GetFSM()->ChangeState(StillState::Instance());
}

void CreatingState::Exit(Mother* pMother)
{

    cout << "\n" << "Mother" << ": " << "Go kid go!";
}
