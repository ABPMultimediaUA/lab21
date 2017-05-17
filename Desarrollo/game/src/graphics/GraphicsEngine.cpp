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

#include "TriggerDoor.h"
#include "TriggerGenerator.h"

#include "ScenaryElement.h"

#include <iostream>
#include <cmath>

#include "CShotgun.h"
#include "CRifle.h"
#include "Gun.h"
#include "Shotgun.h"
#include "Rifle.h"
#include "AmmoGun.h"
#include "GrenadeExplosion.h"
#include "tag/EAnimation.h"

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

    sf::Uint32 style;
    if (_fullScreen)
        style = sf::Style::Fullscreen;
    else
        style = sf::Style::Default;
    //style = sf::Style::Default; // TODO
    m_window = new sf::RenderWindow(sf::VideoMode(GraphicsEngine::_screenWidth, GraphicsEngine::_screenHeight), "Lab21", style, contextSettings);

    // Creamos los mensajes de texto, por ahora vacios
    if (!m_font.loadFromFile("media/ExoRegular.otf"))
        throw std::runtime_error("No se ha podido cargar la fuente de texto");

	for(int i=0; i<MAX_MESSAGE_LINES; i++)
	{
        m_messageLine[i].setFont(m_font);
        m_messageLine[i].setCharacterSize(14);
        m_messageLine[i].setFillColor(sf::Color(255, 255, 255, 255));
        m_messageLine[i].setPosition(10.f, GraphicsEngine::_screenHeight - (i+1)*16.f);
        m_messageLine[i].setString("");
	}

    m_tagEngine.init(GraphicsEngine::_screenHeight, GraphicsEngine::_screenWidth);

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
        float fpsDibujado = 1.0 / (m_timeAccumDraw / m_drawsCount);  // Los fps que podría tener

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
ScenaryElement* dwe::GraphicsEngine::createScenaryElement(std::string s, bool b)
{
    tag::GraphicNode* gn;
    if(b)
        gn = m_tagEngine.createMesh("media/"+s+".obj", vec3f(0,0,0), vec3f(0,0,0), "media/"+s+".bmp");
    else
        gn = m_tagEngine.createMesh("media/"+s+".obj", vec3f(0,0,0), vec3f(0,0,0), "media/unityPared.bmp");
    ScenaryElement* se = new ScenaryElement();
    se->setNode(new Node(gn));
    return se;
}

////////////////////////////////
dwe::Node* dwe::GraphicsEngine::createNode(std::string s, bool b)
{
    tag::GraphicNode* gn;
    if(b)
        gn = m_tagEngine.createMesh("media/"+s+".obj", vec3f(0,0,0), vec3f(0,0,0), "media/"+s+".bmp");
    else
        gn = m_tagEngine.createMesh("media/"+s+".obj", vec3f(0,0,0), vec3f(0,0,0), "media/unitySuelo_Hall.bmp");
    Node* node = new Node(gn);
    return node;
}


/////////////////////////////
Player* dwe::GraphicsEngine::createMainPlayer()
{
    tag::EAnimation* anim = m_tagEngine.createNumAnimations(2);
    m_tagEngine.createAnimation(anim, "media/playerStand/playerStand",  eAnimPlayerStand,   1);
    m_tagEngine.createAnimation(anim, "media/playerRun/playerRun",      eAnimPlayerRun,     8);
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
    tag::EAnimation* anim = m_tagEngine.createNumAnimations(2);
    m_tagEngine.createAnimation(anim, "media/playerStand/playerStand",  eAnimPlayerStand,   1);
    m_tagEngine.createAnimation(anim, "media/playerRun/playerRun",      eAnimPlayerRun,     8);
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
    tag::EAnimation* anim = m_tagEngine.createNumAnimations(2);
    m_tagEngine.createAnimation(anim, "media/Humanoid/Stand/humanoide",         eAnimEnemyStand,   1);
    m_tagEngine.createAnimation(anim, "media/Humanoid/Death/humanoideDeath",    eAnimEnemyDeath,   8, false);
    anim->setActiveAnimation(0);

    tag::GraphicNode* node = m_tagEngine.createNodeAnimations(anim, vec3f(0,0,0), vec3f(0,0,0));
    Humanoid* p = new Humanoid();
	p->setNode(new Node(node));
	p->setPosition(dwe::vec3f(px, py, pz));

	NetInstance->addNetEnemy(p);
	return p;
}

////////////////////////////
Mother* dwe::GraphicsEngine::createEnemyMother(int px, int py, int pz)
{
tag::GraphicNode* node = m_tagEngine.createMesh("media/madre.obj", vec3f(0,0,0), vec3f(0,0,0));
    Mother* p = new Mother();
	p->setNode(new Node(node));
	p->setPosition(dwe::vec3f(px, py, pz));

	return p;
}

////////////////////////////
Dog* dwe::GraphicsEngine::createEnemyDog(int px, int py, int pz)
{
    tag::EAnimation* anim = m_tagEngine.createNumAnimations(5, "media/Dog/dog.bmp");
    m_tagEngine.createAnimation(anim, "media/Dog/Stand/dogStand",   eAnimEnemyStand,   1);
    m_tagEngine.createAnimation(anim, "media/Dog/Death/dogDeath",   eAnimEnemyDeath,   9, false);
    m_tagEngine.createAnimation(anim, "media/Dog/Walk/dogWalk",     eAnimEnemyWalk,   11);
    m_tagEngine.createAnimation(anim, "media/Dog/Attack/dogAttack", eAnimEnemyAttack,  5);
    m_tagEngine.createAnimation(anim, "media/Dog/Run/dogRun",       eAnimEnemyAttack, 11);
    anim->setActiveAnimation(0);

    tag::GraphicNode* node = m_tagEngine.createNodeAnimations(anim, vec3f(0,0,0), vec3f(0,0,0));

    Dog* p = new Dog();
	p->setNode(new Node(node));
    p->setPosition(dwe::vec3f(px, py, pz));
	NetInstance->addNetEnemy(p);
	return p;
}

Bat* dwe::GraphicsEngine::createEnemyBat(int px, int py, int pz)
{
    tag::EAnimation* anim = m_tagEngine.createNumAnimations(1);
    m_tagEngine.createAnimation(anim, "media/Bat/BatRun/murcielago", eAnimEnemyStand, 16);//posicion 0 sera estar parado
    anim->setActiveAnimation(0);

    tag::GraphicNode* node = m_tagEngine.createNodeAnimations(anim, vec3f(0,0,0), vec3f(0,0,0));
    Bat* b = new Bat();
    b->setNode(new Node(node));
    b->setPosition(dwe::vec3f(px, py, pz));

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

    NetInstance->addNetEnemy(l);
    return l;
}

Door* dwe::GraphicsEngine::createDoor(int f, bool a, float px, float py, float pz)
{
	tag::GraphicNode* node = m_tagEngine.createMesh("media/unityPuerta_50m.obj", vec3f(0,0,0), vec3f(0,0,0), "media/unityPuerta_50m.bmp");
    Door* d = new Door(f, a);
	d->setNode(new Node(node));

    d->setPosition(dwe::vec3f(px, py, pz)); // Cerrada
    d->SetSensor();
	d->setPositionClosed(dwe::vec3f(px, py, pz)); // Localización de la puerta CERRADA
	d->setPositionOpened(dwe::vec3f(px, py, pz));
	if(f==1 || f==3)
        d->setRotation(vec3f(0,90,0));

	NetInstance->addNetEntity(d);
	return d;
}

DoorRotate* dwe::GraphicsEngine::createDoorRotate(int f, bool a, float px, float py, float pz)
{
	tag::GraphicNode* node = m_tagEngine.createMesh("media/unityPuerta_50m.obj", vec3f(0,0,0), vec3f(0,0,0), "media/unityPuerta_50m.bmp");
    DoorRotate* d = new DoorRotate(f, a);
	d->setNode(new Node(node));
    d->setPosition(dwe::vec3f(px, py, pz));
	if(f==1 || f==3)
        d->setRotation(vec3f(0,90,0));

	return d;
}

Projectile* dwe::GraphicsEngine::createProjectile(vec3f origin, float angle, std::string weapon)
{
	tag::GraphicNode* node = m_tagEngine.createMesh("media/" + weapon + ".obj", vec3f(0,0,0), vec3f(0,0,0));
    Projectile* p = new Projectile(origin, angle);
	p->setNode(new Node(node));
	p->setPosition(origin);
	return p;
}

ProjectileGrenade* dwe::GraphicsEngine::createProjectileGrenade(vec3f origin, float angle)
{
	tag::GraphicNode* node = m_tagEngine.createMesh("media/grenade.obj", vec3f(0,0,0), vec3f(0,0,0));
    ProjectileGrenade* p = new ProjectileGrenade(vec3f(origin.x, 0, origin.z), angle);
	p->setNode(new Node(node));
	p->setPosition(vec3f(origin.x, 0, origin.z));
	return p;
}

GrenadeExplosion* dwe::GraphicsEngine::createGrenadeExplosion(vec3f origin)
{
	tag::GraphicNode* node = m_tagEngine.createMesh("media/explosion.obj", vec3f(0,0,0), vec3f(0,0,0));
    GrenadeExplosion* g = new GrenadeExplosion();
	g->setNode(new Node(node));
	g->setPosition(vec3f(origin.x, 0, origin.z));
	return g;
}

Generator* dwe::GraphicsEngine::createGenerator(int i, bool b, float px, float py, float pz)
{
	tag::GraphicNode* node = m_tagEngine.createMesh("media/generador.obj", vec3f(0,0,0), vec3f(0,0,0), "media/generador.bmp");
    Generator* g = new Generator(i, b);
	g->setNode(new Node(node));
	g->setPosition(dwe::vec3f(px, py, pz));
	g->SetSensor();
    NetInstance->addNetEntity(g);
	return g;
}

MagnetKey* dwe::GraphicsEngine::createMagnetKey(int i, float px, float py, float pz)
{
	tag::GraphicNode* node = m_tagEngine.createMesh("media/llave.obj", vec3f(0,0,0), vec3f(0,0,0));
    MagnetKey* m = new  MagnetKey(i);
	m->setNode(new Node(node));
	m->setPosition(dwe::vec3f(px, py, pz));
	return m;
}

SpeedBoost* dwe::GraphicsEngine::createSpeedBoost(float px, float py, float pz)
{
	tag::GraphicNode* node = m_tagEngine.createMesh("media/speed/speed.obj", vec3f(0,0,0), vec3f(0,0,0));
    SpeedBoost* s = new SpeedBoost();
	s->setNode(new Node(node));
	s->setPosition(dwe::vec3f(px, py, pz));

	NetInstance->addNetConsumable(s);
	return s;
}

Medkit* dwe::GraphicsEngine::createMedkit(float px, float py, float pz)
{
	tag::GraphicNode* node = m_tagEngine.createMesh("media/First_Aid_Med_Kit/FirstAidMedKit.obj", vec3f(0,0,0), vec3f(0,0,0));
    Medkit* h = new Medkit();
	h->setNode(new Node(node));
	h->setPosition(dwe::vec3f(px, py, pz));

	NetInstance->addNetConsumable(h);
	return h;
}

AmmoGun* dwe::GraphicsEngine::createAmmoGun(float px, float py, float pz)
{
	tag::GraphicNode* node = m_tagEngine.createMesh("media/ammm/AmmoGun.obj", vec3f(0,0,0), vec3f(0,0,0));
    AmmoGun* a = new AmmoGun();
	a->setNode(new Node(node));
	a->setPosition(dwe::vec3f(px, py, pz));

	NetInstance->addNetConsumable(a);
	return a;
}

Gun* dwe::GraphicsEngine::createGun(Player* player)
{
	tag::GraphicNode* node = m_tagEngine.createMesh("media/ammm/Gun.obj", vec3f(0,0,0), vec3f(0,0,0), "", player->getNode()->getNode());
    Gun* g = new Gun();
	g->setNode(new Node(node));

	return g;
}

Shotgun* dwe::GraphicsEngine::createShotgun(Player* player)
{
	tag::GraphicNode* node = m_tagEngine.createMesh("media/ammm/Shotgun.obj", vec3f(0,0,0), vec3f(0,0,0), "", player->getNode()->getNode());
    Shotgun* sg = new Shotgun();
	sg->setNode(new Node(node));

	return sg;
}

Rifle* dwe::GraphicsEngine::createRifle(Player* player)
{
	tag::GraphicNode* node = m_tagEngine.createMesh("media/ammm/Rifle.obj", vec3f(0,0,0), vec3f(0,0,0), "", player->getNode()->getNode());
    Rifle* r = new Rifle();
	r->setNode(new Node(node));

	return r;
}

CShotgun* dwe::GraphicsEngine::createCShotgun(float px, float py, float pz)
{
	tag::GraphicNode* node = m_tagEngine.createMesh("media/ammm/Shotgun.obj", vec3f(0,0,0), vec3f(0,0,0));
    CShotgun* sg = new CShotgun();
	sg->setNode(new Node(node));
	sg->setPosition(dwe::vec3f(px, py, pz));

	NetInstance->addNetConsumable(sg);
	return sg;
}

CRifle* dwe::GraphicsEngine::createCRifle(float px, float py, float pz)
{
	tag::GraphicNode* node = m_tagEngine.createMesh("media/ammm/Rifle.obj", vec3f(0,0,0), vec3f(0,0,0));
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
        m_cameraPosition = vec3f(-150,120,-190);
        m_camera = m_tagEngine.createPerspectiveCamera(m_cameraPosition, vec3f(0,0,0), 45.0f, get_screenWidth() / get_screenHeight(), 0.1f, 1000.0f);
        m_tagEngine.nodeLookAtTarget(m_camera, m_cameraPosition, vec3f(0,0,0));

        float n = 0.6;
        m_tagEngine.createLight(dwe::vec3f(140,24,80), vec3f(0,0,0), vec3f(n,n,n), vec3f(n,n,n), vec3f(n+0.4,n+0.4,n+0.4));
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
