#define GLEW_STATIC
#include<GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "GraphicsEngine.h"

#include <iostream>
#include <vector>

#include "AppReceiver.h"
#include "Scene.h"
#include "Shader.h"
#include "Program.h"

#include "Player.h"
//#include <SFML/String.hpp>


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

    m_window = new sf::RenderWindow(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Lab21", sf::Style::Default, contextSettings);

    // Habilita el z_buffer
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    // Inicialización de GLEW
    if(glewInit() != GLEW_OK)
        throw std::runtime_error("glewInit failed");

    // print out some info about the graphics drivers
    //std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
    //std::cout << "GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
    //std::cout << "Vendedor: " << glGetString(GL_VENDOR) << std::endl;
    //std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;

    m_scale = 1.0;
    memcpy(m_view_position, view_position_default, 3*sizeof(float));
    memcpy(m_view_rotate, view_rotate_default, 16*sizeof(float));


    // Carga de los Shaders
    Shader shader;
    std::vector<GLuint> shaders;
    shaders.push_back(shader.LoadShader("shaders/VertexShader.glsl", GL_VERTEX_SHADER));
    shaders.push_back(shader.LoadShader("shaders/FragmentShader.glsl", GL_FRAGMENT_SHADER));

    m_shaderProgram = new Program(shaders);
    glUseProgram(m_shaderProgram->ReturnProgramID());

    // Attributes
    m_aPositionLocation = m_shaderProgram->attrib(A_POSITION);
    m_aNormalLocation   = m_shaderProgram->attrib(A_NORMAL);

    // Uniforms
    m_uProjectionMatrixLocation   = m_shaderProgram->uniform(U_PROJECTIONMATRIX);
    m_uMVMatrixLocation           = m_shaderProgram->uniform(U_MVMATRIX);
    m_uVMatrixLocation            = m_shaderProgram->uniform(U_VMATRIX);
    m_uColorLocation              = m_shaderProgram->uniform(U_COLOR);
    m_uLuz0Location               = m_shaderProgram->uniform(U_LUZ0);


    // Estableciendo la matriz de proyección perspectiva
    glm::mat4 m_projectionMatrix = glm::perspective(45.0f, (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 1000.0f);
    glUniformMatrix4fv(m_uProjectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(m_projectionMatrix));

    m_scenes.clear();

    // Creamos los mensajes de texto, por ahora vacios
    if (!m_font.loadFromFile("media/ExoRegular.otf"))
        throw std::runtime_error("No se ha podido cargar la fuente de texto");

	for(int i=0; i<MAX_MESSAGE_LINES; i++)
	{
        m_messageLine[i].setFont(m_font);
        m_messageLine[i].setCharacterSize(14);
        m_messageLine[i].setFillColor(sf::Color(255, 255, 255, 255));
        m_messageLine[i].setPosition(10.f, SCREEN_HEIGHT - (i+1)*16.f);
        m_messageLine[i].setString("");
	}

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

    return m_window->isOpen();
}

//////////////////////////
void dwe::GraphicsEngine::draw()
{
    m_window->setActive(true);
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
    m_window->setTitle(tmp);
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
    float x =  sf::Mouse::getPosition(*m_window).x;
    float y = -sf::Mouse::getPosition(*m_window).y;

    return vec2f(x,y);
}






/////////////////////////////////////////////////
// GraphicNode
/////////////////////////////////////////////////

///////////////////////
bool dwe::GraphicNode::setEntity(dwe::Entity* e) { m_entity = e; return true; }
dwe::Entity* dwe::GraphicNode::getEntity() { return m_entity; }

///////////////////////////////////
dwe::GraphicNode* dwe::GraphicNode::getParent() { return m_parent; }

///////////////////////////////
unsigned int dwe::GraphicNode::addChild(dwe::GraphicNode* n)
{
    m_childs.push_back(n);
    return (m_childs.size() - 1);  // devolvemos el indice añadido
}

///////////////////////////////
unsigned int dwe::GraphicNode::removeChild(dwe::GraphicNode* n)
{
    m_childs.erase(std::remove(m_childs.begin(), m_childs.end(), n), m_childs.end());
    return (m_childs.size()); // Devolvemos cantidad de hijos
}

///////////////////////
void dwe::GraphicNode::draw()
{
    if (m_entity != 0)
        m_entity->beginDraw();

    for(vector<GraphicNode*>::iterator it = m_childs.begin(); it != m_childs.end(); it++)
        (*it)->draw();

    if (m_entity != 0)
        m_entity->endDraw();
}

/////////////////
void dwe::EMesh::loadMesh(char *file)
{
    cout << "Cargando malla " << file << endl;
}

/////////////////
void dwe::EMesh::beginDraw()
{
    std::cout << "Begin " << m_cadena << "\n";
}

/////////////////
void dwe::EMesh::endDraw()
{
    std::cout << "End " << m_cadena << "\n";
}

/////////////////
void dwe::ETransform::identity()
{
    m_matrix = glm::mat4();

}

/////////////////
void dwe::ETransform::load(glm::mat4 m)
{
    m_matrix = m;

}

/////////////////
glm::mat4 dwe::ETransform::getMatrix()
{
    return m_matrix;
}

/////////////////
void dwe::ETransform::transpose()
{
    m_matrix = glm::transpose(m_matrix);
}

/////////////////
void dwe::ETransform::translate(vec3f t)
{
    m_matrix = glm::translate(m_matrix, glm::vec3(t.x, t.y, t.z));
}

/////////////////
void dwe::ETransform::translate(float x, float y, float z)
{
    m_matrix = glm::translate(m_matrix, glm::vec3(x, y, z));
}

/////////////////
void dwe::ETransform::rotate(vec3f t)
{
    dwe::ETransform::rotate(t.x, t.y, t.z);
}

/////////////////
void dwe::ETransform::rotate(float x, float y, float z)
{
    float toRad = M_PI / 180;

    if (x != 0)
    {
        x = x * toRad;
        m_matrix = glm::rotate(m_matrix, x, glm::vec3(1, 0, 0));
    }


    if (y != 0)
    {
        y = y * toRad;
        m_matrix = glm::rotate(m_matrix, y, glm::vec3(0, 1, 0));
    }


    if (z != 0)
    {
        z = z * toRad;
        m_matrix = glm::rotate(m_matrix, z, glm::vec3(0, 0, 1));
    }


}

/////////////////
void dwe::ETransform::scale(vec3f s)
{
    m_matrix = glm::scale(m_matrix, glm::vec3(s.x, s.y, s.z));
}

/////////////////
void dwe::ETransform::scale(float x, float y, float z)
{
    m_matrix = glm::scale(m_matrix, glm::vec3(x, y, z));
}

/////////////////
void dwe::ETransform::beginDraw()
{
    std::cout << "Begin " << m_cadena << "\n";
    std::cout << glm::to_string(this->getMatrix()) << endl;

    glPushMatrix();
    glMultMatrixf((GLfloat*)&m_matrix);


}

/////////////////
void dwe::ETransform::endDraw()
{
    std::cout << "End " << m_cadena << "\n";

    glPopMatrix();
}



