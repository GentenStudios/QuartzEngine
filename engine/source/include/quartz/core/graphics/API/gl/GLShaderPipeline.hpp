#pragma once

#include <quartz/core/Core.hpp>
#include <quartz/core/math/Math.hpp>
#include <quartz/core/graphics/API/gl/GLCommon.hpp>
#include <quartz/core/graphics/API/IShaderPipeline.hpp>

#include <vector>
#include <string>

namespace qz
{
	namespace gfx
	{
		namespace api
		{
			namespace gl
			{
				class QZ_API GLShaderPipeline : public IShaderPipeline
				{
				public:
					GLShaderPipeline();
					~GLShaderPipeline();

					GLShaderPipeline(const GLShaderPipeline& o) = default;
					GLShaderPipeline& operator=(const GLShaderPipeline& o) = default;

					GLShaderPipeline(GLShaderPipeline&& o) noexcept;
					GLShaderPipeline& operator=(GLShaderPipeline&& o) noexcept;

					void addStage(ShaderType stage, const char* shaderSource) override;
					void build() override;

					void use() const override;

					void setUniform1(const std::string& name, int a) const override;
					void setUniform2(const std::string& name, int a, int b) const override;
					void setUniform3(const std::string& name, int a, int b, int c) const override;
					void setUniform4(const std::string& name, int a, int b, int c, int d) const override;

					void setUniform1(const std::string& name, float a) const override;
					void setUniform2(const std::string& name, float a, float b) const override;
					void setUniform3(const std::string& name, float a, float b, float c) const override;
					void setUniform4(const std::string& name, float a, float b, float c, float d) const override;

					void setVec2(const std::string& name, math::vec2& data) const override;
					void setVec3(const std::string& name, math::vec3& data) const override;
					void setMat4(const std::string& name, const math::mat4& mat) const override;

					void bindAttributeLocation(const std::string& attribName, int index) override;
					int retrieveAttributeLocation(const std::string& attribName) override;

				private:
					unsigned int m_id;

					std::vector<unsigned int> m_shaders;
				};
			}
		}
	}
}
