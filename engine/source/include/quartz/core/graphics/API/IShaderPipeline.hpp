#pragma once

#include <quartz/core/Core.hpp>
#include <quartz/core/math/Math.hpp>

#include <quartz/core/graphics/API/GraphicsResource.hpp>

#include <string>

namespace qz
{
	namespace gfx
	{
		namespace api
		{
			enum class ShaderType : int
			{
				VERTEX_SHADER,
				FRAGMENT_SHADER,
			};

			class QZ_API IShaderPipeline
			{
			public:
				static GraphicsResource<IShaderPipeline> generateShaderPipeline();
				virtual ~IShaderPipeline() = default;

				virtual void addStage(ShaderType stage, const char* shaderSource) = 0;
				virtual void build() = 0;

				virtual void use() const = 0;

				virtual void setUniform1(const std::string& name, int a) const = 0;
				virtual void setUniform2(const std::string& name, int a, int b) const = 0;
				virtual void setUniform3(const std::string& name, int a, int b, int c) const = 0;
				virtual void setUniform4(const std::string& name, int a, int b, int c, int d) const = 0;

				virtual void setUniform1(const std::string& name, float a) const = 0;
				virtual void setUniform2(const std::string& name, float a, float b) const = 0;
				virtual void setUniform3(const std::string& name, float a, float b, float c) const = 0;
				virtual void setUniform4(const std::string& name, float a, float b, float c, float d) const = 0;

				virtual void setVec2(const std::string& name, const Vector2& data) const = 0;
				virtual void setVec3(const std::string& name, const Vector3& data) const = 0;
				virtual void setMat4(const std::string& name, const Matrix4x4& mat) const = 0;

				virtual void bindAttributeLocation(const std::string& attribName, int index) = 0;
				virtual int retrieveAttributeLocation(const std::string& attribName) = 0;
			};
		}
	}
}
