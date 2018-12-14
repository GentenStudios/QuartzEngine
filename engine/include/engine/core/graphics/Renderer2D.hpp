#pragma once

#include <engine/core/graphics/BatchRenderer.hpp>
#include <engine/core/math/Matrix4x4.hpp>
#include <engine/core/math/Vector2.hpp>

namespace phx
{
	namespace gfx
	{
		/**
		 * A generic 2D renderer.
		 */
		class Renderer2D
		{
		public:
			/**
			 * @brief Initalizes the renderer.
			 *
			 * @param projectionMatrix The projection matrix for the renderer. Normally for 2D this is a orthographic projection.
			 */
			Renderer2D(const Matrix4x4& projectionMatrix);

			/**
			 * @brief Makes the renderer ready for any draw calls.
			 */
			void begin();

			/**
			 * @brief Draw the stored contents of the renderer. Should be called after `end()`
			 */
			void draw();

			/**
			 * @brief Finalises renderering for this frame. Should only be called when after all draw calls and before the actual `draw()` call. 
			 */
			void end();

			/**
			 * @brief Draw filled rectangle with the specified color. Should be called between a `begin()` and a `end()` call.
			 *
			 * @param position The position of the top-left corner of the rectangle
			 * @param width The width of the rectangle
			 * @param height The height of the rectangle
			 * @param color The color of the rectangle
			 */
			void fillRectangle(const Vector2& position, float width, float height, const Color3& color);

			/**
			 * @brief Draw a filled circle. Should be called between a `begin()` and `end()` call.
			 *
			 * @param position The centre position of the circle.
			 * @param radius The radius of the circle
			 * @param noPoints The number of points that makes up the circle. The higher this number the more accurate the circle, but lower performance.
			 * @param color The color of the circle.
			 */
			void fillCircle(const Vector2& position, float radius, size_t noPoints, const Color3& color);

		private:
			/// @brief The batch renderer used internally by the renderer.
			BatchRenderer m_batchRenderer;

			/// @brief The projection matrix for this renderer.
			Matrix4x4 m_projection;

			/// @brief The shader that will be used in conjection with the renderer.
			gl::ShaderPipeline m_shader;

			/// @brief The offset of the current index in this batch. Used when calculating the current index for any vertex set.
			size_t m_indexOffset;
		};
	}
}