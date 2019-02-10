#pragma once

#include <quartz/core/Core.hpp>
#include <quartz/core/graphics/API/GraphicsResource.hpp>

namespace qz
{
	namespace gfx
	{
		namespace api
		{
			enum class BufferUsage : int
			{
				STATIC,
				DYNAMIC
			};

			enum class BufferTarget : int
			{
				ARRAY_BUFFER,
				INDEX_BUFFER,
				TEXTURE_BUFFER,
				UNIFORM_BUFFER
			};

			class QZ_API IBuffer
			{
			public:
				static GraphicsResource<IBuffer> generateBuffer(BufferTarget target = BufferTarget::ARRAY_BUFFER, BufferUsage usage = BufferUsage::STATIC);

				virtual ~IBuffer() = default;

				virtual void bind() = 0;
				virtual void unbind() = 0;

				virtual void resize(unsigned int size) = 0;
				virtual void setData(unsigned int size, const void* data) = 0;

				template<typename T>
				T* retrieveDataPointer()
				{
					return static_cast<T*>(retrievePointerInternal());
				}

				virtual void releaseDataPointer() = 0;

			protected:
				virtual void* retrievePointerInternal() = 0;
			};
		}
	}
}
