#ifndef WHOLE_H
#define WHOLE_H

#include <Enemy.h>


class Whole : public Enemy
{
    public:
        Whole();
        virtual ~Whole();

        virtual void update() {};
        virtual void render() {};

    protected:

    private:
};

#endif // WHOLE_H
