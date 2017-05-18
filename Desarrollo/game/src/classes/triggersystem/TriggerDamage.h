#ifndef TRIGGERDAMAGE_H
#define TRIGGERDAMAGE_H

#include "Trigger.h"
#include "GraphicsEngine.h"

class TriggerDamage : public Trigger
{
    public:

        TriggerDamage(dwe::vec3f pos, float radius, int damage, float angle);

        virtual ~TriggerDamage();

        void Update();

        int getDamage();

    protected:

    private:

        float lastTime;
        int m_damage;
};

#endif // TRIGGERDAMAGE_H
