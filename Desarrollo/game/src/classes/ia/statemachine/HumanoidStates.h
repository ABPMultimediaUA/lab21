#ifndef HUMANOIDSTATES_H
#define HUMANOIDSTATES_H


#include <State.h>


class Humanoid;


class HPatrolState : public State<Humanoid>
{
    private:

        HPatrolState(){}

        //copy ctor and assignment should be private
        HPatrolState(const HPatrolState&);
        HPatrolState& operator=(const HPatrolState&);

    public:

        //this is a singleton
        static HPatrolState* Instance();

        virtual void Enter(Humanoid* humanoid);

        virtual void Execute(Humanoid* humanoid);

        virtual void Exit(Humanoid* humanoid);

};

/************************/

class HLookingForPlayerState : public State<Humanoid>
{
    private:


        HLookingForPlayerState(){}

        //copy ctor and assignment should be private
        HLookingForPlayerState(const HLookingForPlayerState&);
        HLookingForPlayerState& operator=(const HLookingForPlayerState&);

    public:

        //this is a singleton
        static HLookingForPlayerState* Instance();

        virtual void Enter(Humanoid* humanoid);

        virtual void Execute(Humanoid* humanoid);

        virtual void Exit(Humanoid* humanoid);

};


/************************/

class HMeleeAttackState : public State<Humanoid>
{
    private:


        HMeleeAttackState(){}

        //copy ctor and assignment should be private
        HMeleeAttackState(const HMeleeAttackState&);
        HMeleeAttackState& operator=(const HMeleeAttackState&);

    public:

        //this is a singleton
        static HMeleeAttackState* Instance();

        virtual void Enter(Humanoid* humanoid);

        virtual void Execute(Humanoid* humanoid);

        virtual void Exit(Humanoid* humanoid);

};

/************************/

class HRangedAttackState : public State<Humanoid>
{
    private:


        HRangedAttackState(){}

        //copy ctor and assignment should be private
        HRangedAttackState(const HRangedAttackState&);
        HRangedAttackState& operator=(const HRangedAttackState&);

    public:

        //this is a singleton
        static HRangedAttackState* Instance();

        virtual void Enter(Humanoid* humanoid);

        virtual void Execute(Humanoid* humanoid);

        virtual void Exit(Humanoid* humanoid);

};


/************************/

class HRunAwayState : public State<Humanoid>
{
    private:


        HRunAwayState(){}

        //copy ctor and assignment should be private
        HRunAwayState(const HRunAwayState&);
        HRunAwayState& operator=(const HRunAwayState&);

    public:

        //this is a singleton
        static HRunAwayState* Instance();

        virtual void Enter(Humanoid* humanoid);

        virtual void Execute(Humanoid* humanoid);

        virtual void Exit(Humanoid* humanoid);
};


#endif // HUMANOIDSTATES_H
