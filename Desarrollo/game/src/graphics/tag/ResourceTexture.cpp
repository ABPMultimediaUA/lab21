#include "ResourceTexture.h"

#include <iostream>

#include "tag/TAGEngine.h"


unsigned int tag::ResourceTexture::_nextTextureID = 0;

tag::ResourceTexture::ResourceTexture() :
    m_image(0),
    m_textureID(0)
{
}

tag::ResourceTexture::~ResourceTexture()
{
    if (m_textureID)
        glDeleteTextures(1, &m_textureID);
}

/////////////////////////////
GLuint tag::ResourceTexture::loadTexture(Image* image)
{
	GLuint textureId;
	glGenTextures(1, &textureId); // Reservar espacio para la textura

	glBindTexture(GL_TEXTURE_2D, textureId); // Activar la textura a editar

	// Mapear la imagen a la textura
	glTexImage2D(GL_TEXTURE_2D,                // Always GL_TEXTURE_2D
				 0,                            // 0 for now
				 GL_RGB,                       // Format OpenGL uses for image
				 image->width, image->height,  // Width and height
				 0,                            // The border of the image
				 GL_RGB,                       // GL_RGB, because pixels are stored in RGB format
				 GL_UNSIGNED_BYTE,             // GL_UNSIGNED_BYTE, because pixels are stored
                                               //as unsigned numbers
				 image->pixels);               //The actual pixel data


	// Filtros
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	return textureId;
}

///////////////////////////
void tag::ResourceTexture::load(std::string fileName)
{
    setName(fileName);

    Image* image = loadBMP(fileName.c_str());

    m_textureID = loadTexture(image);
    m_textureIndex = ResourceTexture::_nextTextureID++;  // Despues de asignar, incrementamos

    delete image;
}

///////////////////////////
void tag::ResourceTexture::activateTexture() const
{
    glActiveTexture(GL_TEXTURE0+m_textureIndex);
    glBindTexture(GL_TEXTURE_2D, m_textureID);
    glUniform1i(TAGEngine::_uTextureSamplerLocation, m_textureIndex);
    glUniform1i(TAGEngine::_uHasTexture, true);
}

///////////////////////////
void tag::ResourceTexture::deactivateTexture() const
{
    //glActiveTexture(GL_TEXTURE0+m_textureIndex);  // TODO si le pongo +m_textureIndex me da error!!
    glActiveTexture(GL_TEXTURE0);                   // pero en cambio sin esta linea también da error.
    glBindTexture(GL_TEXTURE_2D, 0);
    glUniform1i(TAGEngine::_uHasTexture, false);
}
