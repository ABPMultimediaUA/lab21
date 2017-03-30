#define GLEW_STATIC
#include<GL/glew.h>
#include <glm/glm.hpp>

#include "GraphicsEngine.h"


#include <iostream>
#include <vector>

#include "AppReceiver.h"
#include "Scene.h"
#include "Shader.h"
#include "Program.h"

#include "Player.h"
#include "Gun.h"

using namespace std;
// Necesita volver a poner este namespace
// para que codeblocks autocomplete bien.
// Los demás no, si no tampoco autocompleta.


float view_rotate_default[16] = { 1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1 };
float view_position_default[3] = { 0.0, 0.0, -9.0 };


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
    m_window->setVerticalSyncEnabled(true);

    // Creamos los mensajes de texto, por ahora vacios
    if (!m_font.loadFromFile("media/ExoRegular.otf"))
        throw std::runtime_error("No se ha podido cargar la fuente de texto");

	for(int i=0; i<MAX_MESSAGE_LINES; i++)
	{
        m_messageLine[i].setFont(m_font);
        m_messageLine[i].setCharacterSize(14);
        m_messageLine[i].setFillColor(sf::Color(255, 255, 255, 255));
        m_messageLine[i].setPosition(10.f, GraphicsEngine::_screenHeight - (i+1)*16.f);
        m_messageLine[i].setString("asdf");
	}

    m_tagEngine.init(GraphicsEngine::_screenHeight, GraphicsEngine::_screenWidth);

    m_secondsLastDraw = 0;
    m_clock.restart();
    m_window->pushGLStates();
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
    m_window->popGLStates();   // Antes de este pop hay un push, en init
    m_tagEngine.draw();
    m_window->pushGLStates();

    // Lineas de mensaje del jugador
    for(unsigned int i=0; i<MAX_MESSAGE_LINES; i++)
        m_window->draw(m_messageLine[i]);





    m_window->display();

    char tmp[25];
    float fps = 1.f / (m_clock.getElapsedTime().asSeconds() - m_secondsLastDraw);
    m_secondsLastDraw = m_clock.getElapsedTime().asSeconds();
    sprintf(tmp, "Lab21 - fps:%f", fps);
    m_window->setTitle(tmp);


/*    m_window->setActive(true);
    glm::mat4 rotateMatrix;

    glClearColor(0.0, 0.7, 0.9, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Cálculo de la vista (cámara)
    m_viewMatrix = glm::mat4(1.0f);
    rotateMatrix = glm::make_mat4(m_view_rotate);
    m_viewMatrix = glm::translate(m_viewMatrix,glm::vec3(m_view_position[0], m_view_position[1], m_view_position[2]));
    m_viewMatrix = m_viewMatrix * rotateMatrix;
    m_viewMatrix = glm::scale(m_viewMatrix, glm::vec3(m_scale, m_scale, m_scale));

    // Habilitamos el paso de attributes
    glEnableVertexAttribArray(m_aPositionLocation);
    glEnableVertexAttribArray(m_aNormalLocation);
    glUseProgram(m_shaderProgram->ReturnProgramID());

    glUniform1i(m_uLuz0Location, true);
    glUniformMatrix4fv(m_uVMatrixLocation, 1, GL_FALSE, glm::value_ptr(m_viewMatrix)); // Para la luz matrix view pero sin escalado!

    // Dibujar
    render();

    glDisableVertexAttribArray(m_aPositionLocation);
    glDisableVertexAttribArray(m_aNormalLocation);
    glUseProgram(0);

    m_window->setActive(false);

    m_window->pushGLStates();
    for(unsigned int i=0; i<MAX_MESSAGE_LINES; i++)
        m_window->draw(m_messageLine[i]);
    m_window->popGLStates();

    m_window->display();

    char tmp[25];
    float fps = 1.f / (m_clock.getElapsedTime().asSeconds() - m_secondsLastDraw);
    m_secondsLastDraw = m_clock.getElapsedTime().asSeconds();
    sprintf(tmp, "Lab21 - fps:%f", fps);
    m_window->setTitle(tmp);*/
}

//////////////////////////
void dwe::GraphicsEngine::render()
{/*
    glm::mat4   modelMatrix;
    glm::mat4   modelViewMatrix;

    std::list<Node*>::iterator iter = m_scenes.begin();
    while (iter != m_scenes.end())
    {
        const aiScene* scene = (*iter)->getNode();
        vec3f position = (*iter)->getPosition();
        vec3f rotation = (*iter)->getRotation();

        // Cálculo de la ModelView
        modelMatrix     = glm::mat4(1.0f); // matriz identidad
        modelMatrix     = glm::translate(modelMatrix, glm::vec3(position.x, position.y, position.z));

        modelMatrix     = glm::rotate(modelMatrix, rotation.x, glm::vec3(1,0,0));
        modelMatrix     = glm::rotate(modelMatrix, rotation.y, glm::vec3(0,1,0));
        modelMatrix     = glm::rotate(modelMatrix, rotation.z, glm::vec3(0,0,1));
        modelViewMatrix = m_viewMatrix * modelMatrix;

        // Envía nuestra ModelView al Vertex Shader
        glUniformMatrix4fv(m_uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);

        // Pintar
        glUniform4fv(m_uColorLocation, 1, (*iter)->getColor());

        // Asociamos los vértices y sus normales
        glVertexAttribPointer(m_aPositionLocation, 3, GL_FLOAT, false, sizeof(float)*3, scene->mMeshes[0]->mVertices);
        glVertexAttribPointer(m_aNormalLocation, 3, GL_FLOAT, false, sizeof(float)*3, scene->mMeshes[0]->mNormals);

        for(unsigned int t=0; t<scene->mMeshes[0]->mNumFaces; t++)
        {
            glDrawElements(GL_POLYGON, scene->mMeshes[0]->mFaces[t].mNumIndices, GL_UNSIGNED_INT, scene->mMeshes[0]->mFaces[t].mIndices);
        }

        iter++;
    }*/
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

////////////////////////////////
dwe::Node* dwe::GraphicsEngine::createNode(std::string meshName)
{
    tag::GraphicNode* gn = m_tagEngine.createMesh(meshName+".obj", vec3f(0,0,0), vec3f(0,0,0));
    Node* node = new Node(gn);
    return node;
/*	scene::IAnimatedMesh* mesh = m_smgr->getMesh((meshName+".obj").c_str());
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

	return node;*/
	return 0;
}

/*vector3df dwe::GraphicsEngine::getTransformedBoundingBox(scene::IAnimatedMeshSceneNode* player){
    return(player->getTransformedBoundingBox().getExtent());
}*/

Gun* dwe::GraphicsEngine::createGun(float px, float py, float pz)
{
	tag::GraphicNode* node = m_tagEngine.createMesh("media/ammm/Gun.obj", vec3f(0,0,0), vec3f(0,0,0));
    Gun* g = new Gun();
	g->setNode(new Node(node));
	g->setPosition(dwe::vec3f(px, py, pz));

	return g;

    /*scene::IAnimatedMeshSceneNode* irrnode = createIrrAnimatedMeshSceneNode("media/ammm/Gun"); // centrado
    //scene::IAnimatedMeshSceneNode* irrnode = createIrrAnimatedMeshSceneNode("media/Gun/Gun");

    Gun* g = new Gun();
    g->setNode(new Node(irrnode));
    g->setPosition(dwe::vec3f(px, py, pz));

    return g;*/
}

//////////////////////////
void dwe::GraphicsEngine::yield()
{
    // TODO: yield
    //m_device->yield();
}

//////////////////////////
void dwe::GraphicsEngine::close()
{
    // TODO: close
    //m_device->closeDevice();
}

//////////////////////////
void dwe::GraphicsEngine::createCamera()
{
    vec3f position(2,0,60);
    m_camera = m_tagEngine.createPerspectiveCamera(position, vec3f(0,0,0), 45.0f, get_screenWidth() / get_screenHeight(), 0.1f, 1000.0f);
    m_tagEngine.nodeLookAtTarget(m_camera, position, vec3f(0,0,0));
    m_tagEngine.createLight(vec3f(-10,0,-80), vec3f(0,0,0));
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
        if(tarUD < _camera_desviation)        tarUD+=_camera_progression;
    }else if(cursorY > borderD){
        if(tarUD > -_camera_desviation)       tarUD-=_camera_progression;
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
            vec3f(playerPosition.x+tarLR + zoomX, _camera_y + abs(zoomX) + abs(zoomZ), (-1)*(playerPosition.z + _camera_z_offset + tarUD)),
            vec3f(playerPosition.x+ tarLR + zoomX, playerPosition.y, (-1)*(playerPosition.z+tarUD + zoomZ)));
    //TODOfachada quitar: m_smgr->getActiveCamera()->setTarget(vector3df(playerPosition.x+ tarLR + zoomX, playerPosition.y, playerPosition.z+tarUD + zoomZ));
    //TODOfachada quitar: m_smgr->getActiveCamera()->setPosition(vector3df(playerPosition.x+tarLR + zoomX, _camera_y + abs(zoomX) + abs(zoomZ), playerPosition.z + _camera_z_offset + tarUD));
}



/////////////////////////////
Player* dwe::GraphicsEngine::createMainPlayer(Gun* gun)
{
	tag::GraphicNode* node = m_tagEngine.createMesh("media/sydney.md2", vec3f(0,0,0), vec3f(0,0,0));
	Player* p = new Player(gun);
	p->setNode(new Node(node));

	//NetInstance->addNetObject(p);
	return p;
   /* tag::GraphicNode* camera = m_tagEngine.createPerspectiveCamera(vec3f(0,0,9), vec3f(0,0,0), 45.0f, tag::TAGEngine::screenWidth / tag::TAGEngine::screenHeight, 0.1f, 1000.0f);

    tag::GraphicNode* light  = m_tagEngine.createLight(vec3f(-100,100,50), vec3f(0,0,0));


    vec3f v(0,0,0);

    m_tagEngine.nodeLookAtTarget(camera, vec3f(0,0,100), v);






    cube01 = m_tagEngine.createMesh("media/faerie.md2", vec3f(0,0,0), vec3f(0,0,0));


    Player* p = new Player();
    p->setNode(new Node(cube01));
    return p;*/
/*

    tag::GraphicNode* cube02 = m_tagEngine.createMesh("media/newcube.obj", vec3f( 2,0,0), vec3f(0,20,0));
    tag::GraphicNode* cube03 = m_tagEngine.createMesh("media/newcube.obj", vec3f( 0,-2.2,0), vec3f(0,20,0), cube02);

    tag::GraphicNode* camera = m_tagEngine.createPerspectiveCamera(vec3f(0,0,9.0), vec3f(0,0,0), 45.0f, tag::TAGEngine::screenWidth / tag::TAGEngine::screenHeight, 0.1f, 1000.0f);

    tag::GraphicNode* light  = m_tagEngine.createLight(vec3f(-100,100,50), vec3f(0,0,0));

    return 0;*/
/*
    scene::IAnimatedMesh* mesh = m_smgr->getMesh("media/sydney.md2");
	if (!mesh){
		m_device->drop();
		exit(0);
	}
	scene::IAnimatedMeshSceneNode* irrnode = m_smgr->addAnimatedMeshSceneNode( mesh );
	if (irrnode){
		irrnode->setMaterialFlag(EMF_LIGHTING, false);  // Desactivamos iluminacion, solo para pruebas
		irrnode->setMD2Animation(scene::EMAT_STAND);
		irrnode->setMaterialTexture( 0, m_driver->getTexture("media/sydney.bmp") );
	}

	irrnode->setPosition(vector3df(0,24,10));

	Player* p = new Player(gun);
	p->setNode(new Node(irrnode));
	NetInstance->addNetObject(p);
    return p;*/
}


//////////////////////////
void dwe::GraphicsEngine::addMessageLine(std::string text)
{
    for(int i=MAX_MESSAGE_LINES-1; i>0; i--)
        m_messageLine[i].setString(m_messageLine[i-1].getString());
    m_messageLine[0].setString(text);
}

////////////////////////////////
dwe::vec2f dwe::GraphicsEngine::getMousePosition()
{
/*    float x =  sf::Mouse::getPosition(*m_window).x;
    float y = -sf::Mouse::getPosition(*m_window).y;

    return vec2f(x,y);*/
    return vec2f(0,0);
}


//////////////////////////
void dwe::GraphicsEngine::update()
{
  //  m_tagEngine.moveNodeEntity(cube01, vec3f(0.001,0,0));
  //  m_tagEngine.rotateNodeEntity(cube01, vec3f(0,0.1,0));
  //m_tagEngine.setPositionNodeEntity(cube01, vec3f(0,0,0));
  //m_tagEngine.setRotationNodeEntity(cube01, vec3f(0,0,0));
}

