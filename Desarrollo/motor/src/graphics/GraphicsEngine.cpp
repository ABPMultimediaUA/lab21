#include "GraphicsEngine.h"

#include <iostream>

#include "AppReceiver.h"



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

