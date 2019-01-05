#pragma once

#include <engine/core/Core.hpp>

#include <functional>
#include <unordered_map>

namespace phx
{
	namespace voxels
	{
		using BlockCallback = std::function<void()>;
		using InteractionCallback = std::function<void(int hp)>;

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
			RegistryBlock() = delete;
			RegistryBlock(std::string blockID, std::string blockName, int initialHP, BlockType blockType);
			RegistryBlock(const RegistryBlock& other) = default;

			~RegistryBlock() = default;

			const std::string& getBlockID() const;
			const std::string& getBlockName() const;
			BlockType getBlockType() const;

			void setPlaceCallback(const BlockCallback& callback);
			void setBreakCallback(const BlockCallback& callback);
			void setInteractLeftCallback(const InteractionCallback& callback);
			void setInteractRightCallback(const InteractionCallback& callback);

			const BlockCallback& getPlaceCallback() const;
			const BlockCallback& getBreakCallback() const;
			const InteractionCallback& getInteractLeftCallback() const;
			const InteractionCallback& getInteractRightCallback() const;

			const std::vector<std::string>& getBlockTextures() const;
			void setBlockTextures(const std::vector<std::string>& textures);

			int getInitialHP() const;

		private:
			std::string m_blockID;
			std::string m_blockName;
			BlockType m_blockType;

			std::vector<std::string> m_blockTextures;

			BlockCallback m_onPlaceCallback;
			BlockCallback m_onBreakCallback;

			InteractionCallback m_interactLeftCallback;
			InteractionCallback m_interactRightCallback;

			unsigned int m_initialHealthPoints;
		};

		class BlockInstance
		{
		public:
			BlockInstance();
			BlockInstance(const std::string& blockID);
			BlockInstance(const BlockInstance& other) = default;
			BlockInstance(BlockInstance&& other) = default;

			~BlockInstance() = default;

			unsigned int getHitpoints() const;
			void setHitpoints(unsigned int hitpoints);

			const std::string& getBlockName() const;
			void setBlockName(const std::string& name);

			const std::string& getBlockID() const;
			BlockType getBlockType() const;

			const std::vector<std::string>& getBlockTextures() const;

		private:
			unsigned int m_hitpoints;

			std::string m_blockID;
			std::string m_blockName;
			BlockType m_blockType;
		};

		class BlockLibrary
		{
		public:
			static BlockLibrary* get();
			
			void init();

			void registerBlock(const RegistryBlock& block);
			
			const RegistryBlock& requestBlock(const std::string& blockID) const;

		private:
			BlockLibrary() = default;
			BlockLibrary(const BlockLibrary& other) = default;
			BlockLibrary(BlockLibrary&& other) = default;

			~BlockLibrary() = default;

			std::unordered_map<std::string, RegistryBlock> m_registeredBlocks;
		};
	}
}