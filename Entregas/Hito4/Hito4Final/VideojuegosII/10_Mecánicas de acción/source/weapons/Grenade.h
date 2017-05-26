#ifndef GRENADE_H
#define GRENADE_H


class Grenade
{
    public:
        Grenade();
        virtual ~Grenade();

        void shoot();

        float getCadence();

    protected:

    private:
        float m_cadence;
};

#endif // GRENADE_H
