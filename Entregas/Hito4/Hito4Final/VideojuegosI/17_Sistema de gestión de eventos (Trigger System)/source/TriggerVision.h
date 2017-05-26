#ifndef TRIGGERVISION_H
#define TRIGGERVISION_H

#include "Trigger.h"
#include "GraphicsEngine.h"

class Enemy;

class TriggerVision : public Trigger
{
    public:

        TriggerVision(Enemy* owner);

        virtual ~TriggerVision();

        void Update();

        void onBeginContact(EntityPhysics* otherObject);

        void onEndContact(EntityPhysics* otherObject);

    protected:

    private:

        Enemy* m_owner;
        bool m_touchingMainPlayer;
        EntityPhysics* m_playerEntity;
};

#endif // TRIGGERVISION_H
