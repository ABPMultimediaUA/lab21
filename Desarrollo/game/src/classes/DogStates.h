#ifndef DOGSTATES_H
#define DOGSTATES_H


#include <State.h>


class Dog;


class DPatrolState : public State<Dog>
{
    private:

        DPatrolState(){}

        //copy ctor and assignment should be private
        DPatrolState(const DPatrolState&);
        DPatrolState& operator=(const DPatrolState&);

    public:

        //this is a singleton
        static DPatrolState* Instance();

        virtual void Enter(Dog* dog);

        virtual void Execute(Dog* dog);

        virtual void Exit(Dog* dog);

};

/************************/

class DLookingForPlayerState : public State<Dog>
{
    private:


        DLookingForPlayerState(){}

        //copy ctor and assignment should be private
        DLookingForPlayerState(const DLookingForPlayerState&);
        DLookingForPlayerState& operator=(const DLookingForPlayerState&);

    public:

        //this is a singleton
        static DLookingForPlayerState* Instance();

        virtual void Enter(Dog* dog);

        virtual void Execute(Dog* dog);

        virtual void Exit(Dog* dog);

};


/************************/

class DAsleepState : public State<Dog>
{
    private:


        DAsleepState(){}

        //copy ctor and assignment should be private
        DAsleepState(const DAsleepState&);
        DAsleepState& operator=(const DAsleepState&);

    public:

        //this is a singleton
        static DAsleepState* Instance();

        virtual void Enter(Dog* dog);

        virtual void Execute(Dog* dog);

        virtual void Exit(Dog* dog);

};

/************************/

class DKnockDownState : public State<Dog>
{
    private:


        DKnockDownState(){}

        //copy ctor and assignment should be private
        DKnockDownState(const DKnockDownState&);
        DKnockDownState& operator=(const DKnockDownState&);

    public:

        //this is a singleton
        static DKnockDownState* Instance();

        virtual void Enter(Dog* dog);

        virtual void Execute(Dog* dog);

        virtual void Exit(Dog* dog);

};

/************************/

class DAttackState : public State<Dog>
{
    private:


        DAttackState(){}

        //copy ctor and assignment should be private
        DAttackState(const DAttackState&);
        DAttackState& operator=(const DAttackState&);

    public:

        //this is a singleton
        static DAttackState* Instance();

        virtual void Enter(Dog* dog);

        virtual void Execute(Dog* dog);

        virtual void Exit(Dog* dog);

};

/************************/

class DRunAwayState : public State<Dog>
{
    private:


        DRunAwayState(){}

        //copy ctor and assignment should be private
        DRunAwayState(const DRunAwayState&);
        DRunAwayState& operator=(const DRunAwayState&);

    public:

        //this is a singleton
        static DRunAwayState* Instance();

        virtual void Enter(Dog* dog);

        virtual void Execute(Dog* dog);

        virtual void Exit(Dog* dog);

};

#endif // DOGSTATES_H
