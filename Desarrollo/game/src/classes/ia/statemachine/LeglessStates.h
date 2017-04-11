#ifndef LEGLESSSTATES_H
#define LEGLESSSTATES_H


#include <State.h>


class Legless;


class LPatrolState : public State<Legless>
{
    private:

        LPatrolState(){}

        //copy ctor and assignment should be private
        LPatrolState(const LPatrolState&);
        LPatrolState& operator=(const LPatrolState&);

    public:

        //this is a singleton
        static LPatrolState* Instance();

        virtual void Enter(Legless* legless);

        virtual void Execute(Legless* legless);

        virtual void Exit(Legless* legless);

};

/************************/

class LLookingForPlayerState : public State<Legless>
{
    private:

        LLookingForPlayerState(){}

        //copy ctor and assignment should be private
        LLookingForPlayerState(const LLookingForPlayerState&);
        LLookingForPlayerState& operator=(const LLookingForPlayerState&);

    public:

        //this is a singleton
        static LLookingForPlayerState* Instance();

        virtual void Enter(Legless* legless);

        virtual void Execute(Legless* legless);

        virtual void Exit(Legless* legless);

};

/************************/

class LAttackState : public State<Legless>
{
    private:

        LAttackState(){}

        //copy ctor and assignment should be private
        LAttackState(const LAttackState&);
        LAttackState& operator=(const LAttackState&);


    public:

        //this is a singleton
        static LAttackState* Instance();

        virtual void Enter(Legless* legless);

        virtual void Execute(Legless* legless);

        virtual void Exit(Legless* legless);

};

#endif // LEGLESSSTATES_H
