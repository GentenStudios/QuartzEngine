#pragma once

#include <quartz/core/Core.hpp>
#include <quartz/core/graphics/API/IStateManager.hpp>
#include <quartz/core/graphics/API/gl/GLBuffer.hpp>

#include <vector>

namespace qz
{
	namespace gfx
	{
		namespace api
		{
			namespace gl
			{
				class QZ_API GLStateManager : public IStateManager
				{
				public:
					GLStateManager();
					~GLStateManager();

					GLStateManager(const GLStateManager& o) = default;
					GLStateManager& operator=(const GLStateManager& o) = default;
					GLStateManager(GLStateManager&& o) noexcept;
					GLStateManager& operator=(GLStateManager&& o) noexcept;

					void bind() const override;
					void unbind() const override;

					GraphicsResource<IBuffer> retrieveBuffer(unsigned int index = 0) override;

					void attachBuffer(GraphicsResource<IBuffer> buffer) override;
					void attachBufferLayout(const BufferLayout& bufferLayout, GraphicsResource<IShaderPipeline> shader) override;

					void render(unsigned int start, unsigned int count) const override;

				private:
					unsigned int m_id;
					
					std::vector<GraphicsResource<IBuffer>> m_buffers;
				};
			}
		}
	}
}
