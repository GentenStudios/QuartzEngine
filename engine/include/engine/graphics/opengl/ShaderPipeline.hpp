#pragma once

#include "engine/common.hpp"
#include "engine/math/Vector2.hpp"
#include "engine/math/Vector3.hpp"
#include "engine/math/Matrix4x4.hpp"

#include "engine/graphics/opengl/opengl.hpp"

namespace phx
{
	namespace gfx
	{
		namespace gl
		{

			class ShaderPipeline
			{
			public:
				ShaderPipeline();
				~ShaderPipeline();

				void addStage(ShaderType stage, const char* shaderSource);
				void build();

				void use() const;

				template <typename T> void setUniform1(const std::string& name, T a) const;
        		template <typename T> void setUniform2(const std::string& name, T a, T b) const;
        		template <typename T> void setUniform3(const std::string& name, T a, T b, T c) const;
        		template <typename T> void setUniform4(const std::string& name, T a, T b, T c, T d) const;

				void setVec2(const std::string& name, phx::Vector2 &value) const;
				void setVec2(const std::string& name, float x, float y) const;

				void setVec3(const std::string& name, phx::Vector3 &value) const;
				void setVec3(const std::string& name, float x, float y, float z) const;

				void setMat4(const std::string &name, const Matrix4x4& mat) const;

				unsigned int getShaderProgram() const;

			private:
				std::vector<unsigned int> m_shaders;
				unsigned int m_shaderProgram;

			};

		}
	}
}
