#ifndef HUD_H
#define HUD_H

#include <Drawable.h>
#include <GraphicsEngine.h>
#include <Player.h>

namespace dwe
{
    class WeaponBox;
    class HealthBox;
}

class Hud : public Drawable
{
    public:

        Hud();
        virtual ~Hud();

        virtual void update(){};
        virtual void render(){};
        virtual void draw();


    protected:

    private:

        dwe::WeaponBox *WeaponBox;

        dwe::HealthBox *HealthBox;

        Player* mainPlayer;


};

#endif // HUD_H
