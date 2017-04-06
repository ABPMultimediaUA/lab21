#include "Player.h"
#include "WorldInstance.h"
#include "Firearm.h"

Player::Player(Gun* gun)
{

    setClassID(EntityPhysics::player_id);
    m_mKeys[0]=false;
    m_medkits = 0;
    m_timeMedkit = 2000;
    m_timeGivingStuff = 1000;
    m_timeWeaponSwap = 1000;
    m_hasGun = true;
    m_weapons[0] = gun;
    m_weapons[1] = 0;
    m_weapons[2] = 0;
    m_hasShotgun = false;
    m_hasRifle = false;
    m_currentWeaponType = eGun;
    m_currentWeapon = m_weapons[0];
    m_health = 100;
    m_maxHealth = 100;
    m_grenades=3;

}

Player::~Player()
{
    //dtor
}

/////////////
void Player::update(Shotgun* shotgun, Rifle* rifle)
{
    Drawable::setPosition(dwe::vec3f(getPosEntity().x, getPosition().y, getPosEntity().z));
    if (m_hasShotgun)   {   m_weapons[1] = shotgun; }
    if (m_hasRifle)     {   m_weapons[2] = rifle;   }
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

////////////////////#include <Firearm.h>
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
    m_currentWeapon->shoot();
}


/////////////
FirearmKind Player::getCurrentWeaponType() { return m_currentWeaponType; }
Firearm* Player::getCurrentWeapon() { return m_currentWeapon; }
Firearm** Player::getPlayerWeapons() { return m_weapons; }
Weapon* Player::getPlayerGun() { return m_weapons[0]; }
Weapon* Player::getPlayerShotgun() { return m_weapons[1]; }
Weapon* Player::getPlayerRifle() { return m_weapons[2]; }
bool Player::getHasShotgun() { return m_hasShotgun; }
bool Player::getHasRifle() { return m_hasRifle; }

/////////////
void Player::addWeapon(Consumable* weapon, FirearmKind type)
{
    if (!m_hasShotgun && type == eShotgun){

        m_hasShotgun = true;
        cout << "TENGO SHOTGUN" << endl;
    }

    if (!m_hasRifle && type == eRifle){
        m_hasRifle = true;
        cout << "TENGO RIFLE" << endl;
    }
}

/////////////
void Player::swapCurrentWeapon(int w)
{
    if(w==1){               //GUN
        m_currentWeapon = m_weapons[0];
        m_currentWeaponType = eGun;
        cout<<"pistola"<<endl;
    }else if(w==2){         //SHOTGUN
        if (m_hasShotgun){
            m_currentWeapon = m_weapons[1];
            m_currentWeaponType = eShotgun;
            cout<<"escopeta"<<endl;cout<<&m_currentWeapon<<endl;
        }
    }else if(w==3){         //RIFLE
        cout << m_hasRifle << endl;
        if (m_hasRifle){
            m_currentWeapon = m_weapons[2];
            m_currentWeaponType = eRifle;
            cout<<"rifle"<<endl;
        }
    }
    //cout << "TENGO EL ARMA " << m_currentWeaponType << endl;
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
            setAnimation(dwe::eAnimWalk);
        else
            setAnimation(dwe::eAnimRun);
    }
    else
    {
        setAnimation(dwe::eAnimStand);
    }
    setVelocity(dwe::vec2f(getSpeedX(), getSpeedZ()));


    //Calcular rotacion player - con MOUSE
    if(GEInstance->receiver.getCursorX()>=0 && GEInstance->receiver.getCursorY()>=0){
        setRotation(
            World->from2Dto3D(GEInstance->receiver.getCursorX(),
                              GEInstance->receiver.getCursorY(),
                              getRotation()));
    }


    /*********/
     // consumir botiquin
    if(GEInstance->receiver.isKeyDown(KEY_CONSUME_MEDKIT) && (World->getTimeElapsed() - m_timeMedkit)> 200)
    {
        this->consumeMedkit();

        m_timeMedkit = World->getTimeElapsed();
    }

    /*********/
    PlayerMate* playermate = NetInstance->getPlayerMate(1);
    if (GEInstance->receiver.isKeyDown(KEY_GIVE_AMMO)&& (World->getTimeElapsed() - m_timeGivingStuff) > 200)
    {
         //this->giveMedkits(1,playermate);
         this->giveAmmo(0,1, playermate);
         m_timeGivingStuff = World->getTimeElapsed();
    }


    /*if(GEInstance->receiver.isKeyDown(KEY_KEY_5) && World->getTimeElapsed() - m_timeWeaponSwap > 200){
        this->swapCurrentWeapon(3);
        m_timeWeaponSwap = World->getTimeElapsed();
    }*/

    //CAMBIAR ARMA
    if(GEInstance->receiver.isKeyDown(KEY_WEAPON_1) && World->getTimeElapsed() - m_timeWeaponSwap > 200 && m_currentWeapon != m_weapons[0]){
        this->swapCurrentWeapon(1);
        m_timeWeaponSwap = World->getTimeElapsed();
    }else if(GEInstance->receiver.isKeyDown(KEY_WEAPON_2) && World->getTimeElapsed() - m_timeWeaponSwap > 200 && m_currentWeapon != m_weapons[1]){
        this->swapCurrentWeapon(2);
        m_timeWeaponSwap = World->getTimeElapsed();
    }else if(GEInstance->receiver.isKeyDown(KEY_WEAPON_3) && World->getTimeElapsed() - m_timeWeaponSwap > 200 && m_currentWeapon != m_weapons[2]){
        this->swapCurrentWeapon(3);
        m_timeWeaponSwap = World->getTimeElapsed();
    }

    //HACER DASH
    if(GEInstance->receiver.isKeyDown(KEY_DASH) && World->getTimeElapsed() > 7000) // Corregir CD Dash
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
void Player::setMKeys(int id){  m_mKeys[id]=true; }
bool Player::getMKey(int n){ return m_mKeys[n]; }

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
void Player::onBeginContact(EntityPhysics* otherObject)
{
    if((otherObject && otherObject->getClassID()==EntityPhysics::enemy_id)){
        m_health-=5;
        cout<< "Perdiendo vida: " << m_health <<endl;
    }
}
