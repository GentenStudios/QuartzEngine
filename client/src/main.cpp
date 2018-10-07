#include <engine/common.hpp>

#include "client/client.hpp"

#include <GL/glew.h>
#include <engine/utils/logging.hpp>
#include <engine/graphics/window.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "client/chunk.hpp"
#include "client/textures.hpp"

//extern const char* vertexShaderSource;
//const char* vertexShaderSource = "#version 330 core \n"
//                                 "layout (location = 0) in vec3 aPos; \n"
//                                 "uniform mat4 model; \n"
//                                 "uniform mat4 view; \n"
//                                 "uniform mat4 projection; \n"
//                                 "void main() \n"
//                                 "{ \n"
//                                     "gl_Position = projection * view * model * vec4(aPos, 1.0); \n"
//                                 "}";

//extern const char* fragmentShaderSource;
//const char* fragmentShaderSource = "#version 330 core \n"
//                                   "out vec4 FragColor; \n"
//                                   "void main() \n"
//                                   "{ \n"
//                                       "FragColor = vec4(0.3f, 0.6f, 0.9f, 1.0f);"
//                                   "}";

int main()
{
    pheonix::graphics::Window* window = new pheonix::graphics::Window( 1280, 720, std::string("Project Pheonix") );

    glewInit();

    pheonix::graphics::Texture stone;
    //stone.loadTex( std::string("texture.png") );

    pheonix::graphics::Chunk* chunk = new pheonix::graphics::Chunk();
    chunk->populateChunk(16);

    while ( !window->shouldClose() ) {
        window->pollEvents();

        glClear( GL_COLOR_BUFFER_BIT );
        glClearColor( 0.1f, 0.3f, 0.9f, 1.0f );

        chunk->build();
        //stone.bind(0);
        std::cout << glGetError() << std::endl;
        chunk->draw();
        std::cout << glGetError() << std::endl;

        window->swapBuffers();
    }
}
