#include "GUI.h"

#include "GraphicsEngine.h"

/*************Fachada SFML*******************/
/***Boton INI***/
dwe::Button::Button(std::string t, int x, int y)
{
    this->x=x;
    this->y=y;
    font.loadFromFile("media/8bit.ttf"); // La fuente se puede modificar en cualquier momento
    text.setFont(font);
    text.setString(t);
    text.setCharacterSize(18);
    text.setColor(sf::Color::White);
    text.setPosition(x, y); // 200, 150
}

dwe::Button::~Button(){};

void dwe::Button::draw()
{
    //GEInstance->drawText(text);
}

int dwe::Button::getXOrigin()
{
    return x;
}

int dwe::Button::getYOrigin()
{
    return y;
}

int dwe::Button::getWidth()
{
    return x+text.getGlobalBounds().width;
}

int dwe::Button::getHeight()
{
    return y+text.getGlobalBounds().height;
}
/***Boton FIN***/

/**Fondo INI***/
dwe::Background::Background(std::string s)
{
    rs.setSize(sf::Vector2f(GEInstance->get_screenWidth(), GEInstance->get_screenHeight()));
    texture.loadFromFile("media/menu"+s+".jpg");
    rs.setTexture(&texture, true);
}

dwe::Background::~Background(){};

void dwe::Background::draw()
{
    //GEInstance->drawRectangleShape(rs);
}
/***Fondo FIN***/

/***AchievementInfo INI***/
dwe::AchievementInfo::AchievementInfo(std::string n)
{
    texture.loadFromFile("media/achievement"+n+"info.png");
    sp.setTexture(texture, true);
}

dwe::AchievementInfo::~AchievementInfo(){};

void dwe::AchievementInfo::draw()
{
    //GEInstance->drawSprite(sp);
}

void dwe::AchievementInfo::setPosition()
{
    sp.setPosition(GEInstance->receiver.getCursorX(), GEInstance->receiver.getCursorY());
}
/***AchievementInfo FIN***/

/***Achievement INI***/
dwe::Achievement::Achievement(std::string n, int x, int y, Condition* con) : achinfo(n)
{
    this->x=GEInstance->get_screenWidth()*x;
    this->y=GEInstance->get_screenHeight()*y;
    achieved=false; //Crear sistema logros para variar sprites
    texture.loadFromFile("media/achievement"+n+"locked.png");
    textureAchieved.loadFromFile("media/achievement"+n+"unlocked.png");
    sp.setTexture(texture, true);
    sp.setPosition(x, y);
    condition = con;
}

dwe::Achievement::~Achievement(){};

void dwe::Achievement::draw()
{
    //GEInstance->drawSprite(sp);
}

void dwe::Achievement::hovered()
{
    if(GEInstance->receiver.getCursorX()>x && GEInstance->receiver.getCursorY()>y && GEInstance->receiver.getCursorX()<x+sp.getGlobalBounds().width && GEInstance->receiver.getCursorY()<y+sp.getGlobalBounds().height)
    {
        achinfo.setPosition();
        achinfo.draw();
    }
}

void dwe::Achievement::drawInfo()
{
    hovered();
}

bool dwe::Achievement::getAchieved()
{
    return achieved;
}

 bool dwe::Achievement::testAchieved()
 {
    return condition->test();
 }

void dwe::Achievement::setAchieved()
{
     achieved=true;
     sp.setTexture(textureAchieved, true);
}
/***Achievement FIN***/

dwe::ConditionEnemiesKilled::ConditionEnemiesKilled(int en)
{
    enemies = en;
}

bool dwe::ConditionEnemiesKilled::test()
{
    if(GEInstance->achievementsHandler.getEnemiesKilled()>=enemies)
        return true;
    return false;
}
