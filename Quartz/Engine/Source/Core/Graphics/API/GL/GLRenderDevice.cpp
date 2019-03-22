#include <Quartz/Core/Graphics/API/GL/GLRenderDevice.hpp>
#include <Quartz/Core/Graphics/API/InputLayout.hpp>

using namespace qz::gfx::api::gl;
using namespace qz::gfx::api;

void GLRenderDevice::create()
{
	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);
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

void GLRenderDevice::drawArrays(std::size_t first, std::size_t count)
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