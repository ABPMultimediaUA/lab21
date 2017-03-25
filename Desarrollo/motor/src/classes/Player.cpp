#include "Player.h"

Player::Player(Gun* gun)
{
}

Player::~Player()
{
    //dtor
}

/////////////
void Player::update()
{
}

/////////////
void Player::setNode(dwe::Node* n)
{
    Drawable::setNode(n);
}

/////////////
void Player::setPosition(dwe::vec3f p)
{
    Drawable::setPosition(p);
}

/////////////
void Player::render()
{
    // TODO
}

/////////////
void Player::readEvents()
{
}
