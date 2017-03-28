#include "ResourceTexture.h"

#include <iostream>

#include "tag/TAGEngine.h"


tag::ResourceTexture::ResourceTexture() :
    m_image(0),
    m_textureID(0)
{
    //ctor
}

tag::ResourceTexture::~ResourceTexture()
{
    //dtor
    if (m_textureID)
        glDeleteTextures(1, &m_textureID);
}

GLuint tag::ResourceTexture::loadTexture(Image* image)
{
	GLuint textureId;
	glGenTextures(1, &textureId); // Reservar espacio para la textura

	glBindTexture(GL_TEXTURE_2D, textureId); // Activar la textura a editar

	// Filtros
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

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

	return textureId;
}

void tag::ResourceTexture::load(std::string fileName)
{
    setName(fileName);

    Image* image = loadBMP(fileName.c_str());
    m_textureID = loadTexture(image);
    delete image;
}

void tag::ResourceTexture::activateTexture() const
{
    //glActiveTexture(GL_TEXTURE0+m_textureID);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_textureID);
    glUniform1i(TAGEngine::_uTextureSamplerLocation, 0);
}

void tag::ResourceTexture::_deactivateTexture()
{
    // TODO desactivar textura COMO???? glBindTexture(GL_TEXTURE_2D, 0);
}
