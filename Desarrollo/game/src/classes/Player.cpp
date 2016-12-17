#include "Player.h"

Player::Player()
{
    //ctor
}

Player::~Player()
{
    //dtor
}

/////////////
void Player::update()
{
    Drawable::setPosition(dwe::vec3f(getPosEntity().x, getPosition().y, getPosEntity().z));
}

////////////////////
const char* Player::getNetObjectID() const
{
    return "Player";
}

/////////////
void Player::render()
{
    // TODO
}

/////////////
void Player::shoot()
{
    //TODO
}

/////////////
void Player::throwGrenade()
{
    // TODO
}

////////////
int Player::getAmmo(int numWeapon) { return m_ammo[numWeapon]; }
void Player::setAmmo(int numWeapon, int ammount) { m_ammo[numWeapon] = ammount; }

////////////
int Player::getGrenades() { return m_grenades; }
void Player::setGrenades(int n) { m_grenades = n; }

/////////////
void Player::setPosition(dwe::vec3f p)
{
    setPosEntity(p, getRotation().y);
    Drawable::setPosition(p);
}


