#pragma once

#include <engine/core/Core.hpp>

#include <engine/core/graphics/gl/GLEnums.hpp>
#include <engine/core/graphics/gl/GLDebug.hpp>
#include <GL/glew.h>

#include <unordered_map>

namespace phx
{
	namespace gfx
	{
		namespace gl
		{
			/// @brief Alias TexCache to an unordered_map, primarily just for easier use, because i'm lazy and i ain't gunna type out the whole thing like 50 times.
			using TexCache = std::unordered_map<std::string, int>;

			/**
			 * @brief Class for generating a texture array for blocks.
			 * 
			 * @details Downsides of using this class is that all textures can only be one size until we implement some sort of shaderFactory kind of thing, which may take some work, however, will be worth it.
			 */
			class TextureArray
			{
			public:
				/**
				 * @brief Construct a new Texture Array object, reserve memory for 256 textures as well - we might wanna fix that one day.
				 * 
				 */
				TextureArray();

				/**
				 * @brief Destroy the Texture Array object, and delete the texture.
				 * 
				 */
				~TextureArray();

				/**
				 * @brief Add a texture to the array, until the array is out of places, which is another reason we need a ShaderFactory.
				 * 
				 * @param path The path to the array, will be loaded by stb_image, unless we create something faster... one day, we will, and then we will party 
				 */
				void add(const std::string& path);

				/**
				 * @brief Bind the texture array to a texture unit.
				 * 
				 * @param index The Texture Unit to bind to, if not selected, the texture unit will either be 0, or binded to whatever texture unit was last selected.
				 */
				void bind(int index = -1);

				/**
				 * @brief What do you think this does, you numpty.
				 * @details if you didn't figure it out, this unbinds the texture from the texture unit. well.... it just binds "0" to that texture, but shut up.
				 * 
				 */
				void unbind();

				/**
				 * @brief Get the texture list: remember, it's an unordered map? well, you better remember now, cuz i won't
				 * 
				 * @return const TexCache& 
				 */
				const TexCache& getTextureList() { return m_texNames; }

				/**
				 * @brief Get the texture layer a particular texture is using.
				 * 
				 * @param path The path of the texture.
				 * @return The actual texture layer that the texture is residing in, -1 if there is no texture with that path.
				 */
				int getTexLayer(const std::string& path);

			private:
				TexCache m_texNames;

				unsigned int m_textureID;
				int m_textureNumber = 0;
			};

		}
	}
}