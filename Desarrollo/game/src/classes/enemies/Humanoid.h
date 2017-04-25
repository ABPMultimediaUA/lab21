#ifndef HUMANOID_H
#define HUMANOID_H

#include "Enemy.h"

class BTreeHumanoid;

class Humanoid : public Enemy
{
    public:

        Humanoid();

        ~Humanoid();

        virtual void update();

        virtual void render(){};

    protected:

    private:

        BTreeHumanoid* m_behaviourTree;

};
#endif // HUMANOID_H
