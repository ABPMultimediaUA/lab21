#ifndef PLAYERMATE_H
#define PLAYERMATE_H

#include "DrawableReplica.h"
#include "FachadeDireEngine.h"

class PlayerMate : public dwn::DrawableReplica
{
    public:
        PlayerMate();
        virtual ~PlayerMate();

        virtual void update();
        virtual void render();

        // Getters, Setters
        virtual dwe::vec3f getShift();
        virtual void setShift(dwe::vec3f s);
        virtual unsigned short int getHealth();
        virtual void setHealth(unsigned short int h);
        virtual bool getHasRifle();
        virtual void setHasRifle(unsigned short int h);
        virtual bool getHasShotgun();
        virtual void setHasShotgun(unsigned short int h);
        virtual unsigned short int getNumGrenades();
        virtual void setNumGrenades(unsigned short int n);
        virtual unsigned short int getNumMedkits();
        virtual void setNumMedkits(unsigned short int n);

    protected:

    private:
        dwe::vec3f          m_shift; // Desplazamiento respecto del movimiento anterior
        unsigned short int  m_health;
        bool                m_hasRifle;
        bool                m_hasShotgun;
        unsigned short int  m_numGrenades;
        unsigned short int  m_numMedkits;


};

#endif // PLAYERMATE_H
