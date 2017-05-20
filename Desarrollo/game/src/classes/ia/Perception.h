#ifndef PERCEPTION_H
#define PERCEPTION_H

#include "GraphicsEngine.h"

class Enemy;
class Drawable;

class Perception
{
    public:

        Perception(Enemy *owner);

        virtual ~Perception();

        bool Sense();

        void Hear(dwe::vec3f pos);

        void See(dwe::vec3f pos);

    protected:

    private:

        Enemy *m_owner;
        bool m_hearing;
        dwe::vec2f m_soundPosition;
        bool m_seeing;
        dwe::vec2f m_visionPosition;
        float GetDistanceClosestPlayer(Drawable*& pl);

};

#endif // PERCEPTION_H
