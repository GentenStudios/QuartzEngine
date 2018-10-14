#include <engine/common.hpp>

#include <engine/graphics/window.hpp>
#include <engine/graphics/opengl/texture.hpp>

#include <stb_image/stb_image.h>

#include "client/chunk.hpp"
#include "client/textures.hpp"

int main()
{
	INITLOGGER( "pheonix.log", phoenix::LogVerbosity::INFO );
	INFO( "CLIENT STARTING..." );

	phoenix::graphics::Window* window = new phoenix::graphics::Window( 1280, 720, std::string("Project Pheonix") );

	glewInit();

	glEnable( GL_DEPTH_TEST );

	int nChannels, texWidth, texHeight;
	unsigned char* data = stbi_load( "../dirt.png", &texWidth, &texHeight, &nChannels, 0);

	int nChannels2, texWidth2, texHeight2;
	unsigned char* data2 = stbi_load( "../rubbish.png", &texWidth2, &texHeight2, &nChannels2, 0);

	phoenix::graphics::opengl::Texture* dirt = new phoenix::graphics::opengl::Texture( phoenix::graphics::opengl::Texture::Target::TEXTURE2D, texWidth, texHeight, phoenix::graphics::opengl::Texture::Format::RGBA );
	dirt->bind( 0 );
	dirt->setData( data );

	phoenix::graphics::opengl::Texture* wtf = new phoenix::graphics::opengl::Texture( phoenix::graphics::opengl::Texture::Target::TEXTURE2D, texWidth2, texHeight2, phoenix::graphics::opengl::Texture::Format::RGBA );
	wtf->bind( 1 );
	wtf->setData( data2 );

	phoenix::graphics::Chunk* chunk = new phoenix::graphics::Chunk();

	DEBUG( "POPULATING CHUNK!" );
	chunk->populateChunk(16);
	DEBUG( "CHUNK POPULATED" );

	chunk->build();
	DEBUG( "CHUNK HAS BEEN BUILT!" );

	while ( !window->shouldClose() ) {
		window->pollEvents();

		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
		glClearColor( 0.1f, 0.3f, 0.9f, 1.0f );

		wtf->bind( 0 );
		dirt->bind( 1 );
		std::cout << glGetError() << std::endl;

		chunk->draw();

		window->swapBuffers();
	}

	INFO( "CLIENT QUITTING" );
}
