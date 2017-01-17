#ifndef SPEEDBOOST_H
#define SPEEDBOOST_H

#include "Entity.h"

class SpeedBoost : public Entity
{
    public:

        SpeedBoost(int i);

        virtual ~SpeedBoost();

        int getId();

        virtual void render();

        virtual void update();


    protected:

    private:

        int id;
};

#endif // SPEEDBOOST_H
