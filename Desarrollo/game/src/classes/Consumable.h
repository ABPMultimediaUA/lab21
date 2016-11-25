#ifndef CONSUMABLE_H
#define CONSUMABLE_H

#include <Drawable.h>


class Consumable : public Drawable
{
    public:
        Consumable();
        virtual ~Consumable();

        virtual void onTake() = 0;

    protected:

    private:
};

#endif // CONSUMABLE_H
