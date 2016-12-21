
/****************************************************************************************

    CarGL (Objects.cpp)

    Grado en Ingeniería Multimedia.
    Práctica de Gráficos por Computador.
    OpenGL con Shaders.
  ---------------------------------------------------------------------------------------

    Noviembre 2012 - Septiembre 2016 (C) Juan Antonio Puchol García (puchol@dccia.ua.es)


*****************************************************************************************/

#include "Objects.h"
#include "load3ds.c"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>


// Variable para inicializar los vectores correpondientes con los valores iniciales
GLfloat light0_ambient_c[4]  = {   0.2f,   0.2f,  0.2f, 1.0f };
GLfloat light0_diffuse_c[4]  = {   0.8f,   0.8f,  0.8f, 1.0f };
GLfloat light0_specular_c[4] = {   1.0f,   1.0f,  1.0f, 1.0f };
GLfloat light0_position_c[4] = {-100.0f, 100.0f, 50.0f, 1.0f };

GLfloat light1_ambient_c[4]  = {   0.2f,   0.2f,  0.2f, 1.0f };
GLfloat light1_diffuse_c[4]  = {   0.8f,   0.8f,  0.8f, 1.0f };
GLfloat light1_specular_c[4] = {   1.0f,   1.0f,  1.0f, 1.0f };
GLfloat light1_position_c[4] = {   0.0f, 100.0f,  0.0f, 1.0f };

GLfloat mat_ambient_c[4]    = { 0.7f, 0.7f, 0.7f, 1.0f };
GLfloat mat_diffuse_c[4]    = { 0.8f, 0.8f, 0.8f, 1.0f };
GLfloat mat_specular_c[4]   = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat mat_shininess_c[1] = { 100.0f };

// Matriz de 4x4 = (I)
float view_rotate_c[16] = { 1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1 };
float view_position_c[3] = { 0.0, -2.0, -9.0 };

float color_cubo[4] = { 1.0, 0.5, 0.5, 1.0 }; // Color del cubo RGBA

//************************************************************** Variables de clase

TEscena escena;

//************************************************************** Clase TPrimitiva

TPrimitiva::TPrimitiva(int DL, int ti)
{
    Assimp::Importer importer;

    ID   = DL;
    tipo = ti;

    sx = sy = sz = 1;
    rx = ry = rz = 0;
	switch (tipo) {
	    case CUBE_ID: {
		    tx = ty = tz = 0;  // Posición origen de coordenadas
		    rx = ry = rz = 0;  // rotacion original
	        memcpy(colores, color_cubo, 4*sizeof(float));   // Colores


	        scene = importer.ReadFile("../../Modelos/newcube.obj",
                aiProcess_Triangulate            |
                aiProcess_JoinIdenticalVertices  |
                0
            );
	        if(!scene)
                std::cout << "NO SCENE ------------------------------------" << importer.GetErrorString() << "\n";


	        break;
	    }
	} // switch
}

void __fastcall TPrimitiva::Render(int seleccion, bool reflejo)
{
    glm::mat4   modelMatrix;
    glm::mat4   modelViewMatrix;
    switch (tipo) {

        case CUBE_ID: {
            // Cálculo de la ModelView
            modelMatrix     = glm::mat4(1.0f); // matriz identidad
            modelMatrix     = glm::translate(modelMatrix,glm::vec3(tx, ty, tz));
            modelMatrix     = glm::rotate(modelMatrix, rx, glm::vec3(1,0,0));
            modelMatrix     = glm::rotate(modelMatrix, ry, glm::vec3(0,1,0));
            modelMatrix     = glm::rotate(modelMatrix, rz, glm::vec3(0,0,1));
            modelViewMatrix = escena.viewMatrix * modelMatrix;

            // Envía nuestra ModelView al Vertex Shader
            glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);

            // Pintar
            glUniform4fv(escena.uColorLocation, 1, colores);

            // Asociamos los vértices y sus normales
            glVertexAttribPointer(escena.aPositionLocation, POSITION_COMPONENT_COUNT, GL_FLOAT, false, sizeof(float)*3, scene->mMeshes[0]->mVertices);
            glVertexAttribPointer(escena.aNormalLocation, NORMAL_COMPONENT_COUNT, GL_FLOAT, false, sizeof(float)*3, scene->mMeshes[0]->mNormals);

            for(int t=0; t<scene->mMeshes[0]->mNumFaces; t++)
                glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, scene->mMeshes[0]->mFaces[t].mIndices);
            break;
        }

    } // switch

}

//************************************************************** Clase TEscena

TEscena::TEscena() {

    seleccion = 1;
    num_objects = 0;

    // live variables usadas por GLUI en TGui
    wireframe = 0;
    z_buffer = 1;
    culling = 0;

    scale = 1.0;
    xy_aspect = 1;
    last_x = 0;
    last_y = 0;

    memcpy(view_position, view_position_c, 3*sizeof(float));
    memcpy(view_rotate, view_rotate_c, 16*sizeof(float));

    memcpy(light0_ambient, light0_ambient_c, 4*sizeof(float));

    memcpy(light0_ambient, light0_ambient_c, 4*sizeof(float));
    memcpy(light0_diffuse, light0_diffuse_c, 4*sizeof(float));
    memcpy(light0_specular, light0_specular_c, 4*sizeof(float));
    memcpy(light0_position, light0_position_c, 4*sizeof(float));

    memcpy(light1_ambient, light1_ambient_c, 4*sizeof(float));
    memcpy(light1_diffuse, light1_diffuse_c, 4*sizeof(float));
    memcpy(light1_specular, light1_specular_c, 4*sizeof(float));
    memcpy(light1_position, light1_position_c, 4*sizeof(float));

    memcpy(mat_ambient, mat_ambient_c, 4*sizeof(float));
    memcpy(mat_diffuse, mat_diffuse_c, 4*sizeof(float));
    memcpy(mat_specular, mat_specular_c, 4*sizeof(float));
    memcpy(mat_shininess, mat_shininess_c, 1*sizeof(float));
}

void __fastcall TEscena::InitGL()
{
    int tx, ty, tw, th;

    // Habilita el z_buffer
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    // Inicialización de GLEW
    std::cout << "Inicializando GLEW" << std::endl << std::endl;
    if(glewInit() != GLEW_OK)
        throw std::runtime_error("glewInit failed");

    // print out some info about the graphics drivers
    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
    std::cout << "Vendedor: " << glGetString(GL_VENDOR) << std::endl;
    std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;

    // Carga de los Shaders
    std::cout << std::endl << "Cargando Shaders" << std::endl;

    Shader shader;

    std::vector<GLuint> shaders;
    shaders.push_back(shader.LoadShader("../../Shaders/VertexShader.glsl", GL_VERTEX_SHADER));
    shaders.push_back(shader.LoadShader("../../Shaders/FragmentShader.glsl", GL_FRAGMENT_SHADER));
    shaderProgram = new Program(shaders);


    glUseProgram(shaderProgram->ReturnProgramID());

    aPositionLocation=shaderProgram->attrib(A_POSITION);
    aNormalLocation=shaderProgram->attrib(A_NORMAL);

    uProjectionMatrixLocation=shaderProgram->uniform(U_PROJECTIONMATRIX);
    uMVMatrixLocation=shaderProgram->uniform(U_MVMATRIX);
    uVMatrixLocation=shaderProgram->uniform(U_VMATRIX);
    uColorLocation=shaderProgram->uniform(U_COLOR);
    uLuz0Location=shaderProgram->uniform(U_LUZ0);


    // Habilitamos el paso de attributes
    glEnableVertexAttribArray(aPositionLocation);
    glEnableVertexAttribArray(aNormalLocation);

    // Estableciendo la matriz de proyección perspectiva
    GLUI_Master.get_viewport_area( &tx, &ty, &tw, &th );
    xy_aspect = (float)tw / (float)th;
    projectionMatrix = glm::perspective(45.0f, xy_aspect, 0.1f, 1000.0f);
    glUniformMatrix4fv(uProjectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
}


/******************** TEscena::AddObject(TPrimitiva *object) *****************/

void __fastcall TEscena::AddObject(TPrimitiva *object)
{
    objects[num_objects] = object;
    num_objects++;
}

/******************** TEscena::RenderCars() **********************************/

void __fastcall TEscena::RenderObjects(bool reflejo) {

    for (int i=0; i<num_objects; i++)
    {
        objects[i]->Render(seleccion, reflejo);
    }
}

/***************************************** TEscena::Render() *****************/

void __fastcall TEscena::Render()
{
    glm::mat4 rotateMatrix;

    glClearColor(0.0, 0.7, 0.9, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Cálculo de la vista (cámara)
    viewMatrix      = glm::mat4(1.0f);
    rotateMatrix    = glm::make_mat4(view_rotate);
    viewMatrix      = glm::translate(viewMatrix,glm::vec3(view_position[0], view_position[1], view_position[2]));
    viewMatrix      = viewMatrix*rotateMatrix;
    viewMatrix      = glm::scale(viewMatrix,glm::vec3(scale, scale, scale));

    glUniform1i(uLuz0Location, true);
    glUniformMatrix4fv(uVMatrixLocation, 1, GL_FALSE, glm::value_ptr(viewMatrix)); // Para la luz matrix view pero sin escalado!

    // Dibujar carretera y objetos
    RenderObjects(seleccion);

    glutSwapBuffers();
}

// Selecciona un objeto a través del ratón
void __fastcall TEscena::Pick3D(int mouse_x, int mouse_y){}


TPrimitiva* __fastcall TEscena::getObject(int i)
{
    return objects[i];
}
