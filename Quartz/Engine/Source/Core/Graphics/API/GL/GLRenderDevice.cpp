#include <Quartz/Core/Graphics/API/GL/GLRenderDevice.hpp>
#include <Quartz/Core/Graphics/API/BufferLayout.hpp>

using namespace qz::gfx::api::gl;
using namespace qz::gfx::api;

void GLRenderDevice::create()
{
	glGenVertexArrays(1, &m_vao);
}

VertexBufferHandle GLRenderDevice::createVertexBuffer(BufferLayout layout)
{
	VertexBufferHandle handle = m_vertexBufferHandles.allocate();
	m_vertexBuffers[handle.get()].create();
    
	return handle;
}

void GLRenderDevice::setBufferData(VertexBufferHandle buffer, float *data, std::size_t sizebytes)
{
	m_vertexBuffers[buffer.get()].bufferData(data, sizebytes);
}

void GLRenderDevice::drawArrays(std::size_t first, std::size_t count)
{
	glBindVertexArray(m_vao);
	
	for (int i = 0; i < NUM_STREAMS; ++i)
	{
		const VertexStream& stream = m_vertexStreams[i];
		
		if (stream.active)
		{
			GLVertexBuffer& buffer = m_vertexBuffers[stream.buffer.get()];
			buffer.bind();
			glEnableVertexAttribArray(i);
            
			glDisableVertexAttribArray(i);
		}
	}
    
	glDrawArrays(GL_TRIANGLES, static_cast<GLint>(first), static_cast<GLsizei>(count));
	glBindVertexArray(0);
}

void GLRenderDevice::setVertexBufferStream(VertexBufferHandle buffer, int streamId, int stride, int offset)
{
	VertexStream& stream = m_vertexStreams[streamId];
	stream.buffer = buffer;
	stream.stride = stride;
	stream.offset = offset;
	stream.active = true;
}