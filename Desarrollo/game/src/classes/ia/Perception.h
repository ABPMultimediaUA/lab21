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

        void SetHearing(bool b);
        void SetSeeing(bool b);
        void SetSoundPosition(dwe::vec2f pos);
        void SetVisionPosition(dwe::vec2f pos);

        bool GetHearing();
        bool GetSeeing();
        dwe::vec2f GetSoundPosition();
        dwe::vec2f GetVisionPosition();

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
