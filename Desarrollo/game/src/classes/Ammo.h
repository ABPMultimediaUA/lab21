#ifndef AMMO_H
#define AMMO_H

#include <Consumable.h>


class Ammo : public Consumable
{
    public:
        Ammo();
        virtual ~Ammo();


        // Getters & Setters
        int getAmmount();
        void setAmmount(int a);

    protected:

    private:
        int m_ammount;
};

#endif // AMMO_H
