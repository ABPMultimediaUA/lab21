#include "Player.h"
#include "WorldInstance.h"

Player::Player()
{
    setClassID(CLASS_PLAYER_ID);
    m_mKeys[0]=false;
    m_hasSpeedBoost = false;
}

Player::~Player()
{
    //dtor
}

/////////////
void Player::update()
{
    Drawable::setPosition(dwe::vec3f(getPosEntity().x, getPosition().y, getPosEntity().z));

    //RECUPERAR VIDA
    int posX = Drawable::getPosition().x;
    int posZ = Drawable::getPosition().z;
    if( posX > 392 && posX < 408 && posZ > -8 && posZ < 8){
        setLife(100);
        cout << "Vida recuperada: " << getLife() << endl;
    }
}

/////////////
void Player::setNode(dwe::Node* n)
{
    Drawable::setNode(n);
    createDynamicBody(getPosition());
}

/////////////
void Player::setPosition(dwe::vec3f p)
{
    setPosEntity(p, getRotation().y);
    Drawable::setPosition(p);
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

/////////////
void Player::readEvents()
{
    CharacterController::readEvents();

    //Animacion del player
    if(getSpeedX()!=0 || getSpeedZ()!=0)
    {
        if(GEInstance->receiver.isKeyDown(KEY_LSHIFT))
            setAnimation(dwe::eAnimWalk);
        else
            setAnimation(dwe::eAnimRun);
    }
    else
    {
        setAnimation(dwe::eAnimStand);
    }

    setVelocity(dwe::vec3f(getSpeedX(), 0, getSpeedZ()));


    //Calcular rotacion player - con MOUSE
    if(GEInstance->receiver.getCursorX()>=0 && GEInstance->receiver.getCursorY()>=0){
        setRotation(
            World->from2Dto3D(GEInstance->receiver.getCursorX(),
                              GEInstance->receiver.getCursorY(),
                              getRotation()));
    }
}


////////////
int Player::getAmmo(int numWeapon) { return m_ammo[numWeapon]; }
void Player::setAmmo(int numWeapon, int ammount) { m_ammo[numWeapon] = ammount; }

////////////
int Player::getGrenades() { return m_grenades; }
void Player::setGrenades(int n) { m_grenades = n; }
void Player::setMKeys(int id){  m_mKeys[id]=true; }
bool Player::getMKey(int n){ return m_mKeys[n]; }

////////////
int Player::getLife() { return m_life; }
void Player::setLife(int n) { m_life = n; }


/////////////
void Player::onBeginContact(EntityPhysics* otherObject)
{
}

bool Player::getHasSpeedBoost()
{
    return m_hasSpeedBoost;
}

void Player::setHasSpeedBoost(bool s)
{
    m_hasSpeedBoost = s;
}
