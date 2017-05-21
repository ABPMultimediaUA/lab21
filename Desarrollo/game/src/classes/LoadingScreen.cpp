#include "LoadingScreen.h"
#include "GraphicsEngine.h"
#include "GUI.h"

LoadingScreen::LoadingScreen() :
    m_initialized(false),
    m_background(0),
    m_loadingSprite(0),
    m_progress(0)
{
    //ctor
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

    m_loadingSprite = new dwe::Sprite("LoadingScreen/Barra", GEInstance->get_screenWidth()*0.1, GEInstance->get_screenHeight()*0.8);
    m_progress = new dwe::Sprite("LoadingScreen/progreso", GEInstance->get_screenWidth()*0.1+4, GEInstance->get_screenHeight()*0.8+4);
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
    m_loadingSprite->draw();
    m_progress->draw();
    GEInstance->displayWindow();

    GEInstance->pop();
}
