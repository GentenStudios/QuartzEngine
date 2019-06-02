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

#include <Quartz/Utilities/Singleton.hpp>
#include <Quartz/Math/Math.hpp>

#include <list>
#include <unordered_map>

namespace qz
{
    namespace voxels
    {
		class BlockTextureAtlas
		{
		public:
			typedef int SpriteID;
			constexpr static SpriteID INVALID_SPRITE = -1;

			BlockTextureAtlas(std::size_t spriteWidth, std::size_t spriteHeight);
			BlockTextureAtlas();
			~BlockTextureAtlas();

			void           addTextureFile(const char* texturefilepath);
			void           patch();

			void           setSpriteWidth(std::size_t w);
			void           setSpriteHeight(std::size_t h);

			std::size_t    getSpriteWidth() const { return m_spriteWidth; }
			std::size_t    getSpriteHeight() const { return m_spriteHeight; }

			SpriteID       getSpriteIDFromFilepath(const char* filepath);

			std::size_t    getPatchedTextureWidth() const { return m_patchedTextureWidth; }
			std::size_t    getPatchedTextureHeight() const { return m_patchedTextureHeight; }

			unsigned char* getPatchedTextureData() const { return m_patchedTextureData; }

			RectAABB       getSpriteFromID(SpriteID spriteId) const;

		private:
			std::unordered_map<std::string, SpriteID> m_textureIDMap;
			std::size_t                               m_spriteWidth, m_spriteHeight;
			unsigned char*                            m_patchedTextureData;

			std::size_t                               m_patchedTextureWidth, m_patchedTextureHeight;
		};

		enum class BlockTypeCategory
		{
			AIR, SOLID, LIQUID
		};

		struct BlockType
		{
			const char* displayName;
			const char* id;

			BlockTypeCategory category;

			struct {
				BlockTextureAtlas::SpriteID top, bottom, left, right, front, back;

				void setAll(BlockTextureAtlas::SpriteID sprite)
				{
					top = bottom = left = right = front = back = sprite;
				}
			} textures;
		};

		class BlockRegistery : public utils::Singleton<BlockRegistery>
		{
		public:
			BlockType* registerBlock(BlockType blockInfo);
			BlockType* getBlockFromID(const char* id);

		private:
			// This is a std::list as we don't want to invalidate any pointers when resizing...
			// #todo (bwilks): Maybe use HandleAllocator for this as well??
			std::list<BlockType> m_blocks;
		};
    }
}
