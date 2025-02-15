#include "Player.h"
#include "WorldInstance.h"
#include "Firearm.h"
#include "TriggerSound.h"
#include "Scene.h"
#include "AudioEngine.h"
#include "TriggerDamage.h"

Player::Player() :
    m_currentWeaponType(eNone), m_currentWeapon(0)
{
    setClassID(EntityPhysics::player_id);
    m_mKeys[0]=false;
    m_mKeys[1]=false;
    m_mKeys[2]=false;
    m_mKeys[3]=false;
    m_medkits = 0;
    m_speedBoosts = 0;

    // En segundos
    m_lastTimeTakeDamage= 0.5;
    m_timeMedkit        = 2.0;
    m_timeToSpeedBoost  = 2.0;
    m_timeGivingStuff   = 1.0;
    m_timeWeaponSwap    = 1.0;
    m_timeReload        = 1.0;
    m_timeLastGrenade   = 0;
    m_timeInitGrenade   = 0;
    m_isThrowingGrenade = false;
    m_grenadeSound      = false;
    m_timeLastProjectil = 0;

    m_weapons[eGun]     = 0;
    m_weapons[eShotgun] = 0;
    m_weapons[eRifle]   = 0;

    m_health    = 100;
    m_maxHealth = 100;
    m_grenades  = 1;

    m_playerWeaponKey[eGun].key         = KEY_WEAPON_1;
    m_playerWeaponKey[eGun].weapon      = eGun;
    m_playerWeaponKey[eShotgun].key     = KEY_WEAPON_2;
    m_playerWeaponKey[eShotgun].weapon  = eShotgun;
    m_playerWeaponKey[eRifle].key       = KEY_WEAPON_3;
    m_playerWeaponKey[eRifle].weapon    = eRifle;

    setSoundTrigger();

    // Par�metros de f�sicas por defecto
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
    readEvents(); // Read keyboard and mouse inputs for de player

    // Actualizamos la posici�n del box2d en el modelo
    Drawable::setPosition(dwe::vec3f(getPosEntity().x, getPosition().y, getPosEntity().z));
    m_soundTrigger->setPosEntity(getPosEntity(), 0.0);
}

/////////////
void Player::setNode(dwe::Node* n)
{
    Drawable::setNode(n);

    dwe::vec3f box = n->getBoundingBox();
    createDynamicBody(getPosition(), box.x, box.z);
}

void Player::setSoundTrigger()
{
    m_soundTrigger = new TriggerSound(dwe::vec3f(170,0,60), 2/0.035, true);
    Scene::Instance()->getTriggerSystem().Add(m_soundTrigger);
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
void Player::throwGrenade()
{
    m_grenadeWeapon.shoot();
    m_grenades--;
}

/////////////
bool Player::canThrowGrenade(float timeSinceLastGrenade)
{
    return (timeSinceLastGrenade > m_grenadeWeapon.getCadence() && m_grenades > 0);
}

/////////////
FirearmKind Player::getCurrentWeaponType() { return m_currentWeaponType; }
Firearm* Player::getCurrentWeapon() { return m_currentWeapon; }
Firearm** Player::getPlayerWeapons() { return m_weapons; }

Weapon* Player::getPlayerGun()      { return m_weapons[eGun]; }
Weapon* Player::getPlayerShotgun()  { return m_weapons[eShotgun]; }
Weapon* Player::getPlayerRifle()    { return m_weapons[eRifle]; }

//////////////////
bool Player::reloadWeapon()
{
    return m_currentWeapon->reload();
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
        if(type!=eGun)
            m_weapons[type]->setPut();
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
        // Pongo el arma anterior en su posici�n de guardado
        if (m_currentWeapon)
            m_currentWeapon->setPut();

        m_currentWeapon = m_weapons[weaponKind];

        // Pongo el arma nueva en su posici�n de ataque
        if (m_currentWeapon)
            m_currentWeapon->setDraw();

        m_currentWeaponType = weaponKind;
        m_timeWeaponSwap    = World->getTimeElapsed();

        NetInstance->sendBroadcast(ID_SWAP_WEAPON, NetInstance->getGUID(), m_currentWeaponType);
    }
}

/////////////
void Player::readEvents()
{
    CharacterController::readEvents();
    setVelocity(dwe::vec2f(getSpeedX(), getSpeedZ()));

    if (getIsEvading())
        return;

    if (m_localIsEvading)
    {
        m_currentWeapon->setDraw();
        m_localIsEvading = false;
    }

    float timeElapsed = World->getTimeElapsed();

    if (m_isThrowingGrenade)
    {
        if(!m_grenadeSound){
            AEInstance->Play2D("media/Sounds/AnillaGranada.wav");
            m_grenadeSound = true;
        }

        if (timeElapsed - m_timeInitGrenade > Player::_throwGrenadeOffsetTime)
        {
            throwGrenade();
            NetInstance->sendBroadcast(ID_PROJECTILEGRENADE_CREATE, getPosition(), getRotation().y); // Enviamos mensaje para crear projectilgrenade
            m_timeLastGrenade = timeElapsed;
            m_isThrowingGrenade = false;
            m_grenadeSound = false;
        }
        else{
            return;
        }
    }

    else{
        m_currentWeapon->setDraw();
    }


    //Animacion del player
    if(getSpeedX()!=0 || getSpeedZ()!=0)
    {
        if(GEInstance->receiver.isKeyDown(KEY_WALK))
            setAnimation(dwe::eAnimPlayerStealth);
        else if(getAnimation()!=dwe::eAnimPlayerDash)
            setAnimation(dwe::eAnimPlayerRun);
    }
    else if(getAnimation()!=dwe::eAnimPlayerGrenade && getAnimation()!=dwe::eAnimPlayerDash && getAnimation()!=dwe::eAnimPlayerAttack)
    {
        setAnimation(dwe::eAnimPlayerStand);
    }



    //Calcular rotacion player - con MOUSE
    if(GEInstance->receiver.getCursorX()>=0 && GEInstance->receiver.getCursorY()>=0)
    {
        setRotation(dwe::vec3f(0,
                               GEInstance->getTagEngine()->angleToScreenCoords(
                                            getPosition(),
                                            dwe::vec3f(GEInstance->receiver.getCursorX(), GEInstance->receiver.getCursorY(), 0))
                               , 0));
    }

    // comprobamos si dispara
    if (GEInstance->receiver.isLeftButtonPressed()
        && (timeElapsed - m_timeReload)> _reloadOffsetTime   // Si ha recargado, dejar pasar un tiempo
        && shoot(timeElapsed - m_timeLastProjectil))
    {
        m_timeLastProjectil = timeElapsed;
    }
    else
        // comprobamos si dispara granadas
        if(GEInstance->receiver.isKeyDown(KEY_GRENADE) && canThrowGrenade(timeElapsed - m_timeLastGrenade))
        {
            m_isThrowingGrenade = true;
            m_timeInitGrenade = timeElapsed;
            setAnimation(dwe::eAnimPlayerGrenade);
            m_currentWeapon->setPut();
            return;
        }


    if(GEInstance->receiver.isKeyDown(KEY_ATTACK))
    {
        setAnimation(dwe::eAnimPlayerAttack);
    }


     // consumir botiquin
    if(GEInstance->receiver.isKeyDown(KEY_CONSUME_MEDKIT) && (timeElapsed - m_timeMedkit)> _changeOffsetTime)
    {
        consumeMedkit();

        m_timeMedkit = timeElapsed;
    }

     // consumir adrenalina
    if(GEInstance->receiver.isKeyDown(KEY_CONSUME_SPEED) && (timeElapsed - m_timeToSpeedBoost)> _changeOffsetTime)
    {
        consumeSpeedBoost();

        m_timeToSpeedBoost = timeElapsed;
    }

    // recargar armo
    if(GEInstance->receiver.isKeyDown(KEY_RELOADWEAPON) && (timeElapsed - m_timeReload)> _reloadOffsetTime)
    {
        if(reloadWeapon())
            m_timeReload = timeElapsed;
    }

    if (GEInstance->receiver.isKeyDown(KEY_GIVE_AMMO)&& (timeElapsed - m_timeGivingStuff) > _changeOffsetTime)
    {
        PlayerMate* playermate = NetInstance->getPlayerMate(1);
         giveAmmo(0,1, playermate);
         m_timeGivingStuff = timeElapsed;
    }


    //CAMBIAR ARMA
    for(uint8_t i=0; i<eNumWeapons; i++)
        if (GEInstance->receiver.isKeyDown(m_playerWeaponKey[i].key))
            swapCurrentWeapon(m_playerWeaponKey[i].weapon);

    //HACER DASH
    if(GEInstance->receiver.isKeyDown(KEY_DASH))
    {
        m_localIsEvading = true;
        dash();//evadimos
        if(getIsEvading())
            m_currentWeapon->setPut(); // Guardamos arma
    }



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
int Player::getSpeedBoosts() { return m_speedBoosts; }

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
}

/////////////
void Player::giveMedkits(int ammount, PlayerMate* playermate){
    NetInstance->sendBroadcast(ID_SEND_MEDKIT, playermate->creatingSystemGUID.ToString());
    m_medkits -= ammount;
}

/////////////
void Player::receiveMedkits(int ammount)    {   m_medkits+=ammount;  }

/////////////
void Player::consumeMedkit()
{
    if (m_health<100 && m_medkits>0){
        m_medkits -= 1;
        m_health=100;
    }
}

/////////////
void Player::consumeSpeedBoost()
{
    if (m_speedBoosts > 0){
        m_speedBoosts -= 1;
        setSpeedBoost();
    }
}

void Player::takeDamage(int damage)
{
    float timeElapsed = World->getTimeElapsed();
    if(timeElapsed - m_lastTimeTakeDamage > _takeDamageOffsetTime)
    {
        m_health -= damage;
        m_lastTimeTakeDamage = timeElapsed;
    }
}

/////////////
void Player::onBeginContact(EntityPhysics* otherObject)
{
    if((otherObject && otherObject->getClassID()==EntityPhysics::triggerDamage_id)){
        TriggerDamage* t = static_cast<TriggerDamage*>(otherObject);
        takeDamage(t->getDamage());
    }
}
