#ifndef CSHOTGUN_H
#define CSHOTGUN_H

#include <defines.h>
#include <Consumable.h>


class CShotgun : public Consumable
{
    public:
        CShotgun();
        virtual ~CShotgun();

        void onTake();

        // Getters & Setters
        FirearmKind getKind();
        void setKind(FirearmKind k);

    protected:

    private:
        FirearmKind m_kind;
};

#endif // CSHOTGUN_H
