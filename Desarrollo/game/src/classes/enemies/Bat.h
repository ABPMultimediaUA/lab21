#ifndef BAT_H
#define BAT_H

#include <Enemy.h>
#include "StateMachine.h"

class BTreeHumanoid;

class Bat : public Enemy
{
    public:

        Bat();

        ~Bat();

        StateMachine<Bat>* GetFSM()const;

        virtual void update();

        virtual void render(){};

    protected:

    private:

        StateMachine<Bat>*  b_pStateMachine;
};

#endif // BAT_H
