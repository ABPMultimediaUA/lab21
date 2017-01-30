#ifndef GUARDIANSTATES_H
#define GUARDIANSTATES_H

#include <State.h>


class Guardian;


class GPatrolState : public State<Guardian>
{
    private:

        GPatrolState(){}

        //copy ctor and assignment should be private
        GPatrolState(const GPatrolState&);
        GPatrolState& operator=(const GPatrolState&);

    public:

          //this is a singleton
        static GPatrolState* Instance();

        virtual void Enter(Guardian* guardian);

        virtual void Execute(Guardian* guardian);

        virtual void Exit(Guardian* guardian);

};

/************************/

class GLookingForPlayerState : public State<Guardian>
{
    private:

        GLookingForPlayerState(){}

        //copy ctor and assignment should be private
        GLookingForPlayerState(const GLookingForPlayerState&);
        GLookingForPlayerState& operator=(const GLookingForPlayerState&);

    public:

        //this is a singleton
        static GLookingForPlayerState* Instance();

        virtual void Enter(Guardian* guardian);

        virtual void Execute(Guardian* guardian);

        virtual void Exit(Guardian* guardian);

};

/************************/

class GRangedAttackState : public State<Guardian>
{
    private:

        GRangedAttackState(){}

        //copy ctor and assignment should be private
        GRangedAttackState(const GRangedAttackState&);
        GRangedAttackState& operator=(const GRangedAttackState&);

    public:

        //this is a singleton
        static GRangedAttackState* Instance();

        virtual void Enter(Guardian* guardian);

        virtual void Execute(Guardian* guardian);

        virtual void Exit(Guardian* guardian);

};

/************************/

class GMeleeAttackState : public State<Guardian>
{
    private:

        GMeleeAttackState(){}

        //copy ctor and assignment should be private
        GMeleeAttackState(const GMeleeAttackState&);
        GMeleeAttackState& operator=(const GMeleeAttackState&);

    public:

        //this is a singleton
        static GMeleeAttackState* Instance();

        virtual void Enter(Guardian* guardian);

        virtual void Execute(Guardian* guardian);

        virtual void Exit(Guardian* guardian);

};


#endif // GUARDIANSTATES_H
