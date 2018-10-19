#pragma once

#include <engine/common.hpp>

#include <GL/glew.h>

#include <string>


namespace phoenix
{
	namespace graphics {

		class Texture
		{
		public:
			Texture() {}
			~Texture() {}

			void loadTex(std::string textureFilepath);

			inline unsigned int getTextureID() const { return m_texId; }

			void bind(int textureSlot);
			void unbind();

		private:
			unsigned int m_texId;
			int m_texWidth;
			int m_texHeight;
		};

	}
}
