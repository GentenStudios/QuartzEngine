#include "engine/common.hpp"

#include "engine/graphics/opengl/opengl.hpp"

#include "engine/graphics/opengl/VertexArray.hpp"
#include "engine/graphics/opengl/VertexBuffer.hpp"
#include "engine/graphics/opengl/ShaderPipeline.hpp"

#include "engine/graphics/IWindow.hpp"

namespace phx
{
	namespace gfx
	{
		namespace gl
		{

			struct VertexAttrib
			{
				int index;
				int componentCount;
				int totalSize;
				int offset;
			};

			enum class BufferTarget
			{
				ARRAY = GL_ARRAY_BUFFER,
				DRAW_INDIRECT = GL_DRAW_INDIRECT_BUFFER,
				DISPATCH_INDIRECT = GL_DISPATCH_INDIRECT_BUFFER,
				ELEMENT = GL_ELEMENT_ARRAY_BUFFER,
				TEXTURE = GL_TEXTURE_BUFFER,
				UNIFORM = GL_UNIFORM_BUFFER
			};

			enum class BufferUsage
			{
				STREAM_DRAW = GL_STREAM_DRAW,
				STATIC_DRAW = GL_STATIC_DRAW,
				DYNAMIC_DRAW = GL_DYNAMIC_DRAW,
			};

			class Renderer
			{
			public:
				Renderer();
				~Renderer();

				void attachWindow(phx::gfx::IWindow* window);

				void generateVAO(std::string& name);
				void bindVAO(std::string& name);
				void unbindVAO(std::string& name);

				void generateVBO(std::string& name);
				void bindVBO(std::string& name);
				void setVBOData(void* buffer, int size);
				void subVBOData(void* buffer, int offset, int size);
				void unbindVBO();

				void addVertexAttrib(int index, int componentCount, int totalSize);
				void enableVertexAttrib(int index);
				void enableAllVertexAttribs();

			private:
				IWindow* m_window;

				std::unordered_map<std::string, VertexArray> m_vertexArrays;
				std::unordered_map<std::string, VertexBuffer> m_vertexBuffers;
				std::unordered_map<std::string, VertexAttrib> m_vertexAttribs;
				
			};

		}
	}
}