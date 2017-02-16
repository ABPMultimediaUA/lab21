#ifndef HUD_H
#define HUD_H

#include <Drawable.h>
#include <GraphicsEngine.h>
#include <Player.h>



class Hud : public Drawable
{
    public:

        Hud(dwe::GraphicsEngine::GETexture* t);
        virtual ~Hud();
        virtual void update(){};
        virtual void render(){};
        virtual void draw();

    protected:

    private:
};

#endif // HUD_H
