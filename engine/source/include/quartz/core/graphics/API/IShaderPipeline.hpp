// Copyright 2019 Genten Studios
// 
// Redistribution and use in source and binary forms, with or without modification, are permitted provided that the 
// following conditions are met:
// 
// 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the 
// following disclaimer.
// 
// 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the 
// following disclaimer in the documentation and/or other materials provided with the distribution.
// 
// 3. Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote 
// products derived from this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED 
// WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A 
// PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY 
// DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, 
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER 
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR 
// OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH 
// DAMAGE.

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

				virtual void addStage(ShaderType stage, const std::string& shaderSource) = 0;
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

