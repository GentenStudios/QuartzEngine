#include <engine/common.hpp>

#include <engine/graphics/window.hpp>
#include <engine/utils/logging.hpp>

#include "client/chunk.hpp"
#include "client/textures.hpp"

int main()
{
    INITLOGGER( "pheonix.log", pheonix::LogVerbosity::DEBUG );
    INFO( "CLIENT STARTING..." );

    pheonix::graphics::Window* window = new pheonix::graphics::Window( 1280, 720, std::string("Project Pheonix") );

    glewInit();

    glEnable( GL_DEPTH_TEST );

    pheonix::graphics::Texture dirt;
    DEBUG( "LOADING TEXTURE" );
    dirt.loadTex( std::string("../dirt.png") );
    DEBUG( "TEXTURE LOADED" );

    pheonix::graphics::Chunk* chunk = new pheonix::graphics::Chunk();

    DEBUG( "POPULATING CHUNK!" );
    chunk->populateChunk(16);
    DEBUG( "CHUNK POPULATED" );

    chunk->build();
    DEBUG( "CHUNK HAS BEEN BUILT!" );

    while ( !window->shouldClose() ) {
        window->pollEvents();

        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
        glClearColor( 0.1f, 0.3f, 0.9f, 1.0f );

        dirt.bind( 0 );

        chunk->draw();

        window->swapBuffers();
    }

    INFO( "CLIENT QUITTING" );
}
