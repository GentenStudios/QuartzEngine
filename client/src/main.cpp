#include "engine/common.hpp"

#include "client/client.hpp"

#include "engine/utils/logging.hpp"
#include "engine/graphics/window.hpp"

#include <glm/glm.hpp>

int main()
{

    pheonix::graphics::Window* window = new pheonix::graphics::Window( 1280, 720, std::string("Project Pheonix  ") );

    while ( !window->shouldClose() ) {
        window->pollEvents();

        glClear( GL_COLOR_BUFFER_BIT );
        glClearColor( 0.1f, 0.3f, 0.9f, 1.0f );


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

        static const glm::vec2 CUBE_UV[] = {
            // front
            glm::vec2(0.f, 0.f),
            glm::vec2(1.f, 0.f),
            glm::vec2(1.f, 1.f),
            glm::vec2(1.f, 1.f),
            glm::vec2(0.f, 1.f),
            glm::vec2(0.f, 0.f),

            // back
            glm::vec2(0.f, 0.f),
            glm::vec2(1.f, 0.f),
            glm::vec2(1.f, 1.f),
            glm::vec2(1.f, 1.f),
            glm::vec2(0.f, 1.f),
            glm::vec2(0.f, 0.f),

            // left
            glm::vec2(1.f, 0.f),
            glm::vec2(1.f, 1.f),
            glm::vec2(0.f, 1.f),
            glm::vec2(0.f, 1.f),
            glm::vec2(0.f, 0.f),
            glm::vec2(1.f, 0.f),

            // right
            glm::vec2(1.f, 0.f),
            glm::vec2(1.f, 1.f),
            glm::vec2(0.f, 1.f),
            glm::vec2(0.f, 1.f),
            glm::vec2(0.f, 0.f),
            glm::vec2(1.f, 0.f),

            // bottom
            glm::vec2(0.f, 1.f),
            glm::vec2(1.f, 1.f),
            glm::vec2(1.f, 0.f),
            glm::vec2(1.f, 0.f),
            glm::vec2(0.f, 0.f),
            glm::vec2(0.f, 1.f),

            // top
            glm::vec2(0.f, 1.f),
            glm::vec2(1.f, 1.f),
            glm::vec2(1.f, 0.f),
            glm::vec2(1.f, 0.f),
            glm::vec2(0.f, 0.f),
            glm::vec2(0.f, 1.f)
        };

        static const glm::vec3 EMPTY_BLOCK[] = {
            glm::vec3(0.f), glm::vec3(0.f), glm::vec3(0.f),
            glm::vec3(0.f), glm::vec3(0.f), glm::vec3(0.f),
            glm::vec3(0.f), glm::vec3(0.f), glm::vec3(0.f),
            glm::vec3(0.f), glm::vec3(0.f), glm::vec3(0.f),
            glm::vec3(0.f), glm::vec3(0.f), glm::vec3(0.f),
            glm::vec3(0.f), glm::vec3(0.f), glm::vec3(0.f),
            glm::vec3(0.f), glm::vec3(0.f), glm::vec3(0.f),
            glm::vec3(0.f), glm::vec3(0.f), glm::vec3(0.f),
            glm::vec3(0.f), glm::vec3(0.f), glm::vec3(0.f),
            glm::vec3(0.f), glm::vec3(0.f), glm::vec3(0.f),
            glm::vec3(0.f), glm::vec3(0.f), glm::vec3(0.f),
            glm::vec3(0.f), glm::vec3(0.f), glm::vec3(0.f)
        };

//        unsigned int vao;
//        glGenVertexArrays(1, vao);
//        glBindVertexArray(vao);

//        glGenBuffers(1, &m_vbo);
//        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
//        glBufferData(GL_ARRAY_BUFFER, m_totalVerticesInChunk * sizeof(glm::vec3), chunkVertices, GL_DYNAMIC_DRAW);

//        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
//        glEnableVertexAttribArray(0);

//        glGenBuffers(1, &m_tbo);
//        glBindBuffer(GL_ARRAY_BUFFER, m_tbo);
//        glBufferData(GL_ARRAY_BUFFER, m_totalUvsInChunk * sizeof(glm::vec2), chunkUVs, GL_STATIC_DRAW);

//        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void*)0);
//        glEnableVertexAttribArray(1);

        window->swapBuffers();
    }
}
