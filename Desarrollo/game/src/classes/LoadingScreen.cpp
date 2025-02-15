#include "LoadingScreen.h"
#include "GraphicsEngine.h"
#include "GUI.h"
#include "AudioEngine.h"

LoadingScreen::LoadingScreen() :
    m_initialized(false),
    m_background(0),
    m_loadingSprite(0),
    m_progress(0)
{
    AEInstance->Play2D("media/Sounds/gamestarts.wav", 0.3);
}

LoadingScreen::~LoadingScreen()
{
    Destroy();
}

LoadingScreen* LoadingScreen::getInstance()
{
  static LoadingScreen instance;

  return &instance;
}

void LoadingScreen::Init(int numSteps)
{
    // Calculo incremento
    m_progressIncrement = 1.0/(numSteps-1);

    uint16_t anchoBarra = 795;

    m_loadingSprite = new dwe::Sprite("LoadingScreen/Barra", GEInstance->get_screenWidth()/2 - anchoBarra/2, GEInstance->get_screenHeight()*0.8);
    m_progress = new dwe::RectangleShape("LoadingScreen/progreso", GEInstance->get_screenWidth()/2 - anchoBarra/2 +190, GEInstance->get_screenHeight()*0.8+4, 600.0, 45.0);
    m_progressScale = 0.0;
    m_progress->SetScale(m_progressScale,1);
    m_background = new dwe::Background("LoadingScreen/Loading");

    m_initialized = true;
}

void LoadingScreen::Destroy()
{
    if (m_background)
    {
        delete m_background;
        m_background = 0;
    }
    if (m_loadingSprite)
    {
        delete m_loadingSprite;
        m_loadingSprite = 0;
    }
    if (m_progress)
    {
        delete m_progress;
        m_progress = 0;
    }

    m_initialized = false;
}

void LoadingScreen::AddProgress()
{
    GEInstance->isRunning();
    if (m_initialized)
    {
        m_progress->SetScale(m_progressScale,1);
        m_progressScale += m_progressIncrement;
        //std::cout << "addprogress\n";  // decomentar para contar el numero de veces que se llama

        Draw();
    }
    else
        std::cerr << "(LoadingScreen::AddProgress) No se ha inicializado o se ha borrado antes de la llamada.\n";
}

void LoadingScreen::Draw()
{
    GEInstance->push();

    GEInstance->clearWindow();
    m_background->draw();
    m_progress->draw();
    m_loadingSprite->draw();
    GEInstance->displayWindow();

    GEInstance->pop();
}
