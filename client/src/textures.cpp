#include "client/textures.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image/stb_image.h>

using namespace pheonix::graphics;

void Texture::loadTex( std::string textureFilepath )
{
    glGenTextures(1, &m_texId);
    glBindTexture(GL_TEXTURE_2D, m_texId);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    int nChannels;
    unsigned char* data = stbi_load( textureFilepath.c_str(), &m_texWidth, &m_texHeight, &nChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_texWidth, m_texHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }

    stbi_image_free(data);
}

void Texture::bind( int slot )
{
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, m_texId);
}

void Texture::unbind()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}
