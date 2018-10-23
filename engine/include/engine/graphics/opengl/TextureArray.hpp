#include "engine/common.hpp"

#include "engine/graphics/opengl/opengl.hpp"

namespace phx
{
	namespace gfx
	{
		namespace gl
		{

			class TextureArray
			{
			public:
				TextureArray();
				~TextureArray();

				
				void add(std::vector<std::string> paths);

				void bind(int index = -1);
				void unbind();

			private:

				unsigned int m_textureID;
				int m_textureNumber = 0;
			};
		
		}
	}
}