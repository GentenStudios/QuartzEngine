#include <engine/common.hpp>

#include <engine/graphics/window.hpp>
#include <engine/graphics/opengl/texture.hpp>
#include <engine/camera.hpp>

#include <stb_image/stb_image.h>
#include <thread>

#include "client/chunk.hpp"
#include "client/textures.hpp"

#include <imgui.h>

int main()
{
	INITLOGGER( "pheonix.log", phoenix::LogVerbosity::DEBUG );
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
	phoenix::graphics::Chunk* chunk2 = new phoenix::graphics::Chunk();
	phoenix::graphics::Chunk* chunk3 = new phoenix::graphics::Chunk();
	phoenix::graphics::Chunk* chunk4 = new phoenix::graphics::Chunk();

	phoenix::FreeRoamCamera camera(window);

	DEBUG( "POPULATING CHUNKS!" );
	chunk->populateChunk(16, {0.0f, 0.0f, 0.0f});
	chunk2->populateChunk(16, {16.0f, 0.0f, 0.0f});
	chunk3->populateChunk(16, {16.0f, 16.0f, 0.0f});
	chunk4->populateChunk(16, {0.0f, 16.0f, 0.0f});
	DEBUG( "CHUNKS POPULATED" );

	chunk->build();
	chunk2->build();
	chunk3->build();
	chunk4->build();
	DEBUG( "CHUNK HAS BEEN BUILT!" );

	bool _lastStateOfEscape = false;

	while ( !window->shouldClose() ) {
		window->pollEvents();

		camera.tick(0.16f);

		bool isEscapeDown = window->getKeyState(GLFW_KEY_ESCAPE) != 0;

		if (isEscapeDown && !_lastStateOfEscape) {
			camera.enabled = !camera.enabled;
			if (camera.enabled) {
				window->setCursorState(phoenix::graphics::CursorState::DISABLED);
			}
			else {
				window->setCursorState(phoenix::graphics::CursorState::NORMAL);
			}
		}

		_lastStateOfEscape = isEscapeDown;

		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
		glClearColor( 0.1f, 0.3f, 0.9f, 1.0f );

		wtf->bind( 0 );
		dirt->bind( 1 );
		chunk->draw(camera);
		chunk2->draw(camera);
		chunk3->draw(camera);
		chunk4->draw(camera);

		ImGui::Begin("Demo Window");
		ImGui::Button("Press ME!");
		ImGui::End();

		window->swapBuffers();

		// Lock to 60FPS for now (until a proper game loop is implemented)
		using namespace std::chrono_literals;
		std::this_thread::sleep_for(16ms);
	}

	INFO( "CLIENT QUITTING" );
}
