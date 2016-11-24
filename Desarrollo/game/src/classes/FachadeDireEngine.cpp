#include "FachadeDireEngine.h"
#include "Mono.h"

// Necesita volver a poner este namespace
// para que codeblocks autocomplete bien.
// Los demás no, sino tampoco autocompleta.




///////////////////////////////////////////////
// class Node
///////////////////////////////////////////////
fde::Node::Node() {};
fde::Node::Node(ISceneNode* n)
{
    m_node = n;
}

void fde::Node::setNode(ISceneNode* n)
{
    m_node = n;
}

void fde::Node::move(vec3f v)
{
    irr::core::vector3df _v = m_node->getPosition();
    _v.X += v.x;
    _v.Y += v.y;
    _v.Z += v.z;
    m_node->setPosition(_v);
}

fde::vec3f fde::Node::getPosition()
{
    irr::core::vector3df _v = m_node->getPosition();
    vec3f v;

    v.x = _v.X;
    v.y = _v.Y;
    v.z = _v.Z;

    return v;
}

void fde::Node::setPosicion(vec3f v)
{
    irr::core::vector3df _v = m_node->getPosition();
    _v.X = v.x;
    _v.Y = v.y;
    _v.Z = v.z;
    m_node->setPosition(_v);
}




///////////////////////////////////////////////
// class Graphics
///////////////////////////////////////////////
////////////////////
void fde::Graphics::init(AppReceiver* ar)
{
	m_device = createDevice( video::EDT_OPENGL, irr::core::dimension2d<u32>(640, 480), 16,
			false, false, false, ar);

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
	m_smgr->addCameraSceneNode(0, vector3df(-10,20,5), vector3df(0,0,0));
}

////////////////////
void fde::Graphics::release()
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

////////////////////
bool fde::Graphics::isRunning()
{
  	/*
	Ok, now we have set up the scene, lets draw everything: We run the
	device in a while() loop, until the device does not want to run any
	more. This would be when the user closes the window or presses ALT+F4
	(or whatever keycode closes a window).
	*/

    return m_device->run();
}

////////////////////
void fde::Graphics::draw()
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
}

//////////////////////////
fde::Node* fde::Graphics::createNode(std::string meshName)
{
	scene::IMesh* mesh = m_smgr->getMesh((meshName+".obj").c_str());
	if (!mesh)
	{
		m_device->drop();
		exit(0);
	}
	scene::IMeshSceneNode* irrnode = m_smgr->addMeshSceneNode( mesh );
	if (irrnode)
	{
		irrnode->setMaterialFlag(EMF_LIGHTING, false);  // Desactivamos iluminacion, solo para pruebas
		irrnode->setMaterialTexture( 0, m_driver->getTexture((meshName+".png").c_str()) );
	}

	Node* node = new Node(irrnode);

	return node;
}

//////////////////////////
Mono* fde::Graphics::createMono(std::string meshName)
{
	scene::IMesh* mesh = m_smgr->getMesh((meshName+".obj").c_str());
	if (!mesh)
	{
		m_device->drop();
		exit(0);
	}
	scene::IMeshSceneNode* irrnode = m_smgr->addMeshSceneNode( mesh );
	if (irrnode)
	{
		irrnode->setMaterialFlag(EMF_LIGHTING, false);  // Desactivamos iluminacion, solo para pruebas
		irrnode->setMaterialTexture( 0, m_driver->getTexture((meshName+".png").c_str()) );
	}

	Mono* mono = new Mono();
	mono->setNode(irrnode);

	return mono;
}


////////////////////
bool fde::Graphics::isWindowActive()
{
    return m_device->isWindowActive();
}

////////////////////
void fde::Graphics::yield()
{
    m_device->yield();
}

////////////////////
void fde::Graphics::close()
{
    m_device->closeDevice();
}
