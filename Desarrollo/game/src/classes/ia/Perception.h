#ifndef PERCEPTION_H
#define PERCEPTION_H

class Enemy;
class Drawable;

class Perception
{
    public:

        Perception(Enemy *owner);

        virtual ~Perception();

        bool Sense();

    protected:

    private:

        Enemy *m_owner;

        float GetDistanceClosestPlayer(Drawable*& pl);

};

#endif // PERCEPTION_H
