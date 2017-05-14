#ifndef BATSTATES_H
#define BATSTATES_H

#include <State.h>


class Bat;


class BPatrolState : public State<Bat>
{
    private:

        BPatrolState(){};

        //copy ctor and assignment should be private
        BPatrolState(const BPatrolState&);
        BPatrolState& operator=(const BPatrolState&);

    public:

        //this is a singleton
        static BPatrolState* Instance();

        virtual void Enter(Bat* bat);

        virtual void Execute(Bat* bat);

        virtual void Exit(Bat* bat);

};

/************************/

class BAlarmState : public State<Bat>
{
    private:


        BAlarmState(){};

        //copy ctor and assignment should be private
        BAlarmState(const BAlarmState&);
        BAlarmState& operator=(const BAlarmState&);

    public:

        //this is a singleton
        static BAlarmState* Instance();

        virtual void Enter(Bat* bat);

        virtual void Execute(Bat* bat);

        virtual void Exit(Bat* bat);

};


#endif // BATSTATES_H
