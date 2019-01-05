#pragma once

#include <engine/core/graphics/gl/VertexArray.hpp>
#include <engine/core/graphics/gl/VertexBuffer.hpp>
#include <engine/core/graphics/gl/ShaderPipeline.hpp>

#include <engine/core/math/Vector3.hpp>

namespace phx 
{
	namespace gfx
	{

		/**
		 * @brief Represents a single vertex in 3D space.
		 */
		struct Vertex3D 
		{
			/// @brief The position of this vertex.
			Vector3 position;

			/// @brief The color of this vertex. RGB format, where each component is in the range 0 -> 1
			Color3 color;

			/**
			 * @brief Set all components of this vertex.
			 */
			Vertex3D(const Vector3& pos, const Color3& col)
				: position(pos), color(col) {}
		};

		/**
		 * @brief Represents a batch renderer - e.g. `draw` calls modify a buffer of vertices and then is drawn with
		 *        a single draw call.
		 */
		class BatchRenderer
		{
		public:
			/**
			 * @brief Initalize all CPU and GPU resources for this batch renderer - once this has been called, all other methods are safe to call.
			 *
			 * @param numVertices The maximum number of vertices in the batch
			 * @param numIndices The maximum number of indices in the batch
			 * @param shader The shader that will be used in conjunction with this renderer.
			 */
			void create(int numVertices, int numIndices, gl::ShaderPipeline& shader);
			
			/**
			 * @brief Free any GPU/CPU resources used by the renderer. If this is called the batchRenderer is 
			 *        unusable until `create` is called again
			 */
			void destroy();

			/**
			 * @brief Open the GPU buffer for writing (aka so it can be drawn to). Cannot be called if the buffer is already open.
			 */
			void openBuffer();

			/**
			 * @brief Close the GPU buffer for writing (aka it can no longer be drawn to).
			 *        Cannot be called if the buffer is already in a closed state.
			 */
			void closeBuffer();

			/**
			 * @brief Draw the batch to the screen. Also clears the current batch ready for rendering afresh.
			 */
			void draw();

			/**
			 * @brief Add a vertex to the current batch.
			 *
			 * @param vertex The vertex to add to this batch.
			 */
			void addVertex(const Vertex3D& vertex);

			/**
			 * @brief Add a index to the current batch. Indices allow the same vertices to be referenced multiple times.
			 *
			 * @param index The index to add to this batch.
			 */
			void addIndex(unsigned index);

			/**
			 * @brief Get if the current batch is ready to be drawn to, for example the buffer is open etc...
			 *        If this call returns true then it is safe to call addVertex(...) and addIndex(...)
			 *
			 * @return Whether the current batch can be modified.
			 */
			bool isReadyForDrawing() const;

		private:
			/// @brief The VAO for this renderer.
			gl::VertexArray* m_vao = nullptr;

			/// @brief The VBO for this renderer. The VBO contains all packed data (e.g. position, color etc..).
			gl::VertexBuffer* m_vbo = nullptr;

			/// @brief The element buffer object for this renderer.
			gl::VertexBuffer* m_ibo = nullptr;

			/// @brief Points to the valid memory location of the vertex buffer data, ONLY IF it is accessed and the buffer is open (e.g. isReadyForDrawing() returns true)
			Vertex3D* m_vertexBuffer = nullptr;

			/// @brief Points to the valid memory location of the element buffer data, ONLY IF it is accessed and the buffer is open (e.g. isReadyForDrawing() returns true)
			unsigned int* m_indexBuffer = nullptr;

			/// @brief The number of indices that have been added to this batch.
			std::size_t m_indexCount = 0;

			/// @brief Have the VBO and IBO been mapped to `m_vertexBuffer` and `m_indexBuffer`? If so the buffer is open. (set to true in openBuffer() and set to false in closeBuffer())
			bool m_bufferIsOpen;
		};

	}
}