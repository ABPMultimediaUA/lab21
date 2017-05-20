#include "LoadingScreen.h"
#include "GraphicsEngine.h"
#include "GUI.h"

LoadingScreen::LoadingScreen()
{
    //ctor
}

LoadingScreen* LoadingScreen::getInstance()
{
  static LoadingScreen instance;

  return &instance;
}

void LoadingScreen::Init()
{
    m_loadingSprite = new dwe::Sprite("LoadingScreen/Barra1", GEInstance->get_screenWidth()*0.1, GEInstance->get_screenHeight()*0.8);
    m_background = new dwe::Background("LoadingScreen/Loading");
}

LoadingScreen::~LoadingScreen()
{
    delete m_loadingSprite;
    delete m_background;
}

void LoadingScreen::LoadingDraw(std::string s)
{
    std::cout<<s<<std::endl;
    m_loadingSprite->SetTexture(s);
    GEInstance->clearWindow();
    m_background->draw();
    m_loadingSprite->draw();
    GEInstance->displayWindow();
}
