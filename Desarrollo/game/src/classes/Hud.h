#ifndef HUD_H
#define HUD_H

#include <GraphicsEngine.h>
#include <Player.h>

namespace dwe
{
    class WeaponBox;
    class HealthBox;
}

class Hud
{
    public:

        Hud();
        virtual ~Hud();

        virtual void draw();


    protected:

    private:

        dwe::WeaponBox *WeaponBox;

        dwe::HealthBox *HealthBox;

        Player* mainPlayer;


};

#endif // HUD_H
