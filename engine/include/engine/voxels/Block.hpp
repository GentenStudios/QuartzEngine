#pragma once

#include <engine/core/Core.hpp>

#include <functional>
#include <unordered_map>

namespace phx
{
	namespace voxels
	{
		using BlockCallback = std::function<void()>;

		/// @brief This defines what state of matter the block is
		enum class BlockType
		{
			GAS,		///< Gas Blocks are, for example, Air, or Oxygen if implemented.
			LIQUID,		///< Fluid Liquid Dynamics are applied to these blocks.
			SOLID,		///< Generic Stable Block, used for most things.
			WATER,		///< Water as a fundamental type as it needs to be specially done.
			OBJECT,		///< Things like Entities and objects that like transparent turds.
		};

		class RegistryBlock
		{
		public:
			RegistryBlock();
			RegistryBlock(std::string blockID, std::string blockName, int initialHP);
			RegistryBlock(const RegistryBlock& other) = default;

			~RegistryBlock();

			const std::string& getBlockID() const { return m_blockID; }
			const std::string& getBlockName() const { return m_blockName; }

			void setPlaceCallback(BlockCallback& callback);
			void setBreakCallback(BlockCallback callback);

			const BlockCallback& getPlaceCallback() const { return m_onPlaceCallback; }
			const BlockCallback& getBreakCallback() const { return m_onBreakCallback; }

			int initialHP() const { return m_initialHealthPoints; }
			
		private:
			std::string m_blockID;
			std::string m_blockName;

			BlockCallback m_onPlaceCallback;
			BlockCallback m_onBreakCallback;

			unsigned int m_initialHealthPoints;
		};

		class BlockLibrary
		{
		public:
			static BlockLibrary* get();
			
			void init(const RegistryBlock& unknownBlock);

			void registerBlock(const RegistryBlock& block);
			
			const RegistryBlock& requestBlock(const std::string& blockID);

		private:
			BlockLibrary() {}
			~BlockLibrary() {}

			std::unordered_map<std::string, RegistryBlock> m_registeredBlocks;
		};
	}
}