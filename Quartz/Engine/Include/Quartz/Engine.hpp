#pragma once

#include <Quartz/Core.hpp>

#include <string>

namespace qz
{
	enum class EngineFlags : uint
	{
		INIT_GRAPHICS   = 1 << 0,
		INIT_THREADING  = 1 << 1,
		INIT_LOGGING    = 1 << 2,
		INIT_EVERYTHING = INIT_GRAPHICS | INIT_THREADING | INIT_LOGGING,
	};

	enum class EngineStatus : bool
	{
		READY       = true,
		UNAVAILABLE = false,
	};

	struct EngineInitData
	{
		std::string appName;
		std::string dataDir;
	};

	class Engine
	{
	public:
		Engine();
		~Engine();

		// Yes, this is a singleton...
		static Engine* instance();

		void init(EngineFlags flags, EngineInitData initData);
		void destroy();

		QZ_FORCE_INLINE EngineStatus getThreadingStatus() const
		{
			return static_cast<EngineStatus>(m_threadingAllowed);
		}

		QZ_FORCE_INLINE EngineStatus getGraphicsStatus() const
		{
			return static_cast<EngineStatus>(m_graphicsInit);
		}
		const std::string& getAppName() const { return m_appName; }
		const std::string& getDataDirectory() const { return m_dataDir; }

	private:
		bool m_threadingAllowed = false;
		bool m_graphicsInit     = false;

		std::string m_appName;
		std::string m_dataDir;
	};
} // namespace qz

ENABLE_BITWISE_OPERATORS(qz::EngineFlags);
