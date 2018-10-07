#include "engine/common.hpp"

#include "client/client.hpp"

#include <GL/glew.h>
#include "engine/utils/logging.hpp"
#include "engine/graphics/window.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "client/chunk.hpp"

extern const char* vertexShaderSource;
const char* vertexShaderSource = "#version 330 core \n"
                                 "layout (location = 0) in vec3 aPos; \n"
                                 "uniform mat4 model; \n"
                                 "uniform mat4 view; \n"
                                 "uniform mat4 projection; \n"
                                 "void main() \n"
                                 "{ \n"
                                     "gl_Position = projection * view * model * vec4(aPos, 1.0); \n"
                                 "}";

extern const char* fragmentShaderSource;
const char* fragmentShaderSource = "#version 330 core \n"
                                   "out vec4 FragColor; \n"
                                   "void main() \n"
                                   "{ \n"
                                       "FragColor = vec4(0.3f, 0.6f, 0.9f, 1.0f);"
                                   "}";


int main()
{

    static const glm::vec3 CUBE_VERTICES[] = {
        // front
        glm::vec3(-1.f,-1.f,-1.f),
        glm::vec3(1.f,-1.f,-1.f),
        glm::vec3(1.f,1.f,-1.f),
        glm::vec3(1.f,1.f,-1.f),
        glm::vec3(-1.f,1.f,-1.f),
        glm::vec3(-1.f,-1.f,-1.f),

        // back
        glm::vec3(-1.f,-1.f,1.f),
        glm::vec3(1.f,-1.f,1.f),
        glm::vec3(1.f, 1.f,1.f),
        glm::vec3(1.f, 1.f,1.f),
        glm::vec3(-1.f, 1.f,1.f),
        glm::vec3(-1.f, -1.f,1.f),

        // left
        glm::vec3(-1.f, 1.f,1.f),
        glm::vec3(-1.f, 1.f,-1.f),
        glm::vec3(-1.f, -1.f,-1.f),
        glm::vec3(-1.f, -1.f,-1.f),
        glm::vec3(-1.f, -1.f,1.f),
        glm::vec3(-1.f, 1.f,1.f),

        // right
        glm::vec3(1.f, 1.f,1.f),
        glm::vec3(1.f, 1.f,-1.f),
        glm::vec3(1.f, -1.f,-1.f),
        glm::vec3(1.f, -1.f,-1.f),
        glm::vec3(1.f, -1.f,1.f),
        glm::vec3(1.f, 1.f,1.f),

        // bottom
        glm::vec3(-1.f, -1.f, -1.f),
        glm::vec3(1.f, -1.f, -1.f),
        glm::vec3(1.f, -1.f,  1.f),
        glm::vec3(1.f, -1.f,  1.f),
        glm::vec3(-1.f, -1.f,  1.f),
        glm::vec3(-1.f, -1.f, -1.f),

        // top
        glm::vec3(-1.f,  1.f, -1.f),
        glm::vec3(1.f,  1.f, -1.f),
        glm::vec3(1.f,  1.f,  1.f),
        glm::vec3(1.f,  1.f,  1.f),
        glm::vec3(-1.f,  1.f,  1.f),
        glm::vec3(-1.f,  1.f, -1.f)
    };



    pheonix::graphics::Window* window = new pheonix::graphics::Window( 1280, 720, std::string("Project Pheonix  ") );

    glewInit();

    unsigned int vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    unsigned int vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, 36 * sizeof(glm::vec3), CUBE_VERTICES, GL_DYNAMIC_DRAW);

    unsigned int vertexShader;
    vertexShader = glCreateShader( GL_VERTEX_SHADER );
    glShaderSource( vertexShader, 1, &vertexShaderSource, nullptr );
    glCompileShader( vertexShader );

    unsigned int fragmentShader;
    fragmentShader = glCreateShader( GL_FRAGMENT_SHADER );
    glShaderSource( fragmentShader, 1, &fragmentShaderSource, nullptr );
    glCompileShader( fragmentShader );

    int success;
    char infoLog[512];
    glGetShaderiv( vertexShader, GL_COMPILE_STATUS, &success );

    if ( !success ) {
        glGetShaderInfoLog( vertexShader, 512, nullptr, infoLog );
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    glGetShaderiv( fragmentShader, GL_COMPILE_STATUS, &success );

    if ( !success ) {
        glGetShaderInfoLog( fragmentShader, 512, nullptr, infoLog );
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();

    glAttachShader( shaderProgram, vertexShader );
    glAttachShader( shaderProgram, fragmentShader );
    glLinkProgram( shaderProgram );

    glDeleteShader( vertexShader );
    glDeleteShader( fragmentShader );

    pheonix::graphics::Chunk* chunk = new pheonix::graphics::Chunk();
    chunk->populateChunk(16);

    while ( !window->shouldClose() ) {
        window->pollEvents();

        glClear( GL_COLOR_BUFFER_BIT );
        glClearColor( 0.1f, 0.3f, 0.9f, 1.0f );

        glm::mat4 projection = glm::mat4( 1.0f );
        projection = glm::perspective( glm::radians( 45.0f ), 1280.f / 720.f, 0.1f, 100.0f );

        glm::mat4 view = glm::lookAt(
            glm::vec3(-50,50,3), // Camera is at (4,3,3), in World Space
            glm::vec3(3,10,3), // and looks at the origin
            glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
            );

        glm::mat4 model = glm::mat4( 1.0f );

        int modelLoc = glGetUniformLocation( shaderProgram, "model" );
        glUniformMatrix4fv( modelLoc, 1, GL_FALSE, glm::value_ptr( model ) );

        int viewLoc = glGetUniformLocation( shaderProgram, "view" );
        glUniformMatrix4fv( viewLoc, 1, GL_FALSE, glm::value_ptr( view ) );

        glUniformMatrix4fv( glGetUniformLocation( shaderProgram, "projection" ), 1, GL_FALSE, glm::value_ptr( projection ) );

        glUseProgram(shaderProgram);

        chunk->draw();
        std::cout << glGetError() << std::endl;

        window->swapBuffers();
    }
}
