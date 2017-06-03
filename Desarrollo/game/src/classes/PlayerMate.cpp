#include "PlayerMate.h"
#include "TriggerSound.h"
#include "Scene.h"
#include "AudioEngine.h"

PlayerMate::PlayerMate()
{
    setClassID(EntityPhysics::playermate_id);

    m_currentWeaponKind = (FirearmKind)0;
    m_weapons[0] = 0;
    m_weapons[1] = 0;
    m_weapons[2] = 0;

    setSoundTrigger();

    // Parametros de físicas por defecto
}

PlayerMate::~PlayerMate()
{
    //dtor
}

/////////////////
void PlayerMate::update()
{
    Drawable::setPosition(dwe::vec3f(getPosEntity().x, getPosition().y, getPosEntity().z));
    m_soundTrigger->setPosEntity(getPosEntity(), 0.0);
}

void PlayerMate::render()
{

}

/////////////
void PlayerMate::setNode(dwe::Node* n)
{
    Drawable::setNode(n);

    dwe::vec3f box = n->getBoundingBox();
    createDynamicBody(getPosition(), box.x, box.z);
}

///////////////////////
dwe::vec3f PlayerMate::getShift() { return m_shift; }
void PlayerMate::setShift(dwe::vec3f s) { m_shift = s;}
unsigned short int PlayerMate::getHealth() { return m_health; }
void PlayerMate::setHealth(unsigned short int h) { m_health = h;}
unsigned short int PlayerMate::getNumGrenades() { return m_numGrenades; }
void PlayerMate::setNumGrenades(unsigned short int n) { m_numGrenades = n;}
unsigned short int PlayerMate::getNumMedkits() { return m_numMedkits; }
void PlayerMate::setNumMedkits( unsigned short int n) { m_numMedkits = n;}
void PlayerMate::addMedkits( unsigned short int n) { m_numMedkits += n;}

void PlayerMate::giveMedkits(int ammount)
{
    Player* player = (Player*)NetInstance->getPlayerMate(0);
     player->receiveMedkits(ammount);
}

void PlayerMate::giveAmmo(int numWeapon, int ammount)
{
    Player* player = (Player*)NetInstance->getPlayerMate(0);
    player->receiveAmmo(numWeapon, ammount);
}

/////////////////
void PlayerMate::setWeapon(uint8_t index, Firearm* firearm)
{
    if (index < PlayerMate::_maxWeapons)
    {
        m_weapons[index] = firearm;
    }
    else
        std::cerr << "(PlayerMate::setWeapon) Parametro index fuera de rango\n";
}

/////////////////
void PlayerMate::swapCurrentWeapon(FirearmKind firearmKind)
{
    if (firearmKind == eGun || firearmKind == eShotgun || firearmKind == eRifle)
    {
        m_weapons[m_currentWeaponKind]->setPut();
        m_weapons[firearmKind]->setDraw();
        m_currentWeaponKind = firearmKind;
    }
}

/////////////////
void PlayerMate::setSoundTrigger()
{
    m_soundTrigger = new TriggerSound(dwe::vec3f(170,0,60), 2/0.035, true);
    Scene::Instance()->getTriggerSystem().Add(m_soundTrigger);
}

void PlayerMate::setAnimation(dwe::AnimationType a)
{
    if (a == dwe::eAnimPlayerGrenade)
        AEInstance->Play2D(dwe::AudioEngine::_soundAnillaGranada);
    Drawable::setAnimation(a);
}
