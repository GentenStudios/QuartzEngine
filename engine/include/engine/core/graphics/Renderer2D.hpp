#pragma once

#include <engine/core/graphics/BatchRenderer.hpp>
#include <engine/core/math/Matrix4x4.hpp>
#include <engine/core/math/Vector2.hpp>

namespace phx
{
	namespace gfx
	{
		class Renderer2D
		{
		public:
			Renderer2D(const Matrix4x4& projectionMatrix);

			void begin();
			void draw();
			void end();

			void fillRectangle(const Vector2& position, float width, float height, const Color3& color);
			void fillCircle(const Vector2& position, float radius, size_t noPoints, const Color3& color);

		private:
			BatchRenderer m_batchRenderer;
			Matrix4x4 m_projection;
			gl::ShaderPipeline m_shader;
			size_t m_indexOffset;
		};
	}
}