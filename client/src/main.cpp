#include <engine/common.hpp>

#include <engine/graphics/window.hpp>
#include <engine/graphics/opengl/texture.hpp>
#include <engine/camera.hpp>

#include <stb_image/stb_image.h>
#include <thread>

#include "client/chunk.hpp"
#include "client/textures.hpp"

#include <engine/imgui.hpp>

int main()
{
	INITLOGGER("pheonix.log", phoenix::LogVerbosity::DEBUG);
	INFO("CLIENT STARTING...");

	phoenix::graphics::Window* window = new phoenix::graphics::Window(1280, 720, std::string("Project Pheonix"));
	glewInit();

	glEnable(GL_DEPTH_TEST);

	int nChannels, texWidth, texHeight;
	unsigned char* data = stbi_load("../dirt.png", &texWidth, &texHeight, &nChannels, 0);

	int nChannels2, texWidth2, texHeight2;
	unsigned char* data2 = stbi_load("../rubbish.png", &texWidth2, &texHeight2, &nChannels2, 0);

	phoenix::graphics::opengl::Texture* dirt = new phoenix::graphics::opengl::Texture(phoenix::graphics::opengl::Texture::Target::TEXTURE2D, texWidth, texHeight, phoenix::graphics::opengl::Texture::Format::RGBA);
	dirt->bind(0);
	dirt->setData(data);

	phoenix::graphics::opengl::Texture* wtf = new phoenix::graphics::opengl::Texture(phoenix::graphics::opengl::Texture::Target::TEXTURE2D, texWidth2, texHeight2, phoenix::graphics::opengl::Texture::Format::RGBA);
	wtf->bind(1);
	wtf->setData(data2);

	phoenix::graphics::Chunk* chunk = new phoenix::graphics::Chunk();

	phoenix::FreeRoamCamera camera(window);

	DEBUG("POPULATING CHUNK!");
	chunk->populateChunk(16, { 0.0f, 0.0f, 0.0f });
	DEBUG("CHUNK POPULATED");

	chunk->build();
	DEBUG("CHUNK HAS BEEN BUILT!");

	bool _lastStateOfEscape = false;

	phoenix::Vector3 positionOfDestroy[3] = { 0,0,0 };

	while (!window->shouldClose()) {
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

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.1f, 0.3f, 0.9f, 1.0f);

		wtf->bind(0);
		dirt->bind(1);
		chunk->draw(camera);

		chunk->blockDestroyAt(0, 0, 0);

		std::stringstream camPos;
		phoenix::Vector3 cameraPos = camera.getPosition();
		camPos << "Position of Camera:   " << cameraPos.x << ", " << cameraPos.y << ", " << cameraPos.z;

		ImGui::Begin("Demo Window");
		ImGui::Text(camPos.str().c_str());
		ImGui::NewLine();

		ImGui::Text("Destroy at Position: ");
		ImGui::SameLine();
		ImGui::InputVector3("", positionOfDestroy);
		if (ImGui::Button("DESTROY!!!"))
			chunk->blockDestroyAt(static_cast<int>(positionOfDestroy->x), static_cast<int>(positionOfDestroy->y), static_cast<int>(positionOfDestroy->z));
		ImGui::End();

		window->swapBuffers();

		// Lock to 60FPS for now (until a proper game loop is implemented)
		using namespace std::chrono_literals;
		std::this_thread::sleep_for(16ms);
	}

	INFO("CLIENT QUITTING");
}
