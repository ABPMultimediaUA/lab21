#ifndef PLAYERMATE_H
#define PLAYERMATE_H

#include <Drawable.h>
#include <FachadeDireEngine.h>


class PlayerMate : public Drawable
{
    public:
        PlayerMate();
        virtual ~PlayerMate();

        // Getters, Setters
        dwe::vec3f getShift();
        void setShift(dwe::vec3f s);
        unsigned short int getHealth();
        void setHealth(unsigned short int h);
        bool getHasRifle();
        void setHasRifle(unsigned short int h);
        bool getHasShotgun();
        void setHasShotgun(unsigned short int h);
        unsigned short int getNumGrenades();
        void setNumGrenades(unsigned short int n);
        unsigned short int getNumMedkits();
        void setNumMedkits(unsigned short int n);

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
