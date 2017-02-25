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
#include "tag/TAGEngine.h"


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
    m_tagEngine.init();
}

//////////////////////////
void dwe::GraphicsEngine::release()
{
}

//////////////////////////
bool dwe::GraphicsEngine::isRunning()
{
    return m_tagEngine.isRunning();
}

//////////////////////////
void dwe::GraphicsEngine::draw()
{
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
{
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
    }
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
    // TODO: createNode, no se para que se utiliza
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
void dwe::GraphicsEngine::updateCamera(const dwe::vec3f playerPosition)
{
    // TODO: updateCamera
/*    //update camera target
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
    m_smgr->getActiveCamera()->setPosition(vector3df(playerPosition.x+tarLR, _camera_y, playerPosition.z + _camera_z_offset + tarUD));*/
}


/////////////////////////////
Player* dwe::GraphicsEngine::createMainPlayer()
{
    const aiScene* scene =  m_importer.ReadFile("media/newcube.obj",
                                aiProcess_Triangulate            |
                                aiProcess_JoinIdenticalVertices  |
                                0
                            );
    if(!scene)
    {
        char msg[255];
        sprintf(msg, "Error cargando MainPlayer: %s", m_importer.GetErrorString());
        throw std::runtime_error(msg);
    }

    Node* node = new Node(scene);
    node->setColor(1.0, 0.5, 0.5, 1.0);
    m_scenes.push_back(node);

	Player* p = new Player();
	p->setNode(node);
	p->setPosition(dwe::vec3f(0,0,0));

    return p;
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
}
