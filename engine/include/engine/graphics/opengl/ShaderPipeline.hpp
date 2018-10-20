#pragma once

#include "engine/common.hpp"
#include "engine/math/Vector2.hpp"
#include "engine/math/Vector3.hpp"
#include "engine/math/Matrix4x4.hpp"

#include <GL/glew.h>

namespace phx
{
	namespace gfx
	{
		namespace gl
		{

			enum class ShaderStage
			{
				VERTEX_SHADER = GL_VERTEX_SHADER,
				FRAGMENT_SHADER = GL_FRAGMENT_SHADER,
				GEOMETRY_SHADER = GL_GEOMETRY_SHADER,
			};

			class ShaderPipeline
			{
			public:
				ShaderPipeline();
				~ShaderPipeline();

				void addStage(ShaderStage stage, const char* shaderSource);
				void build();

				void use() const;

				void setBool(const std::string& name, bool value) const;
				void setInt(const std::string& name, int value) const;
				void setFloat(const std::string& name, float value) const;

				void setVec2(const std::string& name, Vector2 &value) const;
				void setVec2(const std::string& name, float x, float y) const;

				void setVec3(const std::string& name, Vector3 &value) const;
				void setVec3(const std::string& name, float x, float y, float z) const;

				void setMat4(const std::string &name, Matrix4x4& mat) const;

				unsigned int getShaderProgram() const;

			private:
				std::vector<unsigned int> m_shaders;
				unsigned int m_shaderProgram;

			};

		}
	}
}