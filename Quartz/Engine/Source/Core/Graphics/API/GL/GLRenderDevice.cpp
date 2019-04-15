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

#include <Quartz/Core/Graphics/API/GL/GLRenderDevice.hpp>
#include <Quartz/Core/Graphics/API/InputLayout.hpp>

#include <imgui/imgui.h>
#include <cstring>

using namespace qz::gfx::api::gl;
using namespace qz::gfx::api;

Uniform::Uniform()
	: type(UniformType::INVALID), location(-1), name(nullptr)
{
	std::memset(userdata.vec2, 0, sizeof(userdata));
}

void GLRenderDevice::create()
{
	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 
}

void GLRenderDevice::showShaderDebugUI()
{
	ImGui::Begin("Shader Debug UI");

	if (ImGui::CollapsingHeader("Uniforms", ImGuiTreeNodeFlags_DefaultOpen))
	{
		for (std::size_t i = 0; i < m_uniformHandleAllocator.size(); i++)
		{
			Uniform& uniform = m_uniforms[i];
			GLShaderPipeline& shader = m_shaders[uniform.shader.get()];
			shader.use();

			switch (uniform.type)
			{
			case UniformType::COLOR3:
				if (ImGui::ColorPicker3(uniform.name, uniform.userdata.vec3))
				{
					glUniform3f(uniform.location, uniform.userdata.vec3[0], uniform.userdata.vec3[1], uniform.userdata.vec3[2]);
				}
				break;
			}
		}
	}

	ImGui::End();
}

VertexBufferHandle GLRenderDevice::createVertexBuffer()
{
	VertexBufferHandle handle = m_vertexBufferHandles.allocate();
	m_vertexBuffers[handle.get()].create();
    
	return handle;
}

ShaderPipelineHandle GLRenderDevice::createShaderPipeline(const std::string& shadersource, const InputLayout& inputLayout)
{
	ShaderPipelineHandle handle = m_shaderHandles.allocate();
	m_shaders[handle.get()].create(shadersource, inputLayout);

	return handle;
}

void GLRenderDevice::setBufferData(VertexBufferHandle buffer, float *data, std::size_t sizebytes)
{
	m_vertexBuffers[buffer.get()].bufferData(data, sizebytes);
}

void GLRenderDevice::draw(std::size_t first, std::size_t count)
{
	GLShaderPipeline& shader = m_shaders[m_boundShader.get()];
	InputLayout& inputLayout = shader.getInputLayout();

	for (const VertexElement& vertexElement : inputLayout.elements)
	{
		VertexStream& stream = m_vertexStreams[vertexElement.streamIndex];
		GLVertexBuffer& buffer = m_vertexBuffers[stream.buffer.get()];
		buffer.bind();

		GLuint attributeIndex = static_cast<GLuint>(vertexElement.attributeIndex);
		glVertexAttribPointer(
			attributeIndex, vertexElement.type.numComponents, 
			gfxToOpenGL(vertexElement.type.type), vertexElement.normalized ? GL_TRUE : GL_FALSE, 
			stream.stride, (void*) (stream.offset + vertexElement.offset)
		);

		glEnableVertexAttribArray(attributeIndex);
	}
    
	shader.use();
	glDrawArrays(GL_TRIANGLES, static_cast<GLint>(first), static_cast<GLsizei>(count));
}

void GLRenderDevice::setShaderPipeline(ShaderPipelineHandle shader)
{
	m_boundShader = shader;
}

void GLRenderDevice::setVertexBufferStream(VertexBufferHandle buffer, int streamId, int stride, int offset)
{
	VertexStream& stream = m_vertexStreams[streamId];
	stream.buffer = buffer;
	stream.stride = stride;
	stream.offset = offset;
	stream.active = true;
}

UniformHandle GLRenderDevice::createUniform(ShaderPipelineHandle shaderHandle,const char* name, UniformType type)
{
	GLShaderPipeline& shader = m_shaders[shaderHandle.get()];
	shader.use();

	UniformHandle handle = m_uniformHandleAllocator.allocate();
	Uniform& uniform = m_uniforms[handle.get()];
	uniform.location = GLCheck(glGetUniformLocation(shader.getID(), name));
	uniform.type = type;
	uniform.shader = shaderHandle;
	uniform.name = name;
	return handle;
}

void GLRenderDevice::setUniformValue(UniformHandle uniform, const void* value, int num)
{
	const float* fdata = static_cast<const float*>(value);

	Uniform& uniformData = m_uniforms[uniform.get()];
	m_shaders[uniformData.shader.get()].use();

	switch (uniformData.type)
	{
	case UniformType::MAT4:
		glUniformMatrix4fv(uniformData.location, num, GL_FALSE, fdata);
		break;
	case UniformType::VEC2:
		glUniform2f(uniformData.location, fdata[0], fdata[1]);
		std::memcpy(uniformData.userdata.vec2, value, sizeof(float) * 2);
		break;
	case UniformType::COLOR3:
	case UniformType::VEC3:
		glUniform3f(uniformData.location, fdata[0], fdata[1], fdata[2]);
		std::memcpy(uniformData.userdata.vec3, value, sizeof(float) * 3);
		break;
	case UniformType::SAMPLER:
		glUniform1i(uniformData.location, *(static_cast<const int*>(value)));
		std::memcpy(uniformData.userdata.vec4, value, sizeof(float) * 4);
		break;
	}
}

TextureHandle GLRenderDevice::createTexture(unsigned char* pixelData, int width, int height)
{
	TextureHandle handle = m_textureHandleAllocator.allocate();
	m_textures[handle.get()].create(pixelData, width, height);
	return handle;
}

void GLRenderDevice::setTexture(TextureHandle texture, int slot)
{
	GLTexture& texData = m_textures[texture.get()];

	GLCheck(glActiveTexture(GL_TEXTURE0 + slot));
	GLCheck(glBindTexture(GL_TEXTURE_2D, texData.getID()))
}
