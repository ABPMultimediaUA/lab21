#define GLEW_STATIC
#include<GL/glew.h>
#include <glm/glm.hpp>

#include "GraphicsEngine.h"
#include "Player.h"
#include "PlayerMate.h"
#include "Humanoid.h"
#include "Dog.h"
#include "Bat.h"
#include "Guardian.h"
#include "Legless.h"
#include "Mother.h"

#include "NetGame.h"

#include "WorldInstance.h"

#include "Door.h"
#include "DoorRotate.h"
#include "Projectile.h"
#include "ProjectileGrenade.h"
#include "Generator.h"
#include "MagnetKey.h"
#include "SpeedBoost.h"
#include "Medkit.h"
#include "Floor.h"

#include "TriggerDoor.h"
#include "TriggerGenerator.h"

#include "ScenaryElement.h"

#include <fstream> //Lectura de ficheros
#include <iostream>
#include <cmath>

#include "CShotgun.h"
#include "CRifle.h"
#include "Gun.h"
#include "Shotgun.h"
#include "Rifle.h"
#include "Ammo.h"
#include "GrenadeExplosion.h"
#include "tag/EAnimation.h"
#include "LoadingScreen.h"
#include "ClippingObject.h"

// OJO estas opciones se reescriben en leerFicheroOpciones() si existe
// Estan para valores por defecto
// Si en fullscreen no se ve bien maximizado es que la pantalla
// no soporta esa resoluci�n. Configurar en fich de opciones
#ifndef LAB21_DEBUG
int  dwe::GraphicsEngine::_screenWidth  = 1366;
int  dwe::GraphicsEngine::_screenHeight = 768;
bool dwe::GraphicsEngine::_fullScreen   = true;
bool dwe::GraphicsEngine::_shadows      = true;
bool dwe::GraphicsEngine::_vsync        = true;
#else
int  dwe::GraphicsEngine::_screenWidth  = 1024;
int  dwe::GraphicsEngine::_screenHeight = 768;
bool dwe::GraphicsEngine::_fullScreen   = false;
bool dwe::GraphicsEngine::_shadows      = true;
bool dwe::GraphicsEngine::_vsync        = false;
#endif


using namespace std;


///////////////////////////////////////////////
// class GraphicsEngine
///////////////////////////////////////////////
dwe::GraphicsEngine* dwe::GraphicsEngine::Instance()
{
    static GraphicsEngine instance;
    return &instance;
}

//////////////////////////
void dwe::GraphicsEngine::init()
{
    // Importante para que muestre bien el cubo y no haga un mal culling
    sf::ContextSettings contextSettings;
    contextSettings.depthBits = 24;
    contextSettings.sRgbCapable = false;

    leerFicheroOpciones();


    sf::Uint32 style;
    if (GraphicsEngine::_fullScreen)
        style = sf::Style::Fullscreen;
    else
        style = sf::Style::Default;

    m_window = new sf::RenderWindow(sf::VideoMode(GraphicsEngine::_screenWidth, GraphicsEngine::_screenHeight), "Lab21", style, contextSettings);
    m_window->setVerticalSyncEnabled(GraphicsEngine::_vsync);

    // Creamos los mensajes de texto, por ahora vacios
    if (!m_font.loadFromFile("media/ExoRegular.otf"))
        throw std::runtime_error("No se ha podido cargar la fuente de texto");

	for(int i=0; i<MAX_MESSAGE_LINES; i++)
	{
        m_messageLine[i].setFont(m_font);
        m_messageLine[i].setCharacterSize(14);
        m_messageLine[i].setFillColor(sf::Color(25, 227, 223, 255));
        m_messageLine[i].setPosition(250.f, GraphicsEngine::_screenHeight - (i+1)*16.f);
        m_messageLine[i].setString("");
	}

	// Cargamos sprite del cursor
	m_cursorTexture.loadFromFile("media/cursor.png");
	m_cursorSprite.setTexture(m_cursorTexture);
	m_cursorSprite.setOrigin(m_cursorTexture.getSize().x/2.0, m_cursorTexture.getSize().y/2.0);

    m_tagEngine.init(GraphicsEngine::_screenHeight, GraphicsEngine::_screenWidth, GraphicsEngine::_shadows);

    m_secondsLastDraw = 0;
    m_drawsCount = 0;
    m_timeIniDraw = 0;
    m_timeAccumDraw = 0;

    m_clock.restart();

    m_camera = 0;

    m_window->pushGLStates();
}
//////////////////////////
void dwe::GraphicsEngine::push()
{
    m_window->pushGLStates();
}
//////////////////////////
void dwe::GraphicsEngine::pop()
{
    m_window->popGLStates();
}

//////////////////////////
void dwe::GraphicsEngine::release()
{
}

//////////////////////////
bool dwe::GraphicsEngine::isRunning()
{
    m_timeIniDraw = m_clock.getElapsedTime().asSeconds();

    sf::Event event;
    while (m_window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            m_window->close();
        }
        else if (event.type == sf::Event::Resized)
        {
            glViewport(0, 0, event.size.width, event.size.height);
        }
        else
            receiver.OnEvent(event);
    }

    return m_window->isOpen() && m_tagEngine.isRunning();
}

bool dwe::GraphicsEngine::getWindowClose()
{
     return !m_window->isOpen();
}

//////////////////////////
void dwe::GraphicsEngine::draw()
{
    m_window->popGLStates();   // Antes de este pop hay un push, en init
    m_tagEngine.draw();
    m_window->pushGLStates();

    // Dibujamos cursor
    if (m_ownCursor)
    {
        m_cursorSprite.setPosition(static_cast<sf::Vector2f>(sf::Mouse::getPosition(*m_window)));
        m_window->draw(m_cursorSprite);
    }

    // Lineas de mensaje del jugador
    for(unsigned int i=0; i<MAX_MESSAGE_LINES; i++)
        m_window->draw(m_messageLine[i]);
}

void dwe::GraphicsEngine::drawRectangleShape(sf::RectangleShape rs)
{
    m_window->draw(rs);
}

void dwe::GraphicsEngine::drawText(sf::Text t)
{
    m_window->draw(t);
}

void dwe::GraphicsEngine::drawSprite(sf::Sprite sp)
{
    m_window->draw(sp);
}

void dwe::GraphicsEngine::drawAnimatedSprite(AnimatedSprite as)
{
    m_window->draw(as);
}

void dwe::GraphicsEngine::clearWindow()
{
    m_window->clear();
}

void dwe::GraphicsEngine::displayWindow()
{
    m_window->display();

    m_drawsCount++;
    m_timeAccumDraw += m_clock.getElapsedTime().asSeconds() - m_timeIniDraw;

    float timeElapsed = m_clock.getElapsedTime().asSeconds() - m_secondsLastDraw;

    // Dibujamos fps y tiempo de dibujo cada segundo
    if ( timeElapsed > 1.0 )
    {
        m_secondsLastDraw = m_clock.getElapsedTime().asSeconds();
        float fps = m_drawsCount / timeElapsed;
        float fpsDibujado = 1.0 / (m_timeAccumDraw / m_drawsCount);  // Los fps que podr�a tener

        char tmp[40];
        sprintf(tmp, "Lab21 - fps:%f    draw:%f", fps, fpsDibujado);
        m_window->setTitle(tmp);

        m_drawsCount=0;
        m_timeAccumDraw=0;
    }
}


//////////////////////////
void dwe::GraphicsEngine::render()
{

}

/////////////////////////////////////
ClippingObject* dwe::GraphicsEngine::createClippingObject(ClippingObject* parent)
{
    tag::GraphicNode* p = parent ? parent->getNode()->getNode() : 0;
    tag::GraphicNode* gn = m_tagEngine.createEmptyNode(p);
    ClippingObject *co= new ClippingObject();
    co->setNode(new Node(gn));
    return co;
}


/////////////////////////////////////
ScenaryElement* dwe::GraphicsEngine::createScenaryElement(std::string m, std::string t, Drawable* parent)
{
    tag::GraphicNode* p = parent ? parent->getNode()->getNode() : 0;
    tag::GraphicNode* gn = m_tagEngine.createMesh("media/"+m+".obj", vec3f(0,0,0), vec3f(0,0,0), "media/"+t+".bmp", p);
    ScenaryElement *se= new ScenaryElement();
    se->setNode(new Node(gn));
    if(m=="environment_elements/mesahall" || m=="environment_elements/mesahallobjetos")
    {
        se->destroyBody();
        se->SetCircle();
    }

    return se;
}

////////////////////////////////
Floor* dwe::GraphicsEngine::createFloor(std::string m, std::string t, Drawable* parent)
{
    tag::GraphicNode* p = parent ? parent->getNode()->getNode() : 0;
    tag::GraphicNode* gn = m_tagEngine.createMesh("media/"+m+".obj", vec3f(0,0,0), vec3f(0,0,0), "media/"+t+".bmp", p);
    Floor *f = new Floor();
    f->setNode(new Node(gn));
    return f;
}


/////////////////////////////
Player* dwe::GraphicsEngine::createMainPlayer()
{
    tag::EAnimation* anim = m_tagEngine.createNumAnimations(7, "media/player/player.bmp");
    m_tagEngine.createAnimation(anim, "media/player/playerStand/playerStand",       eAnimPlayerStand,   1);
    m_tagEngine.createAnimation(anim, "media/player/playerRun/playerRun",           eAnimPlayerRun,     20); LoadingScreen::getInstance()->AddProgress();
    m_tagEngine.createAnimation(anim, "media/player/playerWalk/playerWalk",         eAnimPlayerStealth, 10); LoadingScreen::getInstance()->AddProgress();
    m_tagEngine.createAnimation(anim, "media/player/playerGrenade/playerGrenade",   eAnimPlayerGrenade, 20, false); LoadingScreen::getInstance()->AddProgress();
    m_tagEngine.createAnimation(anim, "media/player/playerAttack/playerAttack",     eAnimPlayerAttack,  15, false); LoadingScreen::getInstance()->AddProgress();
    m_tagEngine.createAnimation(anim, "media/player/playerDash/playerDash",         eAnimPlayerDash,    19, false); LoadingScreen::getInstance()->AddProgress();
    m_tagEngine.createAnimation(anim, "media/player/playerDeath/playerDeath",       eAnimPlayerDeath,   14, false); LoadingScreen::getInstance()->AddProgress();
    anim->setActiveAnimation(0);

    tag::GraphicNode* node = m_tagEngine.createNodeAnimations(anim, vec3f(0,0,0), vec3f(0,0,0));
	Player* p = new Player();
	p->setNode(new Node(node));

	NetInstance->addNetObject(p);
	return p;
}



/////////////////////////////////
PlayerMate* dwe::GraphicsEngine::createPlayerMate()
{
    tag::EAnimation* anim = m_tagEngine.createNumAnimations(7, "media/player/playerMate.bmp");
    m_tagEngine.createAnimation(anim, "media/player/playerStand/playerStand",       eAnimPlayerStand,   1);
    m_tagEngine.createAnimation(anim, "media/player/playerRun/playerRun",           eAnimPlayerRun,     20);
    m_tagEngine.createAnimation(anim, "media/player/playerWalk/playerWalk",         eAnimPlayerStealth, 10);
    m_tagEngine.createAnimation(anim, "media/player/playerGrenade/playerGrenade",   eAnimPlayerGrenade, 19, false);
    m_tagEngine.createAnimation(anim, "media/player/playerAttack/playerAttack",     eAnimPlayerAttack,  14, false);
    m_tagEngine.createAnimation(anim, "media/player/playerDash/playerDash",         eAnimPlayerDash,    19, false);
    m_tagEngine.createAnimation(anim, "media/player/playerDeath/playerDeath",       eAnimPlayerDeath,   14, false);
    anim->setActiveAnimation(0);

    tag::GraphicNode* node = m_tagEngine.createNodeAnimations(anim, vec3f(0,0,0), vec3f(0,0,0));
	PlayerMate* p = new PlayerMate();
	p->setNode(new Node(node));

	NetInstance->addNetObject(p);

	return p;
}

////////////////////////////
Humanoid* dwe::GraphicsEngine::createEnemyHumanoid(int px, int py, int pz)
{
    tag::EAnimation* anim = m_tagEngine.createNumAnimations(4, "media/Humanoid/humanoide.bmp");
    m_tagEngine.createAnimation(anim, "media/Humanoid/Stand/humanoide",                 eAnimEnemyStand,   1);
    m_tagEngine.createAnimation(anim, "media/Humanoid/Death/humanoideDeath",            eAnimEnemyDeath,   11, false);
    m_tagEngine.createAnimation(anim, "media/Humanoid/MeleeAttack/humanoidMeleeAttack", eAnimEnemyAttack,   14);
    m_tagEngine.createAnimation(anim, "media/Humanoid/Walk/humanoidWalk",               eAnimEnemyWalk,   14);

    anim->setActiveAnimation(0);

    tag::GraphicNode* node = m_tagEngine.createNodeAnimations(anim, vec3f(0,0,0), vec3f(0,0,0));
    Humanoid* p = new Humanoid();
	p->setNode(new Node(node));
	p->setPosition(dwe::vec3f(px, py, pz));
	p->SetVision();

	NetInstance->addNetEnemy(p);
	return p;
}

////////////////////////////
Mother* dwe::GraphicsEngine::createEnemyMother(int px, int py, int pz)
{
	tag::EAnimation* anim = m_tagEngine.createNumAnimations(1, "media/Mother/madre.bmp");
    m_tagEngine.createAnimation(anim, "media/Mother/Stand/motherStand", eAnimEnemyStand,   15);

    anim->setActiveAnimation(0);

    tag::GraphicNode* node = m_tagEngine.createNodeAnimations(anim, vec3f(0,0,0), vec3f(0,0,0));
    Mother* p = new Mother();
	p->setNode(new Node(node));
	p->setPosition(dwe::vec3f(px, py, pz));
	p->SetVision();

	NetInstance->addNetEnemy(p);
	return p;
}

////////////////////////////
Dog* dwe::GraphicsEngine::createEnemyDog(int px, int py, int pz)
{
    tag::EAnimation* anim = m_tagEngine.createNumAnimations(4, "media/Dog/dog.bmp");
    m_tagEngine.createAnimation(anim, "media/Dog/Stand/dogStand",   eAnimEnemyStand,   1);
    m_tagEngine.createAnimation(anim, "media/Dog/Death/dogDeath",   eAnimEnemyDeath,   9, false);
    m_tagEngine.createAnimation(anim, "media/Dog/Walk/dogWalk",     eAnimEnemyWalk,   11);
    m_tagEngine.createAnimation(anim, "media/Dog/Attack/dogAttack", eAnimEnemyAttack,  5);
    //m_tagEngine.createAnimation(anim, "media/Dog/Run/dogRun",       eAnimEnemyRun, 11);
    anim->setActiveAnimation(0);

    tag::GraphicNode* node = m_tagEngine.createNodeAnimations(anim, vec3f(0,0,0), vec3f(0,0,0));

    Dog* p = new Dog();
	p->setNode(new Node(node));
    p->setPosition(dwe::vec3f(px, py, pz));
    p->SetVision();

	NetInstance->addNetEnemy(p);
	return p;
}

Bat* dwe::GraphicsEngine::createEnemyBat(int px, int py, int pz)
{
    tag::EAnimation* anim = m_tagEngine.createNumAnimations(2, "media/Bat/bat.bmp");
    m_tagEngine.createAnimation(anim, "media/Bat/BatRun/murcielago", eAnimEnemyStand, 16);//posicion 0 sera estar parado
    m_tagEngine.createAnimation(anim, "media/Bat/BatDeath/batDeath", eAnimEnemyDeath, 5, false);
    anim->setActiveAnimation(0);

    tag::GraphicNode* node = m_tagEngine.createNodeAnimations(anim, vec3f(0,0,0), vec3f(0,0,0));
    Bat* b = new Bat();
    b->setNode(new Node(node));
    b->setPosition(dwe::vec3f(px, py, pz));
    b->SetVision();

    NetInstance->addNetEnemy(b);
    return b;

}

Guardian* dwe::GraphicsEngine::createEnemyGuardian(int px, int py, int pz)
{
    tag::EAnimation* anim = m_tagEngine.createNumAnimations(4, "media/Grande/grande.bmp");
    m_tagEngine.createAnimation(anim, "media/Grande/Stand/grandeStand",   eAnimEnemyStand,   1);
    m_tagEngine.createAnimation(anim, "media/Grande/Death/grandeDeath",   eAnimEnemyDeath,  17, false);
    m_tagEngine.createAnimation(anim, "media/Grande/Walk/grandeWalk",     eAnimEnemyWalk,    9);
    m_tagEngine.createAnimation(anim, "media/Grande/Attack/grandeAttack", eAnimEnemyAttack, 17);
    anim->setActiveAnimation(0);

    tag::GraphicNode* node = m_tagEngine.createNodeAnimations(anim, vec3f(0,0,0), vec3f(0,0,0));
    Guardian* g = new Guardian();
	g->setNode(new Node(node));
    g->setPosition(dwe::vec3f(px, py, pz));
    g->SetVision();

	NetInstance->addNetEnemy(g);
	return g;
}

Legless* dwe::GraphicsEngine::createEnemyLegless(int px, int py, int pz)
{
    tag::EAnimation* anim = m_tagEngine.createNumAnimations(4, "media/Legless/legless.bmp");
    m_tagEngine.createAnimation(anim, "media/Legless/Stand/leglessStand",   eAnimEnemyStand,  1);
    m_tagEngine.createAnimation(anim, "media/Legless/Death/leglessDeath",   eAnimEnemyDeath,  7, false);
    m_tagEngine.createAnimation(anim, "media/Legless/Walk/leglessWalk",     eAnimEnemyWalk,   9);
    m_tagEngine.createAnimation(anim, "media/Legless/Attack/leglessAttack", eAnimEnemyAttack,15);
    anim->setActiveAnimation(0);

    tag::GraphicNode* node = m_tagEngine.createNodeAnimations(anim, vec3f(0,0,0), vec3f(0,0,0));
    Legless* l = new Legless();
    l->setNode(new Node(node));
    l->setPosition(dwe::vec3f(px, py, pz));
    l->SetVision();

    NetInstance->addNetEnemy(l);
    return l;
}

Door* dwe::GraphicsEngine::createDoor(int f, bool a, float px, float py, float pz, Drawable* parent)
{
    tag::GraphicNode* p = parent ? parent->getNode()->getNode() : 0;
	tag::GraphicNode* node = m_tagEngine.createMesh("media/unityPuerta_50m.obj", vec3f(0,0,0), vec3f(0,0,0), "media/unityPuerta_50m.bmp", p);
    Door* d = new Door(f, a);
	d->setNode(new Node(node));

    d->setPosition(dwe::vec3f(px, py, pz)); // Cerrada
    d->SetSensor();
	d->setPositionClosed(dwe::vec3f(px, py, pz)); // Localizaci�n de la puerta CERRADA
	d->setPositionOpened(dwe::vec3f(px, py, pz));
	if(f==1 || f==3)
        d->setRotation(vec3f(0,90,0));

	NetInstance->addNetEntity(d);
	return d;
}

DoorRotate* dwe::GraphicsEngine::createDoorRotate(int f, bool a, float px, float py, float pz, Drawable* parent)
{
    tag::GraphicNode* p = parent ? parent->getNode()->getNode() : 0;
	tag::GraphicNode* node = m_tagEngine.createMesh("media/unityPuerta_50m.obj", vec3f(0,0,0), vec3f(0,0,0), "media/unityPuerta_50m.bmp", p);
    DoorRotate* d = new DoorRotate(f, a);
	d->setNode(new Node(node));
    d->setPosition(dwe::vec3f(px, py, pz));
	if(f==1 || f==3)
        d->setRotation(vec3f(0,90,0));

	return d;
}

Projectile* dwe::GraphicsEngine::createProjectile(vec3f origin, float angle, std::string weapon, int damage)
{
	tag::GraphicNode* node = m_tagEngine.createMesh("media/" + weapon + ".obj", vec3f(0,0,0), vec3f(0,0,0), "media/bullet.bmp");
    Projectile* p = new Projectile(origin, angle, damage);
	p->setNode(new Node(node));
	p->setPosition(origin);
	return p;
}

ProjectileGrenade* dwe::GraphicsEngine::createProjectileGrenade(vec3f origin, float angle)
{
	tag::GraphicNode* node = m_tagEngine.createMesh("media/Weapons/Grenade/grenade.obj", vec3f(0,0,0), vec3f(0,0,0), "media/Weapons/Grenade/grenade.bmp");
    ProjectileGrenade* p = new ProjectileGrenade(vec3f(origin.x, 0, origin.z), angle);
	p->setNode(new Node(node));
	p->setPosition(vec3f(origin.x, 0, origin.z));
	return p;
}

GrenadeExplosion* dwe::GraphicsEngine::createGrenadeExplosion(vec3f origin)
{
    tag::EAnimation* anim = m_tagEngine.createNumAnimations(1, "media/explosionAnimation/explosion.bmp");
    m_tagEngine.createAnimation(anim, "media/explosionAnimation/explosion",   eAnimGrenade,  11);
    anim->setActiveAnimation(0);

    tag::GraphicNode* node = m_tagEngine.createNodeAnimations(anim, vec3f(0,0,0), vec3f(0,0,0));
    GrenadeExplosion* g = new GrenadeExplosion();
	g->setNode(new Node(node));
	g->setPosition(vec3f(origin.x, 0, origin.z));
	return g;
}

Generator* dwe::GraphicsEngine::createGenerator(int i, bool b, Drawable* parent)
{
    tag::GraphicNode* p = parent ? parent->getNode()->getNode() : 0;
	tag::GraphicNode* node = m_tagEngine.createMesh("media/generador.obj", vec3f(0,0,0), vec3f(0,0,0), "media/generador.bmp", p);
    Generator* g = new Generator(i, b);
	g->setNode(new Node(node));
    NetInstance->addNetEntity(g);
	return g;
}

MagnetKey* dwe::GraphicsEngine::createMagnetKey(int i, float px, float py, float pz, Drawable* parent)
{
    tag::GraphicNode* p = parent ? parent->getNode()->getNode() : 0;
	tag::GraphicNode* node = m_tagEngine.createMesh("media/Consumables/magnetKey.obj", vec3f(0,0,0), vec3f(0,0,0), "media/Consumables/magnetKey.bmp", p);
    MagnetKey* m = new  MagnetKey(i);
	m->setNode(new Node(node));
	m->setPosition(dwe::vec3f(px, py, pz));

    NetInstance->addNetConsumable(m);
	return m;
}

SpeedBoost* dwe::GraphicsEngine::createSpeedBoost(float px, float py, float pz, Drawable* parent)
{
    tag::GraphicNode* p = parent ? parent->getNode()->getNode() : 0;
	tag::GraphicNode* node = m_tagEngine.createMesh("media/Consumables/jeringuilla.obj", vec3f(0,0,0), vec3f(0,0,0), "media/Consumables/jeringuilla.bmp", p);
    SpeedBoost* s = new SpeedBoost();
	s->setNode(new Node(node));
	s->setPosition(dwe::vec3f(px, py, pz));

	NetInstance->addNetConsumable(s);
	return s;
}

Medkit* dwe::GraphicsEngine::createMedkit(float px, float py, float pz, Drawable* parent)
{
    tag::GraphicNode* p = parent ? parent->getNode()->getNode() : 0;
	tag::GraphicNode* node = m_tagEngine.createMesh("media/Consumables/Medkit.obj", vec3f(0,0,0), vec3f(0,0,0), "media/Consumables/Medkit.bmp", p);
    Medkit* h = new Medkit();
	h->setNode(new Node(node));
	h->setPosition(dwe::vec3f(px, py, pz));

	NetInstance->addNetConsumable(h);
	return h;
}

Ammo* dwe::GraphicsEngine::createAmmo(float px, float py, float pz, Drawable* parent)
{
    tag::GraphicNode* p = parent ? parent->getNode()->getNode() : 0;
	tag::GraphicNode* node = m_tagEngine.createMesh("media/Consumables/ammo.obj", vec3f(0,0,0), vec3f(0,0,0), "media/consumables/ammo.bmp", p);
    Ammo* a = new Ammo();
	a->setNode(new Node(node));
	a->setPosition(dwe::vec3f(px, py, pz));

	NetInstance->addNetConsumable(a);
	return a;
}

Gun* dwe::GraphicsEngine::createGun(Drawable* player)
{
	tag::GraphicNode* node = m_tagEngine.createMesh("media/Weapons/Gun/Gun.obj", vec3f(0,0,0), vec3f(0,0,0), "media/Weapons/Gun/gun.bmp", player->getNode()->getNode());
    Gun* g = new Gun();
	g->setNode(new Node(node));

	return g;
}

Shotgun* dwe::GraphicsEngine::createShotgun(Drawable* player)
{
	tag::GraphicNode* node = m_tagEngine.createMesh("media/Weapons/Shotgun/Shotgun.obj", vec3f(0,0,0), vec3f(0,0,0), "media/Weapons/Shotgun/shotgun.bmp", player->getNode()->getNode());
    Shotgun* sg = new Shotgun();
	sg->setNode(new Node(node));

	return sg;
}

Rifle* dwe::GraphicsEngine::createRifle(Drawable* player)
{
	tag::GraphicNode* node = m_tagEngine.createMesh("media/Weapons/Rifle/Rifle.obj", vec3f(0,0,0), vec3f(0,0,0), "media/Weapons/Rifle/rifle.bmp", player->getNode()->getNode());
    Rifle* r = new Rifle();
	r->setNode(new Node(node));

	return r;
}

CShotgun* dwe::GraphicsEngine::createCShotgun(float px, float py, float pz, Drawable* parent)
{
    tag::GraphicNode* p = parent ? parent->getNode()->getNode() : 0;
	tag::GraphicNode* node = m_tagEngine.createMesh("media/Weapons/Shotgun/Shotgun.obj", vec3f(0,0,0), vec3f(0,0,0), "media/Weapons/Shotgun/shotgun.bmp", p);
    CShotgun* sg = new CShotgun();
	sg->setNode(new Node(node));
	sg->setPosition(dwe::vec3f(px, py, pz));

	NetInstance->addNetConsumable(sg);
	return sg;
}

CRifle* dwe::GraphicsEngine::createCRifle(float px, float py, float pz, Drawable* parent)
{
    tag::GraphicNode* p = parent ? parent->getNode()->getNode() : 0;
	tag::GraphicNode* node = m_tagEngine.createMesh("media/Weapons/Rifle/Rifle.obj", vec3f(0,0,0), vec3f(0,0,0), "media/Weapons/Rifle/rifle.bmp", p);
    CRifle* r = new CRifle();
	r->setNode(new Node(node));
	r->setPosition(dwe::vec3f(px, py, pz));

    NetInstance->addNetConsumable(r);
	return r;
}

//////////////////////////
void dwe::GraphicsEngine::close()
{

}

//////////////////////////
void dwe::GraphicsEngine::createCamera()
{
    if (!m_camera)
    {
        m_cameraPosition = vec3f(-150.0,120.0,-190.0);
        m_camera = m_tagEngine.createPerspectiveCamera(m_cameraPosition, vec3f(0,0,0), 45.0f, get_screenWidth() / get_screenHeight(), 0.1f, 1000.0f);
        m_tagEngine.nodeLookAtTarget(m_camera, m_cameraPosition, vec3f(0,0,0));

        float ambiente = 0.5;
        float difusa   = 0.8;
        float specular = 1.0;

        m_tagEngine.createLight(dwe::vec3f(170.0,120.0,80.0), vec3f(0), vec3f(ambiente), vec3f(difusa), vec3f(specular));
    }
}

//////////////////////////
void dwe::GraphicsEngine::updateCamera(const dwe::vec3f playerPosition, int moreEnemiesX, int moreEnemiesZ)
{
    float cursorX = GEInstance->receiver.getCursorX();
    float cursorY = GEInstance->receiver.getCursorY();
    int   width   = GEInstance->get_screenWidth();
    int   height  = GEInstance->get_screenHeight();
    int   borderL = width - (width-_camera_border);
    int   borderR = width-_camera_border;
    int   borderU = height - (height-_camera_border);
    int   borderD = height-_camera_border;

    //update camera target
    //Desencuadre horizontal
    if(cursorX < borderL){
        if(tarLR > -_camera_desviation)       tarLR -= _camera_progression;
    }else if(cursorX > borderR){
        if(tarLR < _camera_desviation)        tarLR+=_camera_progression;
    }else{
        //Volver a centrar
        if(tarLR!=0)
            if(tarLR<0)     tarLR+=_camera_progression;
            else            tarLR-=_camera_progression;
        else
            tarLR = 0;
    }

    //Desencuadre vertical
    if(cursorY < borderU){
        if(tarUD > -_camera_desviation)        tarUD-=_camera_progression;
    }else if(cursorY > borderD){
        if(tarUD < _camera_desviation)         tarUD+=_camera_progression;
    }else{
        //Volver a centrar
        if(tarUD!=0)
            if(tarUD<0)     tarUD+=_camera_progression;
            else            tarUD-=_camera_progression;
        else
            tarUD = 0;
    }


    int des  = _camera_desviation/2;
    float prog = 0.25f;
    //DEPENDE DE LOS ENEMIGOS
    if(moreEnemiesX!=0 && (moreEnemiesX>2 || moreEnemiesX<-2) ){
        if(moreEnemiesX>0)
            if(zoomX < des)      zoomX += prog;
        if(moreEnemiesX<0)
            if(zoomX > -des)     zoomX -= prog;
    }else{
        if(zoomX!=0)
            if(zoomX<0)          zoomX += prog;
            else                 zoomX -= prog;
        else
            zoomX = 0;
    }

    //DEPENDE DE LOS ENEMIGOS
    if(moreEnemiesZ!=0 && (moreEnemiesZ>2 || moreEnemiesZ<-2) ){
        if(moreEnemiesZ>0)
            if(zoomZ < des)      zoomZ += prog;
        if(moreEnemiesZ<0)
            if(zoomZ > -des)     zoomZ -= prog;
    }else{
        if(zoomZ!=0)
            if(zoomZ<0)          zoomZ += prog;
            else                 zoomZ -= prog;
        else
            zoomZ = 0;
    }

    m_cameraPosition = vec3f(playerPosition.x+tarLR + zoomX, _camera_y + abs(zoomX) + abs(zoomZ), (playerPosition.z + _camera_z_offset + tarUD));
    m_tagEngine.nodeLookAtTarget(m_camera, m_cameraPosition,
            vec3f(playerPosition.x+ tarLR + zoomX, playerPosition.y, (playerPosition.z+tarUD + zoomZ)));  // target position
}

//////////////////////////
void dwe::GraphicsEngine::addMessageLine(std::string text)
{
    for(int i=MAX_MESSAGE_LINES-1; i>0; i--)
        m_messageLine[i].setString(m_messageLine[i-1].getString());
    m_messageLine[0].setString(text);
}

////////////////////////////////
dwe::vec3f dwe::GraphicsEngine::getCameraPosition()
{
    return m_cameraPosition;
}

//////////////////////////
float dwe::GraphicsEngine::angleToScreenCoords(Drawable *object)
{
    return m_tagEngine.angleToScreenCoords(object->getPosition(), vec3f(receiver.getCursorX(), receiver.getCursorY(), 0));
}

//////////////////////////
void dwe::GraphicsEngine::setOwnCursor(bool ownCursor)
{
    m_ownCursor = ownCursor;
    m_window->setMouseCursorVisible(!ownCursor);
}

void dwe::GraphicsEngine::leerFicheroOpciones()
{
    /*struct TOptionsFile
    {
        std::string name;
        void*       value;
    };
    static TOptionsFile options[] = {
        {"width",       &dwe::GraphicsEngine::_screenWidth},
        {"height",      &dwe::GraphicsEngine::_screenHeight},
        {"fullscreen",  &dwe::GraphicsEngine::_fullScreen},
        {"vsync",       &dwe::GraphicsEngine::_vsync},
        {"shadows",     &dwe::GraphicsEngine::_shadows},
        {"0", 0}  // Marca de fin
    };*/

    ifstream fich("options.ini");
    if (fich.is_open())
    {
        std::string name;
        int value;
        while (fich >> name >> value)
        {
            /*uint8_t i=0;
            while (options[i].name!=name && options[i].name!="0")
                i++;

            if (options[i].name!="0")  // Encontrado
                *(int*)(options[i].value) = value;*/

            if (name=="width")
                dwe::GraphicsEngine::_screenWidth = value;
            else if (name=="height")
                dwe::GraphicsEngine::_screenHeight = value;
            else if (name=="fullscreen")
                dwe::GraphicsEngine::_fullScreen = value;
            else if (name=="vsync")
                dwe::GraphicsEngine::_vsync = value;
            else if (name=="shadows")
                dwe::GraphicsEngine::_shadows = value;
        }
    }
}






