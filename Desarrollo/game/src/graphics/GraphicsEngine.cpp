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

#include "NetGame.h"

#include "EntityPhysics.h"
#include "WorldInstance.h"

#include "Door.h"
#include "Projectile.h"
#include "ProjectileGrenade.h"
#include "Generator.h"
#include "MagnetKey.h"
#include "SpeedBoost.h"
#include "Medkit.h"

#include "Trigger.h"
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
ScenaryElement* dwe::GraphicsEngine::createWall(std::string meshName)
{
    tag::GraphicNode* node = m_tagEngine.createMesh(meshName+".obj", vec3f(0,0,0), vec3f(0,0,0), "media/unityPared.bmp");

    ScenaryElement* s = new ScenaryElement();
    s->setNode(new Node(node));
    return s;
}


////////////////////////////////
dwe::Node* dwe::GraphicsEngine::createNode(std::string meshName)
{
    tag::GraphicNode* gn;
    //if (meshName == "media/unitySuelo_Hall")
        gn = m_tagEngine.createMesh(meshName+".obj", vec3f(0,0,0), vec3f(0,0,0), "media/unitySuelo_Hall.bmp");
    //else
      //  gn = m_tagEngine.createMesh(meshName+".obj", vec3f(0,0,0), vec3f(0,0,0));
    Node* node = new Node(gn);
    return node;
}


/////////////////////////////
Player* dwe::GraphicsEngine::createMainPlayer(Gun* gun)
{
    tag::EAnimation* anim = m_tagEngine.createNumAnimations(2);
    m_tagEngine.createAnimation(anim, "media/playerStand/playerStand", 0, 1);//posicion 0 sera estar parado
    m_tagEngine.createAnimation(anim, "media/playerRun/playerRun", 1, 8);//posicion 0 sera correr
    anim->setNumAnimation(0);

    tag::GraphicNode* node = m_tagEngine.createNodeAnimations(anim, vec3f(0,0,0), vec3f(0,0,0));
	Player* p = new Player(gun);
	p->setNode(new Node(node));

	NetInstance->addNetObject(p);
	return p;
}



/////////////////////////////////
PlayerMate* dwe::GraphicsEngine::createPlayerMate()
{
    tag::EAnimation* anim = m_tagEngine.createNumAnimations(2);
    m_tagEngine.createAnimation(anim, "media/playerStand/playerStand", 0, 1);//posicion 0 sera estar parado
    m_tagEngine.createAnimation(anim, "media/playerRun/playerRun", 1, 8);//posicion 0 sera correr
    anim->setNumAnimation(0);

    tag::GraphicNode* node = m_tagEngine.createNodeAnimations(anim, vec3f(0,0,0), vec3f(0,0,0));
	PlayerMate* p = new PlayerMate();
	p->setNode(new Node(node));

	NetInstance->addNetObject(p);
	return p;
}

////////////////////////////
Humanoid* dwe::GraphicsEngine::createEnemyHumanoid(int px, int py, int pz)
{
	tag::GraphicNode* node = m_tagEngine.createMesh("media/humanoide.obj", vec3f(0,0,0), vec3f(0,0,0));
    Humanoid* p = new Humanoid();
	p->setNode(new Node(node));
	p->setPosition(dwe::vec3f(px, py, pz));

	NetInstance->addNetEnemy(p);
	return p;

    /*scene::IAnimatedMesh* mesh = m_smgr->getMesh("media/faerie.md2");
	if (!mesh)
	{
		m_device->drop();
		exit(0);
	}
	scene::IAnimatedMeshSceneNode* irrnode = m_smgr->addAnimatedMeshSceneNode( mesh );
	if (irrnode)
	{
		irrnode->setMaterialFlag(EMF_LIGHTING, false);  // Desactivamos iluminacion, solo para pruebas
		irrnode->setMD2Animation(scene::EMAT_STAND);
		irrnode->setMaterialTexture( 0, m_driver->getTexture("media/faerie.bmp") );
	}

	Humanoid* p = new Humanoid();
	p->setNode(new Node(irrnode));
	NetInstance->addNetEnemy(p);
    return p;*/
}

////////////////////////////
Dog* dwe::GraphicsEngine::createEnemyDog(int px, int py, int pz)
{
	tag::GraphicNode* node = m_tagEngine.createMesh("media/perro.obj", vec3f(0,0,0), vec3f(0,0,0), "media/perro.bmp");
//	tag::GraphicNode* node = m_tagEngine.createMesh("media/perro.obj", vec3f(0,0,0), vec3f(0,0,0));
    Dog* p = new Dog();
	p->setNode(new Node(node));
    p->setPosition(dwe::vec3f(px, py, pz));
	NetInstance->addNetEnemy(p);
	return p;
}

Bat* dwe::GraphicsEngine::createEnemyBat(int px, int py, int pz)
{
    tag::EAnimation* anim = m_tagEngine.createNumAnimations(1);
    m_tagEngine.createAnimation(anim, "media/Bat/BatRun/murcielago", 0, 16);//posicion 0 sera estar parado
    anim->setNumAnimation(0);

    tag::GraphicNode* node = m_tagEngine.createNodeAnimations(anim, vec3f(0,0,0), vec3f(0,0,0));
    Bat* b = new Bat();
    b->setNode(new Node(node));
    b->setPosition(dwe::vec3f(px, py, pz));

    NetInstance->addNetEnemy(b);
    return b;

}

Guardian* dwe::GraphicsEngine::createEnemyGuardian(int px, int py, int pz)
{
    tag::GraphicNode* node = m_tagEngine.createMesh("media/grande.obj", vec3f(0,0,0), vec3f(0,0,0));
    Guardian* g = new Guardian();
	g->setNode(new Node(node));
    g->setPosition(dwe::vec3f(px, py, pz));
	NetInstance->addNetEnemy(g);
	return g;
}

Legless* dwe::GraphicsEngine::createEnemyLegless(int px, int py, int pz)
{
    tag::EAnimation* anim = m_tagEngine.createNumAnimations(1);
    m_tagEngine.createAnimation(anim, "media/Legless/LeglessRun/sinpiernas", 0, 9);//posicion 0 sera estar parado
    anim->setNumAnimation(0);

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
	d->setPositionClosed(dwe::vec3f(px, py, pz)); // Localización de la puerta CERRADA
	d->setPositionOpened(dwe::vec3f(px, py, pz));
	if(f==1 || f==3)
        d->setRotation(vec3f(0,90,0));

	NetInstance->addNetEntity(d);
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
    ProjectileGrenade* p = new ProjectileGrenade(origin, angle);
	p->setNode(new Node(node));
	p->setPosition(origin);
	return p;
}

Generator* dwe::GraphicsEngine::createGenerator(int i, bool b, float px, float py, float pz)
{
	tag::GraphicNode* node = m_tagEngine.createMesh("media/generador.obj", vec3f(0,0,0), vec3f(0,0,0), "media/generador.bmp");
//	tag::GraphicNode* node = m_tagEngine.createMesh("media/generador.obj", vec3f(0,0,0), vec3f(0,0,0));
    Generator* g = new Generator(i, b);
	g->setNode(new Node(node));
	g->setPosition(dwe::vec3f(px, py, pz));
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

Gun* dwe::GraphicsEngine::createGun(float px, float py, float pz)
{
	tag::GraphicNode* node = m_tagEngine.createMesh("media/ammm/Gun.obj", vec3f(0,0,0), vec3f(0,0,0));
    Gun* g = new Gun();
	g->setNode(new Node(node));
	g->setPosition(dwe::vec3f(px, py, pz));

	return g;
}

Shotgun* dwe::GraphicsEngine::createShotgun(float px, float py, float pz)
{
	tag::GraphicNode* node = m_tagEngine.createMesh("media/ammm/Shotgun.obj", vec3f(0,0,0), vec3f(0,0,0));
    Shotgun* sg = new Shotgun();
	sg->setNode(new Node(node));
	sg->setPosition(dwe::vec3f(px, py, pz));

	return sg;
}

Rifle* dwe::GraphicsEngine::createRifle(float px, float py, float pz)
{
	tag::GraphicNode* node = m_tagEngine.createMesh("media/ammm/Rifle.obj", vec3f(0,0,0), vec3f(0,0,0));
    Rifle* r = new Rifle();
	r->setNode(new Node(node));
	r->setPosition(dwe::vec3f(px, py, pz));

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

TriggerDoor* dwe::GraphicsEngine::createTriggerDoor(float px, float py, float pz)
{
    tag::GraphicNode* node = m_tagEngine.createMesh("media/triggerDoor.obj", vec3f(0,0,0), vec3f(0,0,0));
    TriggerDoor* t = new TriggerDoor();
	t->setNode(new Node(node));
	t->setPosition(dwe::vec3f(px, py, pz));

	return t;
}

TriggerGenerator* dwe::GraphicsEngine::createTriggerGenerator(float px, float py, float pz)
{
    tag::GraphicNode* node = m_tagEngine.createMesh("media/triggerGenerator.obj", vec3f(0,0,0), vec3f(0,0,0));
    TriggerGenerator* t = new TriggerGenerator();
	t->setNode(new Node(node));
	t->setPosition(dwe::vec3f(px, py, pz));

	return t;
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
        vec3f position(-150,120,-190);
        m_camera = m_tagEngine.createPerspectiveCamera(position, vec3f(0,0,0), 45.0f, get_screenWidth() / get_screenHeight(), 0.1f, 1000.0f);
        m_tagEngine.nodeLookAtTarget(m_camera, position, vec3f(0,0,0));
        float n = 0.8;
        m_tagEngine.createLight(vec3f(-100,100,50), vec3f(0,0,0), vec3f(n,n,n), vec3f(n,n,n), vec3f(n+0.4,n+0.4,n+0.4));
    }
}

//////////////////////////
void dwe::GraphicsEngine::updateCamera(const dwe::vec3f playerPosition, int moreEnemiesX, int moreEnemiesZ)
{
    float cursorX = GEInstance->receiver.getCursorX();
    float cursorY = GEInstance->receiver.getCursorY();
    int   width   = GEInstance->get_screenWidth();
    int   height  = GEInstance->get_screenHeight();
    int   borderL = width - (width-50);
    int   borderR = width-50;
    int   borderU = height - (height-50);
    int   borderD = height-50;

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

    m_tagEngine.nodeLookAtTarget(m_camera,
            vec3f(playerPosition.x+tarLR + zoomX, _camera_y + abs(zoomX) + abs(zoomZ), (playerPosition.z + _camera_z_offset + tarUD)),
            vec3f(playerPosition.x+ tarLR + zoomX, playerPosition.y, (playerPosition.z+tarUD + zoomZ)));
}

//////////////////////////
void dwe::GraphicsEngine::addMessageLine(std::string text)
{
    for(int i=MAX_MESSAGE_LINES-1; i>0; i--)
        m_messageLine[i].setString(m_messageLine[i-1].getString());
    m_messageLine[0].setString(text);
}
