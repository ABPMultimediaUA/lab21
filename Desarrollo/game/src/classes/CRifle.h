#ifndef CRIFLE_H
#define CRIFLE_H

#include <defines.h>
#include <Consumable.h>


class CRifle : public Consumable
{
    public:
        CRifle();
        virtual ~CRifle();

        void onTake();

        // Getters & Setters
        FirearmKind getKind();
        void setKind(FirearmKind k);

    protected:

    private:
        FirearmKind m_kind;

};

#endif // CRIFLE_H
