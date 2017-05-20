#ifndef LOADINGSCREEN_H
#define LOADINGSCREEN_H

#include <string>

namespace dwe
{
    class Background;
    class Sprite;
}

class LoadingScreen
{
    public:

        LoadingScreen();

        void LoadingDraw(std::string s);

        static LoadingScreen* getInstance();

        void Init();

        virtual ~LoadingScreen();

    protected:

    private:

        dwe::Background* m_background;
        dwe::Sprite* m_loadingSprite;
};

#endif // LOADINGSCREEN_H
