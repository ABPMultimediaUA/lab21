#include "Player.h"

Player::Player()
{
    //ctor
    createDynPhyEntity(dwe::vec3f(0,0,0));
}

Player::~Player()
{
    //dtor
}

/////////////
void Player::update()
{
    // TODO
    Drawable::setPosition(dwe::vec3f(getBwBody()->GetPosition().x, getPosition().y, getBwBody()->GetPosition().y));
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
    getBwBody()->SetTransform(b2Vec2(p.x, p.z), getRotation().y);
    Drawable::setPosition(p);
}

/////////////
void Player::setVelocity(dwe::vec3f p)
{
    getBwBody()->SetLinearVelocity(b2Vec2(p.x, p.z));
}


