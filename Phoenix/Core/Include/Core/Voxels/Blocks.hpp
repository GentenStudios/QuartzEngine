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

#include <Quartz/Utilities/Singleton.hpp>

#include <string>
#include <vector>

namespace phoenix
{
	namespace voxels
	{
		typedef std::size_t BlockID;

		/// @brief Stores universal definition of a block
		struct RegisteredBlock
		{
			/** 
			 * @brief Stores unique ID to identify block for use in memory,
			 * should match location in registry
			 */
			BlockID blockId;
			/** 
			 * @brief Stores Unique name for use duing saving, should be in
			 * format mod:name eg "core:dirt"
			 */
			std::string uniqueName;
			/// @brief Stores human readable name for output to player ex "dirt"
			std::string displayName;

			RegisteredBlock(const std::string& unique, BlockID id,
			                const std::string& display);

			~RegisteredBlock();
		};

		/// @brief Stores universal block definitions
		class BlockRegistry : public qz::utils::Singleton<BlockRegistry>
		{
		private:
			std::vector<RegisteredBlock> m_blocks;

		public:
			BlockRegistry();

			/** 
			 * @brief Registers a block in the registry
			 * 
			 * @param uniqueName The blocks unique name, this is unique to the block and used on saves and loading lua
			 * @param displayName The human friendly name for the block seen ingame
			 * @return On success, returns the blocks ID in the registry, on failure a -1
			 */
			BlockID registerBlock(const std::string& uniqueName,
			                      const std::string& displayName);
			/** 
			 * @brief Get the Display name for a block in the registry
			 * 
			 * @param blockId the unique numberical block ID for the block you need
			 * @return Returns display name of the block as a string
			 */
			const std::string& getDisplayName(std::size_t blockId);
			/** 
			 * @brief Get the ID for a block in the registry
			 * 
			 * @param uniqueName The blocks unique name used during saves and lua loading
			 * @return Returns ID number as an int
			 */
			BlockID getBlockId(const std::string& uniqueName);
		};
	} // namespace voxels

} // namespace phoenix