#ifndef MEDKIT_H
#define MEDKIT_H

#include <Consumable.h>


class Medkit : public Consumable
{
    public:
        Medkit();
        virtual ~Medkit();

        void onTake();

    protected:

    private:
};

#endif // MEDKIT_H
