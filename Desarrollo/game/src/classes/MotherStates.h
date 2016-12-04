#ifndef MOTHERSTATES_H
#define MOTHERSTATES_H

#include <State.h>


class Mother;


class StillState : public State<Mother>
{
    private:

        StillState(){}

        //copy ctor and assignment should be private
        StillState(const StillState&);
        StillState& operator=(const StillState&);

    public:

      //this is a singleton
      static StillState* Instance();

      virtual void Enter(Mother* mother);

      virtual void Execute(Mother* mother);

      virtual void Exit(Mother* mother);

};

/************************/

class CreatingState : public State<Mother>
{
private:

  CreatingState(){}

  //copy ctor and assignment should be private
  CreatingState(const CreatingState&);
  CreatingState& operator=(const CreatingState&);

public:


  //this is a singleton
  static CreatingState* Instance();

  virtual void Enter(Mother* mother);

  virtual void Execute(Mother* mother);

  virtual void Exit(Mother* mother);

};
#endif // MOTHERSTATES_H
