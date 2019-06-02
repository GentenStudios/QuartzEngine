#include <Quartz/Graphics/RHI/OpenGL/GLRenderDevice.hpp>
#include <Quartz/Graphics/RHI/InputLayout.hpp>
#include <Quartz/Graphics/ImGuiExtensions.hpp>

#include <imgui/imgui.h>

#include <cassert>

using namespace qz::gfx::rhi::gl;
using namespace qz::gfx::rhi;

bool GLRenderDevice::isHandleValid(VertexBufferHandle handle)
{
	return m_vertexBufferHandles.isValid(handle);
}

bool GLRenderDevice::isHandleValid(ShaderPipelineHandle handle)
{
	return m_shaderHandles.isValid(handle);
}

bool GLRenderDevice::isHandleValid(UniformHandle handle)
{
	return m_uniformHandleAllocator.isValid(handle);
}

bool GLRenderDevice::isHandleValid(TextureHandle handle)
{
	return m_textureHandleAllocator.isValid(handle);
}

void GLRenderDevice::freeTexture(TextureHandle texture)
{
	m_textures[texture.get()].free();
	m_textureHandleAllocator.free(texture);
}

void GLRenderDevice::freeUniform(UniformHandle uniform)
{
	// nb: no specific code needed here to deallocate uniforms.

	m_uniformHandleAllocator.free(uniform);
}

void GLRenderDevice::freeVertexBuffer(VertexBufferHandle buffer)
{
	m_vertexBuffers[buffer.get()].free();
	m_vertexBufferHandles.free(buffer);
}

void GLRenderDevice::freeShaderPipeline(ShaderPipelineHandle shader)
{
	m_shaders[shader.get()].free();
	m_shaderHandles.free(shader);
}

Uniform::Uniform()
	: type(UniformType::INVALID), location(-1), name(nullptr)
{
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

			// Maybe should use setUniformValue here? (instead of manually updating GL)
			// allthough a) this is not permenant (and really should move when the meta
			// query API is implemented.
			// b) ImGui will modify the uniform.userdata values in place so this does the
			// same job as setUniformValue anyway.
			switch (uniform.type)
			{
			case UniformType::COLOR3:
				if (ImGui::ColorPicker3(uniform.name, uniform.userdata.vec3))
				{
					glUniform3f(uniform.location, uniform.userdata.vec3[0], uniform.userdata.vec3[1], uniform.userdata.vec3[2]);
				}
				break;
			case UniformType::MAT4:
				if(ImGui::InputMatrix4x4(uniform.name, &uniform.userdata.mat4))
				{
					glUniformMatrix4fv(uniform.location, 1, GL_FALSE, uniform.userdata.mat4.elements);
				}
				break;
			case UniformType::VEC2:
				if(ImGui::InputFloat2(uniform.name, uniform.userdata.vec2))
				{
					glUniform2f(uniform.location, uniform.userdata.vec3[0], uniform.userdata.vec3[1]);
				}
				break;
			case UniformType::VEC3:
				if(ImGui::InputFloat3(uniform.name, uniform.userdata.vec3))
				{
					glUniform3f(uniform.location, uniform.userdata.vec3[0], uniform.userdata.vec3[1], uniform.userdata.vec3[2]);
				}
				break;
			case UniformType::SAMPLER:
			case UniformType::INVALID:
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
			ralTypeToGLType(vertexElement.type.type), vertexElement.normalized ? GL_TRUE : GL_FALSE,
			stream.stride, (void*) (stream.offset + vertexElement.offset)
		);

		glEnableVertexAttribArray(attributeIndex);
	}
    
	shader.use();
	glDrawArrays(GL_TRIANGLES, static_cast<GLint>(first), static_cast<GLsizei>(count));
}

void GLRenderDevice::setShaderPipeline(ShaderPipelineHandle shader)
{
	assert(m_shaderHandles.isValid(shader));

	m_boundShader = shader;
}

void GLRenderDevice::setVertexBufferStream(VertexBufferHandle buffer, int streamId, int stride, int offset)
{
	assert(m_vertexBufferHandles.isValid(buffer));

	VertexStream& stream = m_vertexStreams[streamId];
	stream.buffer = buffer;
	stream.stride = stride;
	stream.offset = offset;
	stream.active = true;
}

UniformHandle GLRenderDevice::createUniform(ShaderPipelineHandle shaderHandle,const char* name, UniformType type)
{
	assert(m_shaderHandles.isValid(shaderHandle));

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
	assert(m_uniformHandleAllocator.isValid(uniform));

	const float* fdata = static_cast<const float*>(value);

	Uniform& uniformData = m_uniforms[uniform.get()];
	m_shaders[uniformData.shader.get()].use();

	switch (uniformData.type)
	{
	case UniformType::MAT4:
	{
		glUniformMatrix4fv(uniformData.location, num, GL_FALSE, fdata);

		Matrix4x4 m4;
		std::memcpy(m4.elements, fdata, 16*sizeof(float));
		uniformData.userdata.mat4 = m4;
		break;
	}
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
	case UniformType::INVALID:
		assert(!"Invalid shader value (cannot set)...");
	}
}

TextureHandle GLRenderDevice::createTexture(unsigned char* pixelData, std::size_t width, std::size_t height)
{
	TextureHandle handle = m_textureHandleAllocator.allocate();
	m_textures[handle.get()].create(pixelData, width, height);
	return handle;
}

void GLRenderDevice::setTexture(TextureHandle texture, int slot)
{
	assert(m_textureHandleAllocator.isValid(texture));

	// No need to bind the currently bound texture again.
	if(texture == m_boundTexture)
		return;

	GLTexture& texData = m_textures[texture.get()];

	GLCheck(glActiveTexture(static_cast<GLenum>(GL_TEXTURE0 + slot)));
	GLCheck(glBindTexture(GL_TEXTURE_2D, texData.getID()))

	m_boundTexture = texture;
}
