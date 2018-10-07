#pragma once

#include <GL/glew.h>
#include <GL/gl.h>
#include "engine/graphics/window.hpp"

namespace pheonix
{
    namespace graphics
    {
        namespace opengl {

            enum class layoutChoice
            {
                ARRAY_BUFFER = GL_ARRAY_BUFFER,
                ELEMENT_BUFFER = GL_ELEMENT_ARRAY_BUFFER,
            };

            class Renderer
            {
            public:
                Renderer();
                ~Renderer();

                void attachWindow();
                void detachWindow();

                int addVertexArray( std::string name );
                int removeVertexArray( std::string name  );

                int addVertexBuffer( std::string name );
                int removeVertexBuffer( std::string name );

                template< typename T >
                void addLayout( std::string bufferName, layoutChoice dataType );
            };

        }
    }
}
