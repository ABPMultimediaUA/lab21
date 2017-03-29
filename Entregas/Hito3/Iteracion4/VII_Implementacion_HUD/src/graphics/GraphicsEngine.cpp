#define GLEW_STATIC
#include<GL/glew.h>
#include <glm/glm.hpp>

#include "GraphicsEngine.h"

#include <sstream>
#include <iostream>
#include <vector>

#include "AppReceiver.h"
#include "Scene.h"
#include "Shader.h"
#include "Program.h"

#include "Player.h"

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

    m_tagEngine.init();

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
        // TODO faltan eventos de teclado
        /*else if (event.type == sf::Event::Resized)
        {
            glViewport(0, 0, event.size.width, event.size.height);
        }
        else
            receiver.OnEvent(event);*/
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

/*******/
void dwe::GraphicsEngine::drawRectangleShape(sf::RectangleShape rs)
{
    m_window->draw(rs);
}

void dwe::GraphicsEngine::drawText(sf::Text t)
{
    m_window->draw(t);
}

void dwe::GraphicsEngine::drawSprite(sf::Sprite s)
{
    m_window->draw(s);
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
    tag::GraphicNode* cube01 = m_tagEngine.createMesh("media/newcube.obj", vec3f(-2,0,0), vec3f(2,45,1));
    tag::GraphicNode* cube02 = m_tagEngine.createMesh("media/newcube.obj", vec3f( 2,0,0), vec3f(0,20,0));
    tag::GraphicNode* cube03 = m_tagEngine.createMesh("media/newcube.obj", vec3f( 0,-2.2,0), vec3f(0,0,0), cube02);

    tag::GraphicNode* camera = m_tagEngine.createPerspectiveCamera(vec3f(2,0,-9.0), vec3f(0,0,0), 45.0f, tag::TAGEngine::screenWidth / tag::TAGEngine::screenHeight, 0.1f, 1000.0f);

    tag::GraphicNode* light  = m_tagEngine.createLight(vec3f(-100,100,50), vec3f(0,0,0));

    return 0;
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

/*************Fachada SFML*******************/
dwe::Button::Button(std::string t, int x, int y)
{
    /*// Inicializacion de fondo para el boton. Si se utiliza, cuadrar Size y Position
    texture.loadFromFile("media/buttonBackground.png");
    background.setTexture(&texture, true);
    background.setSize(sf::Vector2f(100, 25));//   setSize(100, 25);
    background.setPosition(SCREEN_WIDTH/2-x, SCREEN_HEIGHT/2-y);
    */

    font.loadFromFile("media/8bit.ttf"); // La fuente se puede modificar en cualquier momento
    text.setFont(font);
    text.setString(t);
    text.setCharacterSize(18);
    text.setColor(sf::Color::White);
    text.setPosition(x, y); // 200, 150
}

dwe::Button::~Button(){};

void dwe::Button::draw()
{
    //GEInstance->drawRectangleShape(background);
    GEInstance->drawText(text);
}

dwe::Background::Background(std::string s)
{
    rs.setSize(sf::Vector2f(SCREEN_WIDTH,SCREEN_HEIGHT));
    texture.loadFromFile("media/menu"+s+".jpg");
    rs.setTexture(&texture, true);
}

dwe::Background::~Background(){};

void dwe::Background::draw()
{
    GEInstance->drawRectangleShape(rs);
}

void dwe::HudBox::setComponents(std::string str, sf::Sprite *s, sf::Texture *t, float px, float py)
{
    t->loadFromFile(str);
    s->setTexture(*t, true);

    s->setOrigin(0,0);
    s->setPosition(px, py);
}


dwe::WeaponBox::WeaponBox( float x, float y)
{
    t = 2000;
    grenades = 2;
    ammoGun = 20;
    ammoRifle = 10;
    ammoShotgun = 10;

    /**** Caja base ****/
    setComponents("media/CuadroArma.png", &s_box, &t_box, x, y);

    /**** Arma ****/
    setComponents("media/grenade.png", &s_weapon, &t_weapon, s_box.getPosition().x, s_box.getPosition().y );

    /**** Munición del arma actual ****/
    font.loadFromFile("media/exoregular.otf");
    text_ammo.setFont(font);
    text_ammo.setCharacterSize(15);
    text_ammo.setColor(sf::Color::White);
    text_ammo.setPosition(s_box.getPosition().x + SCREEN_WIDTH/9, SCREEN_HEIGHT*7.3/8);

    std::stringstream sw;
    sw << "x" << grenades;
    text_ammo.setString(sw.str());

}

dwe::WeaponBox::~WeaponBox(){};

void dwe::WeaponBox::draw()
{
    GEInstance->drawSprite(s_box);

    swapWeapon(&t_weapon, &text_ammo);

    GEInstance->drawSprite(s_weapon);

    GEInstance->drawText(text_ammo);
}

void dwe::WeaponBox::swapWeapon(sf::Texture *tweapon, sf::Text *textammo)
{

    // Según el arma que haya en el momento, cambiamos la imagen y la cantidad disponible
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num1) && (clock() - t)> 200)
        updateWeapon(tweapon, "media/grenade.png", &grenades, textammo);


    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num2) && (clock() - t)> 200)
        updateWeapon(tweapon, "media/cosa2.png", &ammoGun, textammo);


    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num3) && (clock() - t)> 200)
        updateWeapon(tweapon, "media/cosa3.png", &ammoRifle, textammo);


    // Ponmos textura, posicion, etc del arma
    s_weapon.setTexture(*tweapon, true);
    s_weapon.setOrigin(0,0);
    s_weapon.setPosition(s_box.getPosition().x, s_box.getPosition().y + 2);

}

void dwe::WeaponBox::updateWeapon (sf::Texture *tweapon, std::string str, int *ammo, sf::Text *textammo)
{
    std::stringstream sw;
    tweapon->loadFromFile(str);
    sw << "x" << *ammo;
    textammo->setString(sw.str());
}

dwe::HealthBox::HealthBox(float x, float y)
{
    max_health = 100;
    health = max_health;
    heals = 10;

    t = 2000;

    /**** Texto de Vida actual / Vida total ****/
    font.loadFromFile("media/exoregular.otf");
    text_health.setFont(font);
    text_health.setCharacterSize(15);
    text_health.setColor(sf::Color::White);
    text_health.setPosition(SCREEN_WIDTH - SCREEN_WIDTH/4.25, SCREEN_HEIGHT*6.8/8);

    /**** Texto de Botiquines ****/
    text_heal.setFont(font);
    text_heal.setCharacterSize(15);
    text_heal.setColor(sf::Color::White);
    text_heal.setPosition(SCREEN_WIDTH - SCREEN_WIDTH/7, SCREEN_HEIGHT*7.2/8);

    /**** Caja base ****/
    setComponents("media/CuadroVida.png", &s_box, &t_box, x, y);

    /**** Vida perdida ****/
    setComponents("media/VidaPerdida.png", &s_hplost, &t_hplost, s_box.getPosition().x + 6, s_box.getPosition().y + 6);

    /**** Vida actual ****/
    t_health.loadFromFile("media/VidaLlena.png");
    s_health.setTexture(&t_health, true);
    s_health.setOrigin(0,0);
    s_health.setPosition(s_box.getPosition().x + 7, s_box.getPosition().y + 6);

    /**** Contorno vida ****/
    setComponents("media/ContornoVida.png", &s_edge, &t_edge, s_box.getPosition().x + 6, s_box.getPosition().y + 6);

    /**** Botiquines ****/
    setComponents("media/Botiquines.png", &s_heal, &t_heal, s_box.getPosition().x + 110, s_box.getPosition().y + 33);

}

dwe::HealthBox::~HealthBox() {}

void dwe::HealthBox::draw()
{
    // Perder vida
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && (clock() - t)> 200 && health > 0)
    {
        health -= 10;
        t = clock();
    }
    // Ganar vida
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && (clock() - t)> 200 && health < 100)
    {
        health += 10;
        t = clock();
    }

    // Coger botiquin
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D) && (clock() - t)> 200 && heals > 0)
    {
        heals -= 1;
        t = clock();
    }
    // Usar botiquín
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::F) && (clock() - t)> 200 && heals < 20)
    {
        heals += 1;
        t = clock();
    }

    /////////////////////

    GEInstance->drawSprite(s_box);

    GEInstance->drawSprite(s_hplost);

    drawCurrentHealth();

    GEInstance->drawSprite(s_edge);

    GEInstance->drawSprite(s_heal);

    drawNumberOfHeals();
}


void dwe::HealthBox::drawCurrentHealth()
{

    float hpn = health;
    float hpmn = max_health;

    // Actualizamos sprite de vida
    float c = ((hpn/hpmn) * 100 *1.8) ;
    s_health.setSize(sf::Vector2f(c , 22));
    sf::Rect<int> rect = s_health.getTextureRect();
    rect.width = c;
    s_health.setTextureRect(rect);

    // Actualizamos texto Vida Actual / Vida Total
    std::stringstream ss;
    ss << hpn<<"/"<<hpmn << " HP";
    text_health.setString(ss.str());

    // Dibujamos
    GEInstance->drawRectangleShape(s_health);
    GEInstance->drawText(text_health);
}

void dwe::HealthBox::drawNumberOfHeals()
{
    std::stringstream sh;
    sh << "x" << heals;
    text_heal.setString(sh.str());

    GEInstance->drawText(text_heal);
}
