#ifndef FLOOR_H
#define FLOOR_H

#include "Drawable.h"


class Floor: public Drawable
{
    public:
        Floor();
        virtual ~Floor();
        void update(){};
        void render(){};

    protected:

    private:
};

#endif // FLOOR_H
