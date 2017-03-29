#define GLEW_STATIC
#include<GL/glew.h>
#include <glm/glm.hpp>

#include "GraphicsEngine.h"
#include "Player.h"
#include "PlayerMate.h"
#include "Humanoid.h"
#include "Dog.h"
#include "NetGame.h"

#include "EntityPhysics.h"
#include "WorldInstance.h"

#include "Door.h"
#include "Projectile.h"
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

    m_window = new sf::RenderWindow(sf::VideoMode(GraphicsEngine::_screenWidth, GraphicsEngine::_screenHeight), "Lab21", sf::Style::Default, contextSettings);

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
    m_clock.restart();
}

//////////////////////////
void dwe::GraphicsEngine::release()
{
}

//////////////////////////
bool dwe::GraphicsEngine::isRunning()
{
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

//////////////////////////
void dwe::GraphicsEngine::draw()
{
    m_window->setActive(true);
    m_tagEngine.draw();

    m_window->setActive(false);


    // Entre pushGLStates y popGLStates dibujamos los sprites
    m_window->pushGLStates();

    // Lineas de mensaje del jugador
    for(unsigned int i=0; i<MAX_MESSAGE_LINES; i++)
        m_window->draw(m_messageLine[i]);

    m_window->popGLStates();

    /*
    m_window->display();

    char tmp[25];
    float fps = 1.f / (m_clock.getElapsedTime().asSeconds() - m_secondsLastDraw);
    m_secondsLastDraw = m_clock.getElapsedTime().asSeconds();
    sprintf(tmp, "Lab21 - fps:%f", fps);
    m_window->setTitle(tmp);
    */
}

/*******/
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

void dwe::GraphicsEngine::clearWindow()
{
    m_window->clear();
}

void dwe::GraphicsEngine::displayWindow()
{
    m_window->display();

    char tmp[25];
    float fps = 1.f / (m_clock.getElapsedTime().asSeconds() - m_secondsLastDraw);
    m_secondsLastDraw = m_clock.getElapsedTime().asSeconds();
    sprintf(tmp, "Lab21 - fps:%f", fps);
    m_window->setTitle(tmp);
}
/*******/

//////////////////////////
void dwe::GraphicsEngine::render()
{
}

////////////////////////////////////////////////////
/*scene::IAnimatedMeshSceneNode* dwe::GraphicsEngine::createIrrAnimatedMeshSceneNode(std::string meshName)
{
	scene::IAnimatedMesh* mesh = m_smgr->getMesh((meshName+".obj").c_str());
	if (!mesh)
	{
		m_device->drop();
		exit(0);
	}
	scene::IAnimatedMeshSceneNode* irrnode = m_smgr->addAnimatedMeshSceneNode( mesh );

	if (irrnode)
	{
		irrnode->setMaterialFlag(EMF_LIGHTING, false);  // Desactivamos iluminacion, solo para pruebas
		irrnode->setMaterialTexture( 0, m_driver->getTexture((meshName+".png").c_str()) );
	}

	return irrnode;
}*/

/////////////////////////////////////
ScenaryElement* dwe::GraphicsEngine::createWall(std::string meshName)
{
    tag::GraphicNode* node = m_tagEngine.createMesh(meshName+".obj", vec3f(0,0,0), vec3f(0,0,0));

    ScenaryElement* s = new ScenaryElement();
    s->setNode(new Node(node));
    return s;
}


////////////////////////////////
dwe::Node* dwe::GraphicsEngine::createNode(std::string meshName)
{
    tag::GraphicNode* gn = m_tagEngine.createMesh(meshName+".obj", vec3f(0,0,0), vec3f(0,0,0));
    Node* node = new Node(gn);
    return node;
}

/*vector3df dwe::GraphicsEngine::getTransformedBoundingBox(scene::IAnimatedMeshSceneNode* player){
    return(player->getTransformedBoundingBox().getExtent());
}*/


/////////////////////////////
Player* dwe::GraphicsEngine::createMainPlayer(Gun* gun)
{
	tag::GraphicNode* node = m_tagEngine.createMesh("media/player.obj", vec3f(0,0,0), vec3f(0,0,0));
	Player* p = new Player(gun);
	p->setNode(new Node(node));

	NetInstance->addNetObject(p);
	return p;

	// setMaterialTexture( 0, m_driver->getTexture("media/sydney.bmp") );
}



/////////////////////////////////
PlayerMate* dwe::GraphicsEngine::createPlayerMate()
{
	tag::GraphicNode* node = m_tagEngine.createMesh("media/playermate.md2", vec3f(0,0,0), vec3f(0,0,0));
	PlayerMate* p = new PlayerMate();
	p->setNode(new Node(node));

	NetInstance->addNetObject(p);
	return p;
}

////////////////////////////
Humanoid* dwe::GraphicsEngine::createEnemyHumanoid()
{
	tag::GraphicNode* node = m_tagEngine.createMesh("media/faerie.md2", vec3f(0,0,0), vec3f(0,0,0));
    Humanoid* p = new Humanoid();
	p->setNode(new Node(node));

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
Dog* dwe::GraphicsEngine::createEnemyDog()
{
	tag::GraphicNode* node = m_tagEngine.createMesh("media/perro.obj", vec3f(0,0,0), vec3f(0,0,0), "media/perro.bmp");
    Dog* p = new Dog();
	p->setNode(new Node(node));

	NetInstance->addNetEnemy(p);
	return p;
}

Door* dwe::GraphicsEngine::createDoor(int f, bool a, float px, float py, float pz)
{
	tag::GraphicNode* node = m_tagEngine.createMesh("media/unityPuerta_50m.obj", vec3f(0,0,0), vec3f(0,0,0));
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

Generator* dwe::GraphicsEngine::createGenerator(int i, bool b, float px, float py, float pz)
{
	tag::GraphicNode* node = m_tagEngine.createMesh("media/generador.obj", vec3f(0,0,0), vec3f(0,0,0));
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
	tag::GraphicNode* node = m_tagEngine.createMesh("media/Gun/gun.obj", vec3f(0,0,0), vec3f(0,0,0));
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
    vec3f position(-150,120,-190);
    m_camera = m_tagEngine.createPerspectiveCamera(position, vec3f(0,0,0), 45.0f, get_screenWidth() / get_screenHeight(), 0.1f, 1000.0f);
    m_tagEngine.nodeLookAtTarget(m_camera, position, vec3f(0,0,0));
    m_tagEngine.createLight(vec3f(-100,100,50), vec3f(0,0,0));
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

