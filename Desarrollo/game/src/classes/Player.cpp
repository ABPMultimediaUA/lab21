#include "Player.h"
#include "WorldInstance.h"
#include "Firearm.h"

Player::Player() :
    m_currentWeaponType(eNone), m_currentWeapon(0)
{

    setClassID(EntityPhysics::player_id);
    m_mKeys[0]=false;
    m_mKeys[1]=false;
    m_mKeys[2]=false;
    m_medkits = 0;

    // En segundos
    m_timeMedkit        = 2.0;
    m_timeToSpeedBoost  = 2.0;
    m_timeGivingStuff   = 1.0;
    m_timeWeaponSwap    = 1.0;
    m_timeReload        = 1.0;

    m_weapons[eGun]     = 0;
    m_weapons[eShotgun] = 0;
    m_weapons[eRifle]   = 0;

    m_health = 100;
    m_maxHealth = 100;
    m_grenades=3;

    m_playerWeaponKey[eGun].key         = KEY_WEAPON_1;
    m_playerWeaponKey[eGun].weapon      = eGun;
    m_playerWeaponKey[eShotgun].key     = KEY_WEAPON_2;
    m_playerWeaponKey[eShotgun].weapon  = eShotgun;
    m_playerWeaponKey[eRifle].key       = KEY_WEAPON_3;
    m_playerWeaponKey[eRifle].weapon    = eRifle;
}

Player::~Player()
{
    deleteWeapons();
}

void Player::deleteWeapons()
{
    for(uint8_t i=0; i<eNumWeapons; i++)
    {
        if (m_weapons[i])
        {
            delete m_weapons[i];
            m_weapons[i] = 0;
        }
    }
}

/////////////
void Player::update()
{
    // Actualizamos la posición del box2d en el modelo
    Drawable::setPosition(dwe::vec3f(getPosEntity().x, getPosition().y, getPosEntity().z));
}

/////////////
void Player::setNode(dwe::Node* n)
{
    Drawable::setNode(n);

    dwe::vec3f box = n->getBoundingBox();
    createDynamicBody(getPosition(), box.x, box.z);
}

/////////////
void Player::setPosition(dwe::vec3f p)
{
    setPosEntity(p, getRotation().y);
    Drawable::setPosition(p);
}

/***/
void Player::sayPosition()
{
    cout<<"X: "<<getPosition().x<<" Z: "<<getPosition().z<<endl;
}
/***/

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
bool Player::shoot(float timeSinceLastShoot)
{
    if (timeSinceLastShoot > m_currentWeapon->getCadence() && m_currentWeapon->getAmmo() > 0)
    {
        m_currentWeapon->shoot();
        m_currentWeapon->addAmmo(-1);
        return true;
    }
    return false;
}


/////////////
FirearmKind Player::getCurrentWeaponType() { return m_currentWeaponType; }
Firearm* Player::getCurrentWeapon() { return m_currentWeapon; }
Firearm** Player::getPlayerWeapons() { return m_weapons; }

Weapon* Player::getPlayerGun()      { return m_weapons[eGun]; }
Weapon* Player::getPlayerShotgun()  { return m_weapons[eShotgun]; }
Weapon* Player::getPlayerRifle()    { return m_weapons[eRifle]; }

//////////////////
void Player::reloadWeapon()
{
    m_currentWeapon->reload();
}

/////////////
void Player::addWeapon(FirearmKind type)
{
    if (!m_weapons[type])
    {
        switch(type)
        {
        case eGun:      m_weapons[eGun]     = GEInstance->createGun(this);       break;
        case eShotgun:  m_weapons[eShotgun] = GEInstance->createShotgun(this);   break;
        case eRifle:    m_weapons[eRifle]   = GEInstance->createRifle(this);     break;
        default:  break;
        }
        swapCurrentWeapon(type);
    }
}

/////////////
void Player::swapCurrentWeapon(FirearmKind weaponKind)
{
    if( weaponKind!=m_currentWeaponType && weaponKind!=eNone && weaponKind<eNumWeapons
       && !(weaponKind==eShotgun && !m_weapons[eShotgun])
       && !(weaponKind==eRifle   && !m_weapons[eRifle])
       && (World->getTimeElapsed() - m_timeWeaponSwap > _changeOffsetTime) )
    {
        // Pongo el arma anterior en su posición de guardado
        if (m_currentWeapon)
            m_currentWeapon->setPut();

        m_currentWeapon = m_weapons[weaponKind];

        // Pongo el arma nueva en su posición de ataque
        if (m_currentWeapon)
            m_currentWeapon->setDraw();

        m_currentWeaponType = weaponKind;
        m_timeWeaponSwap    = World->getTimeElapsed();
    }
}

/////////////
void Player::throwGrenade()
{
    m_grenadeWeapon.shoot();
}

/////////////
void Player::readEvents()
{
    CharacterController::readEvents();

    //Animacion del player
    if(getSpeedX()!=0 || getSpeedZ()!=0)
    {
        if(GEInstance->receiver.isKeyDown(KEY_WALK))
            setAnimation(dwe::eAnimPlayerStealth);
        else
            setAnimation(dwe::eAnimPlayerRun);
    }
    else
    {
        setAnimation(dwe::eAnimPlayerStand);
    }
    setVelocity(dwe::vec2f(getSpeedX(), getSpeedZ()));


    //Calcular rotacion player - con MOUSE
    if(GEInstance->receiver.getCursorX()>=0 && GEInstance->receiver.getCursorY()>=0)
    {
        //GEInstance->rotateNodeToCursor(getNode());
        setRotation(
            World->from2Dto3D(GEInstance->receiver.getCursorX(),
                              GEInstance->receiver.getCursorY(),
                              getRotation()));
    }


    /*********/
     // consumir botiquin
    if(GEInstance->receiver.isKeyDown(KEY_CONSUME_MEDKIT) && (World->getTimeElapsed() - m_timeMedkit)> _changeOffsetTime)
    {
        this->consumeMedkit();

        m_timeMedkit = World->getTimeElapsed();
    }

     // consumir adrenalina
    if(GEInstance->receiver.isKeyDown(KEY_CONSUME_SPEED) && (World->getTimeElapsed() - m_timeToSpeedBoost)> _changeOffsetTime)
    {
        this->consumeSpeedBoost();

        m_timeToSpeedBoost = World->getTimeElapsed();
    }

    // recargar armo
    if(GEInstance->receiver.isKeyDown(KEY_RELOADWEAPON) && (World->getTimeElapsed() - m_timeReload)> _changeOffsetTime)
    {
        reloadWeapon();
        m_timeReload = World->getTimeElapsed();
    }
    /*********/
    PlayerMate* playermate = NetInstance->getPlayerMate(1);
    if (GEInstance->receiver.isKeyDown(KEY_GIVE_AMMO)&& (World->getTimeElapsed() - m_timeGivingStuff) > _changeOffsetTime)
    {
         //this->giveMedkits(1,playermate);
         this->giveAmmo(0,1, playermate);
         m_timeGivingStuff = World->getTimeElapsed();
    }


    //CAMBIAR ARMA
    for(uint8_t i=0; i<eNumWeapons; i++)
        if (GEInstance->receiver.isKeyDown(m_playerWeaponKey[i].key))
            swapCurrentWeapon(m_playerWeaponKey[i].weapon);

    //HACER DASH
    if(GEInstance->receiver.isKeyDown(KEY_DASH))
        this->dash();//evadimos
}


/////////////
void Player::giveAmmo(int numWeapon, int ammount, PlayerMate* playermate)
{
    NetInstance->sendBroadcast(ID_SEND_AMMO, playermate->creatingSystemGUID.ToString());

    static_cast<Weapon*>(m_weapons[numWeapon])->setAmmo(ammount - 1);

}

/////////////
void Player::receiveAmmo(int numWeapon, int ammount)
{
    static_cast<Weapon*>(m_weapons[numWeapon])->addAmmo(ammount);
}

////////////
int Player::getGrenades() { return m_grenades; }
void Player::setGrenades(int n) { m_grenades = n; }
void Player::setMKeys(int id){  m_mKeys[id]=true; cout<<"Tengo llave del generador "<<id<<endl;}
bool Player::getMKey(int n){ return m_mKeys[n]; }

////////////
void Player::addSpeedBoost() { m_speedBoosts += 1;}

////////////
int Player::getHealth() { return m_health; }
void Player::setHealth(int n) { m_health = n; }
int Player::getMaxHealth() { return m_maxHealth; }

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
void Player::addMedkits(int ammount){
    m_medkits += ammount;
    cout << "\nPlayer.cpp------------Obtengo " << ammount << " medkits---------\n";
}

/////////////
void Player::giveMedkits(int ammount, PlayerMate* playermate){
    NetInstance->sendBroadcast(ID_SEND_MEDKIT, playermate->creatingSystemGUID.ToString());
    m_medkits -= ammount;
    cout << "\nPlayer.cpp------------le doy al otro jugador "<< ammount << " botiquines--------------\n";
}

/////////////
void Player::receiveMedkits(int ammount)    {   this->addMedkits(ammount);  }

/////////////
void Player::consumeMedkit()
{
    if (this->getNumMedkits() > 0){
        m_medkits -= 1;
        this->setHealth(100);
        cout << "Vida recuperada: " << this->getHealth() << endl;
    }

    cout << m_medkits << endl;
}

/////////////
void Player::consumeSpeedBoost()
{
    if (m_speedBoosts > 0){
        m_speedBoosts -= 1;
        setSpeedBoost();
    }
}

/////////////
void Player::onBeginContact(EntityPhysics* otherObject)
{
    if((otherObject && otherObject->getClassID()==EntityPhysics::enemy_id)){
        m_health-=5;
    }
}
