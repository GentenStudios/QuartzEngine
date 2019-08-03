// Copyright 2019 Genten Studios
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// 1. Redistributions of source code must retain the above copyright notice,
// this list of conditions and the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above copyright notice,
// this list of conditions and the following disclaimer in the documentation
// and/or other materials provided with the distribution.
//
// 3. Neither the name of the copyright holder nor the names of its contributors
// may be used to endorse or promote products derived from this software without
// specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.

#pragma once

#include <cstddef>
#include <functional>
#include <vector>

#include <Quartz/Math/Math.hpp>
#include <Quartz/Voxels/Blocks.hpp>

namespace qz
{
	namespace voxels
	{
		class Chunk
		{
		  public:
			typedef std::function<BlockType*(std::size_t, std::size_t,
			                                 std::size_t)>
			    GeneratorFunction;

		  private:
			std::vector<BlockType*> m_voxelData;

		  public:
			void fill(const std::size_t               chunkSize,
			          const Chunk::GeneratorFunction& generator);
		};

		class Terrain
		{
		  private:
			std::size_t              m_chunkSize;
			Chunk::GeneratorFunction m_generatorFunction;
			std::vector<Chunk>       m_loadedChunks;

		  public:
			Terrain(std::size_t                     chunkSize,
			        const Chunk::GeneratorFunction& generator);

			void tick(Vector3 streamCenter);
		};

	} // namespace voxels
} // namespace qz
