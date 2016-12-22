#ifndef MAGNETKEY_H
#define MAGNETKEY_H
#include "Entity.h"


class MagnetKey: public Entity
{
    public:
        MagnetKey(int i);
        virtual ~MagnetKey();
        int getId();

        virtual void render();
        virtual void update();

    protected:

    private:
        int id;
        bool onPlayer;
};

#endif // MAGNETKEY_H
