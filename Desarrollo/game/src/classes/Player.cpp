#include "Player.h"
#include "WorldInstance.h"

Player::Player()
{
    Gun* gun = new Gun();
    setClassID(CLASS_PLAYER_ID);
    m_mKeys[0]=false;
    m_medkits = 0;
    m_timeMedkit = 2000;
    m_timeGivingStuff = 1000;
    m_timeWeaponSwap = 1000;
    m_hasGun = true;
    m_weapons[0] = gun;
    m_hasShotgun = false;
    m_hasRifle = false;
    m_currentWeapon = eGun;

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
FirearmKind Player::getCurrentWeapon() { return m_currentWeapon; }
Firearm* Player::getPlayerWeapons() { return *m_weapons; }
bool Player::getHasShotgun() { return m_hasShotgun; }
bool Player::getHasRifle() { return m_hasRifle; }

/////////////
void Player::addWeapon(Consumable* weapon, FirearmKind type)
{

    if (!m_hasShotgun && type == eShotgun)
    {
        //m_weapons.push_back(weapon);
        m_weapons[1] = new Shotgun();

        m_hasShotgun = true;
    }

    if (!m_hasRifle && type == eRifle)
    {
        //m_weapons.push_back(weapon);
        m_weapons[2] = new Rifle();

        m_hasRifle = true;
    }


}

/////////////
void Player::swapCurrentWeapon()
{
    if (m_currentWeapon == eGun)
    {
        if (m_hasShotgun)
            m_currentWeapon = eShotgun;

        else if (m_hasRifle)
            m_currentWeapon = eRifle;
    }
    else if (m_currentWeapon == eShotgun)
    {
        if (m_hasRifle)
            m_currentWeapon = eRifle;

        else
            m_currentWeapon = eGun;
    }
    else
        m_currentWeapon = eGun;

    cout << "tengo el arma " << m_currentWeapon << endl;
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


    /*********/
     // consumir botiquin
    if(GEInstance->receiver.isKeyDown(KEY_KEY_3) && (World->getTimeElapsed() - m_timeMedkit)> 200)
    {
        this->consumeMedkit();
        m_timeMedkit = World->getTimeElapsed();
    }

    /*********/
    PlayerMate* playermate = NetInstance->getPlayerMate(1);
    if (GEInstance->receiver.isKeyDown(KEY_KEY_4)&& (World->getTimeElapsed() - m_timeGivingStuff) > 200)
    {
         this->giveMedkits(1,playermate);
         m_timeGivingStuff = World->getTimeElapsed();
    }


    if(GEInstance->receiver.isKeyDown(KEY_KEY_5) && World->getTimeElapsed() - m_timeWeaponSwap > 200)
    {
        this->swapCurrentWeapon();
        m_timeWeaponSwap = World->getTimeElapsed();
    }


}


////////////
int Player::getAmmo(int numWeapon) { return m_ammo[numWeapon]; }
void Player::setAmmo(int numWeapon, int ammount) { m_ammo[numWeapon] = ammount; }
void Player::addAmmo(int numWeapon, int ammount) { m_ammo[numWeapon] += ammount; }

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

/////////////
int Player::getNumMedkits()
{
    return m_medkits;
}

/////////////
void Player::setNumMedkits(int ammount)
{
    m_medkits = ammount;

}

/////////////
void Player::addMedkits(int ammount)
{
    m_medkits += ammount;

}

/////////////
void Player::giveMedkits(int ammount, PlayerMate* playermate)
{
    m_medkits -= ammount;

    playermate->addMedkits(ammount);

    //int i = 0;


    //if ((Drawable*)this == NetInstance->getPlayerMate(0))
      //  i = 1;

    cout << "le doy al otro jugador "<< ammount << " botiquines" << endl;
    //Player* p = (Player*)NetInstance->getPlayerMate(1);

    //playermate->receiveMedkits(ammount);

}

/////////////
void Player::receiveMedkits(int ammount)
{
    this->addMedkits(ammount);

}

/////////////
void Player::consumeMedkit()
{

    if (this->getNumMedkits() > 0)
    {
        m_medkits -= 1;
        this->setHealth(100);
        cout << "Vida recuperada: " << this->getLife() << endl;
    }

    cout << m_medkits << endl;
}
