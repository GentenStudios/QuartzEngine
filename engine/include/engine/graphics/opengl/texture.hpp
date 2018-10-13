#include "engine/common.hpp"
#include "engine/graphics/opengl/glTypes.hpp"

#include <GL/glew.h>
#include <glm/glm.hpp>

namespace pheonix {
	namespace graphics {
		namespace opengl {

			class Texture
			{

			public:
				/// Texture targets
				enum class Target
				{
					TEXTURE2D = GL_TEXTURE_2D,
					CUBEMAP   = GL_TEXTURE_CUBE_MAP,

					CUBE_MAP_POS_Y = GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
					CUBE_MAP_NEG_Y = GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
					CUBE_MAP_POS_X = GL_TEXTURE_CUBE_MAP_POSITIVE_X,
					CUBE_MAP_NEG_X = GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
					CUBE_MAP_POS_Z = GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
					CUBE_MAP_NEG_Z = GL_TEXTURE_CUBE_MAP_NEGATIVE_Z
				};

				/// Texture formats
				enum class Format
				{
					RGB       = GL_RGB,
					RGBA      = GL_RGBA,
				};

				/// Parameter Names
				enum class ParamName
				{
					MAG_FILTER = GL_TEXTURE_MAG_FILTER,
					MIN_FILTER = GL_TEXTURE_MIN_FILTER,
					WRAP_S     = GL_TEXTURE_WRAP_S,
					WRAP_T     = GL_TEXTURE_WRAP_T,
					WRAP_R     = GL_TEXTURE_WRAP_R
				};

				/// Parameter Values
				enum class ParamValue
				{
					NEAREST    = GL_NEAREST,
					LINEAR     = GL_LINEAR,
					CLAMP      = GL_CLAMP,
					CLAMP_EDGE = GL_CLAMP_TO_EDGE,
					REPEAT     = GL_REPEAT
				};

				/// Texture units
				enum class Unit
				{
					T0 = GL_TEXTURE0,
					T1 = GL_TEXTURE1,
					T2 = GL_TEXTURE2,
					T3 = GL_TEXTURE3,
					T4 = GL_TEXTURE4,
					T5 = GL_TEXTURE5,
					T6 = GL_TEXTURE6,
					NONE
				};

				/// Holds UV coordinates
				struct TextureUV
				{
					glm::vec2 bottomLeft;
					glm::vec2 topLeft;
					glm::vec2 topRight;
					glm::vec2 bottomRight;
				};

				// Constructor and Destructor
				Texture( Target target, int width, int height, Format format );
				~Texture();

				void setData( unsigned char* pixelData );

				void setCompressedData( unsigned char* pixels, unsigned int levels, unsigned int blockSize );

				void bind( Unit unit );

				void unbind();

				TextureUV uvCoords( float x, float y, float w, float h );

				int getIndex() const;

				unsigned int getId() const;

				inline bool isBound() { return m_isBound; }

			private:
				unsigned int m_id;
				Target m_target;
				Unit m_currentUnit;
				int m_width;
				int m_height;
				Format m_format;
				GLType m_pixelDataType;
				bool m_isBound;

				void create();
				void destroy();
			};

		};


	}
}
