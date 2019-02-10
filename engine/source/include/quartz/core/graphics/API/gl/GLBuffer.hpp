#pragma once

#include <quartz/core/Core.hpp>
#include <quartz/core/graphics/API/IBuffer.hpp>
#include <quartz/core/graphics/API/gl/GLCommon.hpp>

namespace qz
{
	namespace gfx
	{
		namespace api
		{
			namespace gl
			{
				class QZ_API GLBuffer : public IBuffer
				{
				public:
					GLBuffer(BufferTarget target, BufferUsage usage);

					~GLBuffer();

					GLBuffer(const GLBuffer& o) = default;
					GLBuffer& operator=(const GLBuffer& o) = default;

					GLBuffer(GLBuffer&& o) noexcept;
					GLBuffer& operator=(GLBuffer&& o) noexcept;

					void bind() override;
					void unbind() override;

					void resize(unsigned int size) override;
					void setData(unsigned int size, const void* data) override;

					void releaseDataPointer() override;

				protected:
					void* retrievePointerInternal() override;

				private:
					unsigned int m_id = 0;
					unsigned int m_size = 0;

					GLenum m_target;
					GLenum m_usage;
				};
			}

		}
	}
}
