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


void dwe::HudBox::setComponents(std::string str, sf::Sprite *s, sf::Texture *t, float px, float py)
{
    t->loadFromFile(str);
    s->setTexture(*t, true);

    s->setOrigin(0,0);
    s->setPosition(px, py);
}


dwe::WeaponBox::WeaponBox( float x, float y)
{
    int   width   = GEInstance->get_screenWidth();
    int   height  = GEInstance->get_screenHeight();

    t = 2000;
    grenades = 2;
    ammoGun = 20;
    ammoRifle = 10;
    ammoShotgun = 10;

    /**** Caja base ****/
    setComponents("media/CuadroArma.png", &s_box, &t_box, x, y);

    /**** Arma ****/
    setComponents("media/grenade.png", &s_weapon, &t_weapon, s_box.getPosition().x, s_box.getPosition().y );

    /**** Munición del arma actual ****/
    font.loadFromFile("media/exoregular.otf");
    text_ammo.setFont(font);
    text_ammo.setCharacterSize(15);
    text_ammo.setColor(sf::Color::White);
    text_ammo.setPosition(s_box.getPosition().x + width/9, height*7.3/8);

    std::stringstream sw;
    sw << "x" << grenades;
    text_ammo.setString(sw.str());

}

dwe::WeaponBox::~WeaponBox(){};

void dwe::WeaponBox::draw()
{
    GEInstance->drawSprite(s_box);

    swapWeapon(&t_weapon, &text_ammo);

    GEInstance->drawSprite(s_weapon);

    GEInstance->drawText(text_ammo);
}

void dwe::WeaponBox::swapWeapon(sf::Texture *tweapon, sf::Text *textammo)
{

    // Según el arma que haya en el momento, cambiamos la imagen y la cantidad disponible
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num1) && (clock() - t)> 200)
        updateWeapon(tweapon, "media/grenade.png", &grenades, textammo);


    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num2) && (clock() - t)> 200)
        updateWeapon(tweapon, "media/cosa2.png", &ammoGun, textammo);


    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num3) && (clock() - t)> 200)
        updateWeapon(tweapon, "media/cosa3.png", &ammoRifle, textammo);


    // Ponmos textura, posicion, etc del arma
    s_weapon.setTexture(*tweapon, true);
    s_weapon.setOrigin(0,0);
    s_weapon.setPosition(s_box.getPosition().x, s_box.getPosition().y + 2);

}

void dwe::WeaponBox::updateWeapon (sf::Texture *tweapon, std::string str, int *ammo, sf::Text *textammo)
{
    std::stringstream sw;
    tweapon->loadFromFile(str);
    sw << "x" << *ammo;
    textammo->setString(sw.str());
}

dwe::HealthBox::HealthBox(float x, float y)
{
    int   width   = GEInstance->get_screenWidth();
    int   height  = GEInstance->get_screenHeight();

    max_health = 100;
    health = max_health;
    heals = 10;

    t = 2000;

    /**** Texto de Vida actual / Vida total ****/
    font.loadFromFile("media/exoregular.otf");
    text_health.setFont(font);
    text_health.setCharacterSize(15);
    text_health.setColor(sf::Color::White);
    text_health.setPosition(width - width/4.25, height*6.8/8);

    /**** Texto de Botiquines ****/
    text_heal.setFont(font);
    text_heal.setCharacterSize(15);
    text_heal.setColor(sf::Color::White);
    text_heal.setPosition(height - width/7, height*7.2/8);

    /**** Caja base ****/
    setComponents("media/CuadroVida.png", &s_box, &t_box, x, y);

    /**** Vida perdida ****/
    setComponents("media/VidaPerdida.png", &s_hplost, &t_hplost, s_box.getPosition().x + 6, s_box.getPosition().y + 6);

    /**** Vida actual ****/
    t_health.loadFromFile("media/VidaLlena.png");
    s_health.setTexture(&t_health, true);
    s_health.setOrigin(0,0);
    s_health.setPosition(s_box.getPosition().x + 7, s_box.getPosition().y + 6);

    /**** Contorno vida ****/
    setComponents("media/ContornoVida.png", &s_edge, &t_edge, s_box.getPosition().x + 6, s_box.getPosition().y + 6);

    /**** Botiquines ****/
    setComponents("media/Botiquines.png", &s_heal, &t_heal, s_box.getPosition().x + 110, s_box.getPosition().y + 33);

}

dwe::HealthBox::~HealthBox() {}

void dwe::HealthBox::draw()
{
    // Perder vida
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && (clock() - t)> 200 && health > 0)
    {
        health -= 10;
        t = clock();
    }
    // Ganar vida
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && (clock() - t)> 200 && health < 100)
    {
        health += 10;
        t = clock();
    }

    // Coger botiquin
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D) && (clock() - t)> 200 && heals > 0)
    {
        heals -= 1;
        t = clock();
    }
    // Usar botiquín
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::F) && (clock() - t)> 200 && heals < 20)
    {
        heals += 1;
        t = clock();
    }

    /////////////////////

    GEInstance->drawSprite(s_box);

    GEInstance->drawSprite(s_hplost);

    drawCurrentHealth();

    GEInstance->drawSprite(s_edge);

    GEInstance->drawSprite(s_heal);

    drawNumberOfHeals();
}


void dwe::HealthBox::drawCurrentHealth()
{

    float hpn = health;
    float hpmn = max_health;

    // Actualizamos sprite de vida
    float c = ((hpn/hpmn) * 100 *1.8) ;
    s_health.setSize(sf::Vector2f(c , 22));
    sf::Rect<int> rect = s_health.getTextureRect();
    rect.width = c;
    s_health.setTextureRect(rect);

    // Actualizamos texto Vida Actual / Vida Total
    std::stringstream ss;
    ss << hpn<<"/"<<hpmn << " HP";
    text_health.setString(ss.str());

    // Dibujamos
    GEInstance->drawRectangleShape(s_health);
    GEInstance->drawText(text_health);
}

void dwe::HealthBox::drawNumberOfHeals()
{
    std::stringstream sh;
    sh << "x" << heals;
    text_heal.setString(sh.str());

    GEInstance->drawText(text_heal);
}
