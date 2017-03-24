#ifndef PLAYER_H
#define PLAYER_H

#include "Drawable.h"


class Player : public Drawable
{
    public:
        Player(Gun* gun);
        virtual ~Player();

        void update();
        void render();
        void shoot();
        void throwGrenade();

        virtual void readEvents();


        // Getters & Setters
        virtual void setNode(dwe::Node* n);   // Necesario para EntityPhysics

        virtual void setPosition(dwe::vec3f p);

    protected:

    private:
};

#endif // PLAYER_H
