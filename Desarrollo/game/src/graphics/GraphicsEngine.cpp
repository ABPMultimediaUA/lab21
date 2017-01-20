#include "GraphicsEngine.h"
#include "Player.h"
#include "PlayerMate.h"
#include "Humanoid.h"
#include "Dog.h"
#include "NetGame.h"
#include "AppReceiver.h"

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

#include "iostream"


using namespace std;
// Necesita volver a poner este namespace
// para que codeblocks autocomplete bien.
// Los demás no, si no tampoco autocompleta.


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
	m_device = createDevice( video::EDT_OPENGL, irr::core::dimension2d<u32>(800, 600), 16,
			false, false, false, &receiver);

	m_device->setWindowCaption(L"Lab21");

	// TODO comprobar que m_device existe if !m_device exit()

    /*
	Get a pointer to the VideoDriver, the SceneManager and the graphical
	user interface environment, so that we do not always have to write
	device->getVideoDriver(), device->getSceneManager(), or
	device->getGUIEnvironment().
	*/
	m_driver = m_device->getVideoDriver();
	m_smgr = m_device->getSceneManager();
	m_guienv = m_device->getGUIEnvironment();


	/*
	We add a hello world label to the window, using the GUI environment.
	The text is placed at the position (10,10) as top left corner and
	(260,22) as lower right corner.
	*/
	m_guienv->addStaticText(L"Hello World! This is the Irrlicht Software renderer!",
		rect<s32>(10,10,260,22), true);

	/*
	To look at the mesh, we place a camera into 3d space at the position
	(0, 30, -40). The camera looks from there to (0,5,0), which is
	approximately the place where our md2 model is.
	*/
	//m_smgr->addCameraSceneNode(0, vector3df(150,180,-200), vector3df(0,0,0));
	m_smgr->addCameraSceneNode(0, vector3df(-150,120,190), vector3df(0,0,0));
}

//////////////////////////
void dwe::GraphicsEngine::release()
{
	/*
	After we are done with the render loop, we have to delete the Irrlicht
	Device created before with createDevice(). In the Irrlicht Engine, you
	have to delete all objects you created with a method or function which
	starts with 'create'. The object is simply deleted by calling ->drop().
	See the documentation at irr::IReferenceCounted::drop() for more
	information.
	*/
	m_device->drop();
}

//////////////////////////
bool dwe::GraphicsEngine::isRunning()
{
  	/*
	Ok, now we have set up the scene, lets draw everything: We run the
	device in a while() loop, until the device does not want to run any
	more. This would be when the user closes the window or presses ALT+F4
	(or whatever keycode closes a window).
	*/

    return m_device->run();
}

//////////////////////////
void dwe::GraphicsEngine::draw()
{
    /*
    Anything can be drawn between a beginScene() and an endScene()
    call. The beginScene() call clears the screen with a color and
    the depth buffer, if desired. Then we let the Scene Manager and
    the GUI Environment draw their content. With the endScene()
    call everything is presented on the screen.
    */
    m_driver->beginScene(true, true, SColor(255,0,0,0));  // a,r,g,b

    m_smgr->drawAll();
    m_guienv->drawAll();

    m_driver->endScene();

    wchar_t tmp[255];
    swprintf(tmp, L"Lab21 - fps:%d triangles:%d", m_driver->getFPS(), m_driver->getPrimitiveCountDrawn());
  	m_device->setWindowCaption(tmp);
}


////////////////////////////////////////////////////
scene::IAnimatedMeshSceneNode* dwe::GraphicsEngine::createIrrAnimatedMeshSceneNode(std::string meshName)
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
}

/////////////////////////////////////
ScenaryElement* dwe::GraphicsEngine::createWall(std::string meshName)
{
    scene::IAnimatedMeshSceneNode* irrnode = createIrrAnimatedMeshSceneNode(meshName);

    ScenaryElement* s = new ScenaryElement();
    s->setNode(new Node(irrnode));
    return s;
}


////////////////////////////////
dwe::Node* dwe::GraphicsEngine::createNode(std::string meshName)
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

	Node* node = new Node(irrnode);

	return node;
}

vector3df dwe::GraphicsEngine::getTransformedBoundingBox(scene::IAnimatedMeshSceneNode* player){
    return(player->getTransformedBoundingBox().getExtent());
}


/////////////////////////////
Player* dwe::GraphicsEngine::createMainPlayer()
{
	scene::IAnimatedMesh* mesh = m_smgr->getMesh("media/sydney.md2");
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
		irrnode->setMaterialTexture( 0, m_driver->getTexture("media/sydney.bmp") );
	}

	irrnode->setPosition(vector3df(0,24,10));



	// TODO ¿esto es para quitar????
	vector3df extent= irrnode->getTransformedBoundingBox().getExtent();
    //now extent.X is the X size of the box, .Y is Y etc.
    cout << "SIZE: X = " << extent.X << " ... Y = " << extent.Y << " ... Z = " << extent.Z << endl;

    vector3df pos= irrnode->getPosition();
    cout << "POS: X = " << pos.X << " ... Y = " << pos.Y << " ... Z = " << pos.Z << endl;

    //createDynPhyEntity(m_world,vector2d<s32>(0,0), m_device);
    // TODO .................... hasta aqui



	Player* p = new Player();
	p->setNode(new Node(irrnode));
	NetInstance->addNetObject(p);
    return p;
}



/////////////////////////////////
PlayerMate* dwe::GraphicsEngine::createPlayerMate()
{
	scene::IAnimatedMesh* mesh = m_smgr->getMesh("media/playermate.md2");
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
		irrnode->setMaterialTexture( 0, m_driver->getTexture("media/playermate.bmp") );
	}

	PlayerMate* p = new PlayerMate();
	p->setNode(new Node(irrnode));
	NetInstance->addNetObject(p);
    return p;
}

////////////////////////////
Humanoid* dwe::GraphicsEngine::createEnemyHumanoid()
{
    scene::IAnimatedMesh* mesh = m_smgr->getMesh("media/faerie.md2");
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
    return p;
}

////////////////////////////
Dog* dwe::GraphicsEngine::createEnemyDog()
{
    scene::IAnimatedMesh* mesh = m_smgr->getMesh("media/dog.obj");
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
		irrnode->setMaterialTexture( 0, m_driver->getTexture("media/dogC1.jpg") );
		irrnode->setMaterialTexture( 1, m_driver->getTexture("media/dogEyeC1.jpg") );

	}

	Dog* p = new Dog();
	p->setIAnimNode(irrnode);
	p->setNode(new Node(irrnode));
	NetInstance->addNetEnemy(p);
    return p;
}

void dwe::GraphicsEngine::changeEnemyDogTexture(Dog* dog,const io::path& text)
{

    //text = "media/" + text;
    //cout << text << endl;

    scene::IAnimatedMeshSceneNode* irrnode = dog->getIAnimNode();
    if (irrnode)
	{
		irrnode->setMaterialTexture( 0, m_driver->getTexture(text) );

		irrnode->setMaterialTexture( 1, m_driver->getTexture(text) );

	}

}

Door* dwe::GraphicsEngine::createDoor(int f, bool a, float px, float py, float pz)
{
    scene::IAnimatedMeshSceneNode* irrnode = createIrrAnimatedMeshSceneNode("media/puerta");
    Door* d = new Door(f, a);
	d->setNode(new Node(irrnode));
    d->setPosition(dwe::vec3f(px, py, pz)); // Cerrada
	//d->setPosition(dwe::vec3f(43.5-70, 36.3, 135.9)); // Abierta
	d->setPositionClosed(dwe::vec3f(px, py, pz)); // Localización de la puerta CERRADA
	d->setPositionOpened(dwe::vec3f(px, py, pz));
	if(f==1 || f==3)
        d->setRotation(90);

    NetInstance->addNetEntity(d);
    return d;
}

Projectile* dwe::GraphicsEngine::createProjectile(vec3f origin, float angle)
{
    scene::IAnimatedMeshSceneNode* irrnode = createIrrAnimatedMeshSceneNode("media/proyectil");

    Projectile* p = new Projectile(origin, angle);
    p->setNode(new Node(irrnode));
    p->setPosition(origin);
    return p;
}

Generator* dwe::GraphicsEngine::createGenerator(int i, bool b, float px, float py, float pz)
{
    scene::IAnimatedMeshSceneNode* irrnode = createIrrAnimatedMeshSceneNode("media/generador");

    Generator* g = new Generator(i, b);
    g->setNode(new Node(irrnode));
    g->setPosition(dwe::vec3f(px, py, pz));

    NetInstance->addNetEntity(g);
    return g;
}

MagnetKey* dwe::GraphicsEngine::createMagnetKey(int i, float px, float py, float pz)
{
    scene::IAnimatedMeshSceneNode* irrnode = createIrrAnimatedMeshSceneNode("media/llave");

    MagnetKey* m = new  MagnetKey(i);
    m->setNode(new Node(irrnode));
    m->setPosition(dwe::vec3f(px, py, pz));
    return m;
}

SpeedBoost* dwe::GraphicsEngine::createSpeedBoost(float px, float py, float pz)
{
    scene::IAnimatedMeshSceneNode* irrnode = createIrrAnimatedMeshSceneNode("media/speed/speed");
    SpeedBoost* s = new SpeedBoost();
    s->setNode(new Node(irrnode));
    s->setPosition(dwe::vec3f(px, py, pz));

    NetInstance->addNetConsumable(s);
    return s;
}

Medkit* dwe::GraphicsEngine::createMedkit(float px, float py, float pz)
{
    scene::IAnimatedMeshSceneNode* irrnode = createIrrAnimatedMeshSceneNode("media/speed/speed");
    //scene::IAnimatedMeshSceneNode* irrnode = createIrrAnimatedMeshSceneNode("media/medkit/medkit");



    Medkit* h = new Medkit();
    h->setNode(new Node(irrnode));
    h->setPosition(dwe::vec3f(px, py, pz));

    NetInstance->addNetConsumable(h);
    return h;
}

Trigger* dwe::GraphicsEngine::createTrigger(int type, float px, float py, float pz)
{
    Trigger *t;
    scene::IAnimatedMeshSceneNode* irrnode;

    if(type==0)
    {
        irrnode = createIrrAnimatedMeshSceneNode("media/triggerDoor");
        t = new TriggerDoor();
    }
    else if(type==1)
    {
        irrnode = createIrrAnimatedMeshSceneNode("media/triggerGenerator");
        t = new TriggerGenerator();
    }

    t->setNode(new Node(irrnode));
    t->setPosition(dwe::vec3f(px, py, pz));
    return t;
}

//////////////////////////
bool dwe::GraphicsEngine::isWindowActive()
{
    return m_device->isWindowActive();
}

//////////////////////////
void dwe::GraphicsEngine::yield()
{
    m_device->yield();
}

//////////////////////////
void dwe::GraphicsEngine::close()
{
    m_device->closeDevice();
}

//////////////////////////
void dwe::GraphicsEngine::updateCamera(const dwe::vec3f playerPosition)
{
    //update camera target
    //Desencuadre horizontal
    if(GEInstance->receiver.getCursorX()<50){
        if(tarLR > -_camera_desviation)
            tarLR -= _camera_progression;
    }else if(GEInstance->receiver.getCursorX()>750){
        if(tarLR<_camera_desviation)
            tarLR+=_camera_progression;
    }else{
        //Volver a centrar
        if(tarLR!=0)
            if(tarLR<0)
                tarLR+=_camera_progression;
            else
                tarLR-=_camera_progression;
        else
            tarLR = 0;
    }

    //Desencuadre vertical
    if(GEInstance->receiver.getCursorY()<50){
        if(tarUD<_camera_desviation)
            tarUD+=_camera_progression;
    }else if(GEInstance->receiver.getCursorY()>550){
        if(tarUD>-_camera_desviation)
            tarUD-=_camera_progression;
    }else{
        //Volver a centrar
        if(tarUD!=0)
            if(tarUD<0)
                tarUD+=_camera_progression;
            else
                tarUD-=_camera_progression;
        else
            tarUD = 0;
    }

    m_smgr->getActiveCamera()->setTarget(vector3df(playerPosition.x+tarLR, playerPosition.y, playerPosition.z+tarUD));
    m_smgr->getActiveCamera()->setPosition(vector3df(playerPosition.x+tarLR, _camera_y, playerPosition.z + _camera_z_offset + tarUD));
}

irr::scene::ISceneManager*  dwe::GraphicsEngine::getSMGR(){return(m_smgr);}

