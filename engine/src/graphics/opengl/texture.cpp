#include "engine/graphics/opengl/texture.hpp"

#include <cassert>
#include <memory>
#include <algorithm>

using namespace phoenix::graphics::opengl;

Texture::Texture( Target target, int width, int height, Texture::Format format ) :
	m_width( width ),
	m_height( height ),
	m_isBound( false ),
	m_pixelDataType( GLType::UBYTE ),
	m_currentUnit( 0 )
{
	glGenTextures( 1, &m_id );
	m_target = target;
	m_format = format;
}

void Texture::setData( unsigned char* pixels )
{
	bind( 0 );

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexImage2D(
				static_cast<GLenum>(m_target),
				0,
				static_cast<GLint>(m_format),
				m_width,
				m_height,
				0,
				static_cast<GLenum>(m_format),
				static_cast<GLenum>(m_pixelDataType),
				pixels
				);
}

void Texture::setCompressedData( unsigned char * pixels, unsigned int levels, unsigned int blockSize )
{
	bind( 0 );

	int level;
	int offset = 0;
	unsigned int width = m_width;
	unsigned int height = m_height;

	for (level = 0; level < levels && (width || height); ++level)
	{
		int size = ((width + 3) / 4) * ((height + 3) / 4) * blockSize;

		glCompressedTexImage2D(
					static_cast<GLuint>(m_target),
					level,
					static_cast<GLenum>(m_format),
					width,
					height,
					0,
					size,
					pixels + offset
					);

		offset += size;
		width /= 2;
		height /= 2;
	}
}

void Texture::bind( unsigned int unit )
{
	m_currentUnit = unit;

	glActiveTexture( GL_TEXTURE0 + unit );
	glBindTexture( static_cast<GLenum>(m_target), m_id );

	m_isBound = true;
}

void Texture::unbind()
{
	glActiveTexture( GL_TEXTURE0 + m_currentUnit );
	glBindTexture( static_cast<GLenum>(m_target), 0 );

	m_currentUnit = 0;
	m_isBound = false;
}

GLuint Texture::getID() const
{
	return m_id;
}

int Texture::getIndex() const
{
	return static_cast<int>(m_currentUnit);
}

Texture::~Texture()
{
	glDeleteTextures( 1, &m_id );
}
