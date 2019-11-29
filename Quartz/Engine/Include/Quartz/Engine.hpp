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

