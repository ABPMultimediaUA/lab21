#include "ResourceTexture.h"

#include <iostream>

#include "tag/TAGEngine.h"
#include "tag/TAGError.h"

tag::ResourceTexture::ResourceTexture() :
    m_image(0),
    m_diffuseTextureID(0),
    m_specularTextureID(0),
    m_normalTextureID(0)
{
}

tag::ResourceTexture::~ResourceTexture()
{
    if (m_diffuseTextureID)
        glDeleteTextures(1, &m_diffuseTextureID);
    if (m_specularTextureID)
        glDeleteTextures(1, &m_specularTextureID);
    if (m_normalTextureID)
        glDeleteTextures(1, &m_normalTextureID);
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

    glGenerateMipmap(GL_TEXTURE_2D);

	// Filtros
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glBindTexture(GL_TEXTURE_2D, 0);

	return textureId;
}

/////////////////////////////
Image* tag::ResourceTexture::createBlackImage() const
{
    char* pixels = new char[3];  // la clase Image hace el delete de pixels
    pixels[0] = 0; pixels[1] = 0; pixels[2] = 0;

    return (new Image(pixels, 1, 1));
}

//////////////////////////////////
std::string tag::ResourceTexture::getFileName(const std::string fileName, const std::string appendName) const
{
    std::string f = fileName.substr(0, fileName.size()-4);
    f = f + appendName + ".bmp";
    return f;
}

///////////////////////////
void tag::ResourceTexture::load(std::string fileName)
{
    setName(fileName);

    Image* image;

    // Textura difusa
    image = loadBMP(fileName.c_str());
    if (!image)
        throw std::runtime_error("No se encuentra el fichero de textura " + fileName);
    m_diffuseTextureID = loadTexture(image);
    delete image;

    // Textura especular
    image = loadBMP(getFileName(fileName, "specular").c_str());
    if (!image)  // Si no existe textura especular, genero una textura de 1x1 en negro, sin brillos.
        image = createBlackImage();
    m_specularTextureID = loadTexture(image);
    delete image;

    // Textura de normales
    image = loadBMP(getFileName(fileName, "normal").c_str());
    if (image)
    {
        m_normalTextureID = loadTexture(image);
        delete image;
    }
}

///////////////////////////
void tag::ResourceTexture::activateTexture() const
{
    glUniform1i(TAGEngine::_uMaterialHasTextureLocation, true);
    glUniform1f(TAGEngine::_uMaterialShininessLocation, 32.0);

    glActiveTexture(GL_TEXTURE0+Entity::_diffuseTextureIndex);
    glBindTexture(GL_TEXTURE_2D, m_diffuseTextureID);

    glActiveTexture(GL_TEXTURE0+Entity::_specularTextureIndex);
    glBindTexture(GL_TEXTURE_2D, m_specularTextureID);

    if (m_normalTextureID)
    {
        // Tiene textura de normales
        glActiveTexture(GL_TEXTURE0+Entity::_normalTextureIndex);
        glBindTexture(GL_TEXTURE_2D, m_normalTextureID);
        glUniform1i(TAGEngine::_uHasNormalTextureLocation, true);
    }
    else
    {
        glUniform1i(TAGEngine::_uHasNormalTextureLocation, false);
    }
}

///////////////////////////
void tag::ResourceTexture::deactivateTexture() const
{
    glUniform1i(TAGEngine::_uMaterialHasTextureLocation, false);
    glUniform1i(TAGEngine::_uHasNormalTextureLocation, false);

    glActiveTexture(GL_TEXTURE0+Entity::_diffuseTextureIndex);
    glBindTexture(GL_TEXTURE_2D, 0);

    glActiveTexture(GL_TEXTURE0+Entity::_specularTextureIndex);
    glBindTexture(GL_TEXTURE_2D, 0);

    if (m_normalTextureID)
    {
        glActiveTexture(GL_TEXTURE0+Entity::_normalTextureIndex);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    glActiveTexture(GL_TEXTURE0);
}
