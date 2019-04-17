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

#include <Quartz/Core/Core.hpp>
#include <Quartz/Core/Utilities/Logger.hpp>
#include <Quartz/Core/Graphics/ContextManager.hpp>
#include <Quartz/Core/Utilities/EnumTools.hpp>

namespace qz
{
	struct ApplicationRequirements
	{
		std::string logFile;
		utils::LogVerbosity logVerbosity;

		gfx::RenderingAPI renderAPI = gfx::RenderingAPI::OPENGL;

		ApplicationRequirements(const std::string& logFile, utils::LogVerbosity logVerb = utils::LogVerbosity::INFO, gfx::RenderingAPI renderAPI = gfx::RenderingAPI::OPENGL) :
			logFile(logFile), logVerbosity(logVerb), renderAPI(renderAPI)
		{}
	};

	enum class EngineConfigFlags : uint
	{
		ALLOW_THREADS = 1 << 0,
		INIT_LOGGER = 1 << 1,
		INIT_GRAPHICS = 1 << 2,

		INIT_EVERYTHING = ALLOW_THREADS | INIT_LOGGER | INIT_GRAPHICS,
		INIT_MINIMAL = ALLOW_THREADS | INIT_LOGGER,
	};

	class Engine
	{
	public:
		static Engine* instance();

		void initialize(EngineConfigFlags flags, const ApplicationRequirements& requirements);
		void shutdown();

		bool threadsAllowed() const { return m_threadsAllowed; }
		bool graphicsReady() const { return m_graphicsInitialized; }

	private:
		Engine() {}
		~Engine() {}

		bool m_threadsAllowed = false;
		bool m_graphicsInitialized = false;
	};
}

ENABLE_BITMASK_OPERATORS(qz::EngineConfigFlags)
