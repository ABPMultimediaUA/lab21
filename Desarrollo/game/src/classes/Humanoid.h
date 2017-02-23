#ifndef HUMANOID_H
#define HUMANOID_H

#include <Enemy.h>
#include <StateMachine.h>
#include <HumanoidStates.h>
#include <iostream>


class Perception;
class Pathplanning;
class Selector;
class Sequence;
class PathplanningTask;
class PerceptionTask;
class PatrolTask;


class Humanoid : public Enemy
{
    public:
        Humanoid();

        ~Humanoid();

        StateMachine<Humanoid>* GetFSM()const;

        void Update(); // Update de la maquina de estados

        int getSteps();

        void update();

        virtual void render() {};


    protected:

    private:

        int steps;

        StateMachine<Humanoid>*  h_pStateMachine;

        dwe::Node* fovnode; // Futuro dentro de cada enemigo

        Perception* percep;
        Pathplanning* pathp;
        Selector* selector1;
        Sequence *sequence1;

        PathplanningTask* path;
        PerceptionTask* perc;
        PatrolTask* patrol;
};
#endif // HUMANOID_H
