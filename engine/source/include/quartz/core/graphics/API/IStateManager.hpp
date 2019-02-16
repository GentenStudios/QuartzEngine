#pragma once

#include <quartz/core/Core.hpp>

#include <quartz/core/graphics/API/GraphicsResource.hpp>
#include <quartz/core/graphics/API/IBuffer.hpp>
#include <quartz/core/graphics/API/BufferLayout.hpp>
#include <quartz/core/graphics/API/IShaderPipeline.hpp>

namespace qz
{
	namespace gfx
	{
		namespace api
		{
			class QZ_API IStateManager
			{
			public:
				static GraphicsResource<IStateManager> generateStateManager();
				virtual ~IStateManager() = default;

				virtual void bind() const = 0;
				virtual void unbind() const = 0;

				virtual GraphicsResource<IBuffer> retrieveBuffer(unsigned int index = 0) = 0;

				virtual void attachBuffer(GraphicsResource<IBuffer> buffer) = 0;
				virtual void attachBufferLayout(const BufferLayout& bufferLayout, GraphicsResource<IShaderPipeline> shader) = 0;

				virtual void render(unsigned int start, unsigned int count) const = 0;
			};
		}
	}
}
