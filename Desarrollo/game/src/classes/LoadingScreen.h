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
        ~LoadingScreen(); // No virtual, no debe tener clases heredadas

        void AddProgress();

        static LoadingScreen* getInstance();

        void Init(int numSteps);
        void Destroy();

    protected:

    private:
        bool                m_initialized;
        float               m_progressScale;
        float               m_progressIncrement;
        dwe::Background*    m_background;
        dwe::Sprite*        m_loadingSprite;
        dwe::Sprite*        m_progress;

        void Draw();
};

#endif // LOADINGSCREEN_H
