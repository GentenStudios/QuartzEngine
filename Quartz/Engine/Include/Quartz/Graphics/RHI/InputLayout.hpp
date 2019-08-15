// Copyright 2019 Genten Studios
// 
// Redistribution and use in source and binary forms, with or without modification, are permitted provided that the 
// following conditions are met:
// 
// 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the 
// following disclaimer.
// 
// 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the 
// following disclaimer in the documentation and/or other materials provided with the distribution.
// 
// 3. Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote 
// products derived from this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED 
// WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A 
// PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY 
// DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, 
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER 
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR 
// OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH 
// DAMAGE.

#pragma once

#include <Quartz/Graphics/RHI/DataTypes.hpp>

#include <vector>
#include <string>
#include <initializer_list>

namespace qz
{
	namespace gfx
	{
		namespace rhi
		{
			/// @brief Represents the type of a vertex element in a shader InputLayout.
			struct VertexElementType
			{
				/// @brief The type of the entry.
				DataType type;

				// #todo: This could probably be inferred from the type.
				/// @brief The number of components of this entry (e.g. Vec3 has 3, Vec2 has 1, float has 1 etc...)
				int      numComponents;

				/// @brief Represents a vertex element that is a 2 component vector of floats.
				static const VertexElementType Vec2f;

				/// @brief Represents a vertex element that is a 3 component vector of floats.
				static const VertexElementType Vec3f;

				/// @brief Represents a vertex element that is a 4 component vector of floats.
				static const VertexElementType Vec4f;
			};

			/// @brief Represents a vertex element in a shader input layout/buffer layout.
			struct VertexElement
			{
				/// @brief The type of this element.
				VertexElementType type;

				/// @brief The (index of) the vertex stream that this element sits in.
				int               streamIndex;

				/// @brief The shader attribute index of this element.
				int               attributeIndex;

				/// @brief The offset of this element in the buffer (in bytes).
				int               offset;

				// #todo: Maybe this is too OpenGL specific?
				/// @brief Is this element normalized or not?
				bool              normalized;
			};

			/// @brief Describes the layout of data that will be sent to a shader.
			class InputLayout
			{
			public:
				/**
				 * @brief Constructs the InputLayout, copying the elements from the given initalizer list.
				 */
				InputLayout(std::initializer_list<VertexElement> init);
				
				/**
				 * @brief Default constructs this InputLayout to have to vertex elements.
				 */
				InputLayout() {}

				/// @brief The list of elements in this input layout.
				std::vector<VertexElement> elements;
			};
		}
	}
}

