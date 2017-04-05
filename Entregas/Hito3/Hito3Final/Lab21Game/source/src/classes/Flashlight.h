#ifndef FLASHLIGHT_H
#define FLASHLIGHT_H

#include <Consumable.h>


class Flashlight : public Consumable
{
    public:
        Flashlight();
        virtual ~Flashlight();

        void onTake();

    protected:

    private:
};

#endif // FLASHLIGHT_H
