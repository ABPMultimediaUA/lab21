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
    GEInstance->drawText(text);
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
    texture.loadFromFile("media/"+s+".jpg");
    rs.setTexture(&texture, true);
}

dwe::Background::~Background(){};

void dwe::Background::draw()
{
    GEInstance->drawRectangleShape(rs);
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
    GEInstance->drawSprite(sp);
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

    t = 4;

    /**** Caja base ****/
    //setComponents("media/HUDArma.png", &s_box, &t_box, x, y);
    s_box = AnimatedSprite(sf::seconds(0.1), true, false);
    s_box.setPosition(x,y);
    s_box.setScale(0.5,0.5);

    t_box.loadFromFile("media/HUDWeaponSpriteSheet.png");
    weaponBoxAnim.setSpriteSheet(t_box);

    setWeaponBoxAnimation ();


    /**** Arma ****/
    setComponents("media/Gun.png", &s_weapon, &t_weapon, s_box.getPosition().x + 20, s_box.getPosition().y + 40 );
    s_weapon.setScale(0.7, 0.7);

    /**** Granada ****/
    setComponents("media/Grenade.png", &s_grenade, &t_grenade, s_box.getPosition().x + 100, s_box.getPosition().y + 120 );
    s_grenade.setScale(0.5, 0.5);

    /**** Munici�n del arma actual ****/
    font.loadFromFile("media/exoregular.otf");
    text_ammo.setFont(font);
    text_ammo.setCharacterSize(15);
    text_ammo.setColor(sf::Color::White);
    text_ammo.setPosition(s_box.getPosition().x + 65, s_box.getPosition().y + 100);

    /**** Cantidad de granadas ****/
    text_grenades.setFont(font);
    text_grenades.setCharacterSize(15);
    text_grenades.setColor(sf::Color::White);
    text_grenades.setPosition(s_box.getPosition().x + 150, s_box.getPosition().y + 130);

    s_box.play(weaponBoxAnim);
}

dwe::WeaponBox::~WeaponBox(){};

void dwe::WeaponBox::draw(FirearmKind weapon, int ammo, int grenades)
{

    s_box.update(frameTime);

    GEInstance->drawAnimatedSprite(s_box);

    swapWeapon(weapon, ammo, &t_weapon, &text_ammo);

    GEInstance->drawSprite(s_weapon);

    GEInstance->drawText(text_ammo);

    setText(&text_grenades, grenades);

    GEInstance->drawText(text_grenades);

    GEInstance->drawSprite(s_grenade);

}

void dwe::WeaponBox::swapWeapon(FirearmKind weapon, int ammo, sf::Texture *tweapon, sf::Text *textammo)
{

    // Seg�n el arma que haya en el momento, cambiamos la imagen y la cantidad disponible
    if (weapon == eGun)
        updateWeapon(tweapon, "media/Gun.png", ammo, textammo);


    else if (weapon == eRifle)
        updateWeapon(tweapon, "media/Rifle.png", ammo, textammo);


    else if (weapon == eShotgun)
        updateWeapon(tweapon, "media/Shotgun.png", ammo, textammo);


    // Ponmos textura, posicion, etc del arma
    s_weapon.setTexture(*tweapon, true);
    s_weapon.setOrigin(0,0);
    s_weapon.setPosition(s_box.getPosition().x + 20, s_box.getPosition().y + 40);


    if (( GEInstance->receiver.isKeyDown(KEY_WEAPON_1)
        || (GEInstance->receiver.isKeyDown(KEY_WEAPON_2)) && (weapon == eShotgun)
        || (GEInstance->receiver.isKeyDown(KEY_WEAPON_3)) && (weapon == eRifle))
        && (clock() - t) > 200)
    {
        animateWeaponBox();
        frameTime = frameClock.restart();
        t = clock();

        if (clock() - t > 4000)
        {
            s_box.stop();
        }

    }


}

void dwe::WeaponBox::animateWeaponBox()
{
    s_box.play(weaponBoxAnim);
}

void dwe::WeaponBox::updateWeapon (sf::Texture *tweapon, std::string str, int ammo, sf::Text *textammo)
{
    std::stringstream sw;
    tweapon->loadFromFile(str);
    sw << "x" << ammo;
    textammo->setString(sw.str());
}

void dwe::WeaponBox::setText(sf::Text *text, int num)
{
    std::stringstream sw;
    sw << "x" << num;
    text->setString(sw.str());

}

void dwe::WeaponBox::setWeaponBoxAnimation()
{
    weaponBoxAnim.addFrame(sf::IntRect(0, 0, 300, 300));
    weaponBoxAnim.addFrame(sf::IntRect(300, 0, 300, 300));
    weaponBoxAnim.addFrame(sf::IntRect(600, 0, 300, 300));
    weaponBoxAnim.addFrame(sf::IntRect(900, 0, 300, 300));
    weaponBoxAnim.addFrame(sf::IntRect(1200, 0, 300, 300));

    weaponBoxAnim.addFrame(sf::IntRect(1500, 0, 300, 300));
    weaponBoxAnim.addFrame(sf::IntRect(1800, 0, 300, 300));
    weaponBoxAnim.addFrame(sf::IntRect(2100, 0, 300, 300));
    weaponBoxAnim.addFrame(sf::IntRect(2400, 0, 300, 300));
    weaponBoxAnim.addFrame(sf::IntRect(2700, 0, 300, 300));

    weaponBoxAnim.addFrame(sf::IntRect(3000, 0, 300, 300));
    weaponBoxAnim.addFrame(sf::IntRect(3300, 0, 300, 300));
    weaponBoxAnim.addFrame(sf::IntRect(3600, 0, 300, 300));
    weaponBoxAnim.addFrame(sf::IntRect(3900, 0, 300, 300));
    weaponBoxAnim.addFrame(sf::IntRect(4200, 0, 300, 300));

    weaponBoxAnim.addFrame(sf::IntRect(0, 300, 300, 300));
    weaponBoxAnim.addFrame(sf::IntRect(300, 300, 300, 300));
    weaponBoxAnim.addFrame(sf::IntRect(600, 300, 300, 300));
    weaponBoxAnim.addFrame(sf::IntRect(900, 300, 300, 300));
    weaponBoxAnim.addFrame(sf::IntRect(1200, 300, 300, 300));

    weaponBoxAnim.addFrame(sf::IntRect(1500, 300, 300, 300));
    weaponBoxAnim.addFrame(sf::IntRect(1800, 300, 300, 300));
    weaponBoxAnim.addFrame(sf::IntRect(2100, 300, 300, 300));
    weaponBoxAnim.addFrame(sf::IntRect(2400, 300, 300, 300));
    weaponBoxAnim.addFrame(sf::IntRect(2700, 300, 300, 300));

    weaponBoxAnim.addFrame(sf::IntRect(3000, 300, 300, 300));
    weaponBoxAnim.addFrame(sf::IntRect(3300, 300, 300, 300));
    weaponBoxAnim.addFrame(sf::IntRect(3600, 300, 300, 300));
    weaponBoxAnim.addFrame(sf::IntRect(3900, 300, 300, 300));
    weaponBoxAnim.addFrame(sf::IntRect(4200, 300, 300, 300));

    weaponBoxAnim.addFrame(sf::IntRect(0, 600, 300, 300));
    weaponBoxAnim.addFrame(sf::IntRect(300, 600, 300, 300));
    weaponBoxAnim.addFrame(sf::IntRect(600, 600, 300, 300));
    weaponBoxAnim.addFrame(sf::IntRect(900, 600, 300, 300));
    weaponBoxAnim.addFrame(sf::IntRect(1200, 600, 300, 300));

    weaponBoxAnim.addFrame(sf::IntRect(1500, 600, 300, 300));
    weaponBoxAnim.addFrame(sf::IntRect(1800, 600, 300, 300));
    weaponBoxAnim.addFrame(sf::IntRect(2100, 600, 300, 300));
    weaponBoxAnim.addFrame(sf::IntRect(2400, 600, 300, 300));
    weaponBoxAnim.addFrame(sf::IntRect(2700, 600, 300, 300));

    weaponBoxAnim.addFrame(sf::IntRect(3000, 600, 300, 300));
    weaponBoxAnim.addFrame(sf::IntRect(3300, 600, 300, 300));
    weaponBoxAnim.addFrame(sf::IntRect(3600, 600, 300, 300));
    weaponBoxAnim.addFrame(sf::IntRect(3900, 600, 300, 300));
    weaponBoxAnim.addFrame(sf::IntRect(4200, 600, 300, 300));

    weaponBoxAnim.addFrame(sf::IntRect(0, 900, 300, 300));
    weaponBoxAnim.addFrame(sf::IntRect(300, 900, 300, 300));
    weaponBoxAnim.addFrame(sf::IntRect(600, 900, 300, 300));
    weaponBoxAnim.addFrame(sf::IntRect(900, 900, 300, 300));
    weaponBoxAnim.addFrame(sf::IntRect(1200, 900, 300, 300));

    weaponBoxAnim.addFrame(sf::IntRect(1500, 900, 300, 300));
    weaponBoxAnim.addFrame(sf::IntRect(1800, 900, 300, 300));
    weaponBoxAnim.addFrame(sf::IntRect(2100, 900, 300, 300));
    weaponBoxAnim.addFrame(sf::IntRect(2400, 900, 300, 300));
    weaponBoxAnim.addFrame(sf::IntRect(2700, 900, 300, 300));

    weaponBoxAnim.addFrame(sf::IntRect(3000, 900, 300, 300));
    weaponBoxAnim.addFrame(sf::IntRect(3300, 900, 300, 300));
    weaponBoxAnim.addFrame(sf::IntRect(3600, 900, 300, 300));
    weaponBoxAnim.addFrame(sf::IntRect(3900, 900, 300, 300));
    weaponBoxAnim.addFrame(sf::IntRect(4200, 900, 300, 300));

    weaponBoxAnim.addFrame(sf::IntRect(0, 1200, 300, 300));
    weaponBoxAnim.addFrame(sf::IntRect(300, 1200, 300, 300));
    weaponBoxAnim.addFrame(sf::IntRect(600, 1200, 300, 300));
    weaponBoxAnim.addFrame(sf::IntRect(900, 1200, 300, 300));
    weaponBoxAnim.addFrame(sf::IntRect(1200, 1200, 300, 300));

    weaponBoxAnim.addFrame(sf::IntRect(1500, 1200, 300, 300));
    weaponBoxAnim.addFrame(sf::IntRect(1800, 1200, 300, 300));
    weaponBoxAnim.addFrame(sf::IntRect(2100, 1200, 300, 300));
    weaponBoxAnim.addFrame(sf::IntRect(2400, 1200, 300, 300));
    weaponBoxAnim.addFrame(sf::IntRect(2700, 1200, 300, 300));

    weaponBoxAnim.addFrame(sf::IntRect(3000, 1200, 300, 300));
    weaponBoxAnim.addFrame(sf::IntRect(3300, 1200, 300, 300));
    weaponBoxAnim.addFrame(sf::IntRect(3600, 1200, 300, 300));
    weaponBoxAnim.addFrame(sf::IntRect(3900, 1200, 300, 300));
    weaponBoxAnim.addFrame(sf::IntRect(4200, 1200, 300, 300));

}

dwe::HealthBox::HealthBox(float x, float y)
{
    int   width   = GEInstance->get_screenWidth();
    int   height  = GEInstance->get_screenHeight();


    /**** Caja base ****/
    setComponents("media/HUDVida.png", &s_box, &t_box, x, y);

    /**** Vida perdida ****/
    setComponents("media/HUDBarraVidaPerdida.png", &s_hplost, &t_hplost, s_box.getPosition().x + 60, s_box.getPosition().y + 30);
    s_hplost.setScale(1.04, 0.9);

    /**** Vida actual ****/
    t_health.loadFromFile("media/HUDBarraVida.png");
    s_health.setTexture(&t_health, true);
    s_health.setOrigin(0,0);
    s_health.setPosition(s_box.getPosition().x + 60, s_box.getPosition().y + 30);

    /**** Contorno vida ****/
    //setComponents("media/ContornoVida.png", &s_edge, &t_edge, s_box.getPosition().x + 6, s_box.getPosition().y + 6);

    /**** Botiquines ****/
    setComponents("media/HUDHeal.png", &s_heal, &t_heal, s_box.getPosition().x + 65, s_box.getPosition().y + 5);

    /**** Texto de Vida actual / Vida total ****/
    font.loadFromFile("media/exoregular.otf");
    text_health.setFont(font);
    text_health.setCharacterSize(9);
    text_health.setColor(sf::Color::White);
    text_health.setPosition(s_box.getPosition().x + 100, s_box.getPosition().y + 30);

    /**** Texto de Botiquines ****/
    text_heal.setFont(font);
    text_heal.setCharacterSize(12);
    text_heal.setColor(sf::Color::White);
    text_heal.setPosition(s_box.getPosition().x + 90, s_box.getPosition().y + 10);

}

dwe::HealthBox::~HealthBox() {}

void dwe::HealthBox::draw(int medkits, int health, int maxHealth)
{


    /////////////////////

    GEInstance->drawSprite(s_box);

    GEInstance->drawSprite(s_hplost);

    drawCurrentHealth(health, maxHealth);

    //GEInstance->drawSprite(s_edge);

    GEInstance->drawSprite(s_heal);

    drawNumberOfMedkits(medkits);
}


void dwe::HealthBox::drawCurrentHealth(int health, int maxHealth)
{

    float hpn   = health;
    float hpmn  = maxHealth;

    // Actualizamos sprite de vida
    float c     = ((hpn/hpmn) * 100 *1.2) ;
    s_health.setSize(sf::Vector2f(c , 10));
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

void dwe::HealthBox::drawNumberOfMedkits(int medkits)
{
    std::stringstream sh;
    sh << "x" << medkits;
    text_heal.setString(sh.str());

    GEInstance->drawText(text_heal);
}
