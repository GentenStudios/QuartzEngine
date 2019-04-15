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

#include <Quartz/Core/Engine.hpp>

using namespace qz;

Engine* Engine::instance()
{
	static Engine engine;
	return &engine;
}

void Engine::initialize(EngineOptions flags, const ApplicationRequirements& requirements)
{
	SDL_SetMainReady();
	SDL_Init(SDL_INIT_EVERYTHING);

	if (hasFlag(flags, EngineOptions::ALLOW_THREADS))
		m_threadsAllowed = true;

	if (hasFlag(flags, EngineOptions::INIT_GRAPHICS))
	{
		// There will be more here, but first we have to ya know... actually have the code for it.
		// You could argue lets save this for a later date, but it's good to get the architecture in
		// early so we don't struggle later.
		m_graphicsInitialized = true;
		gfx::ContextManager::setRenderingAPI(requirements.renderAPI);
	}

	if (hasFlag(flags, EngineOptions::INIT_LOGGER))
	{
		utils::LogConfigurations logFlags = utils::LogConfigurations::LOG_TO_FILE | utils::LogConfigurations::USE_COLORS;

		if (m_threadsAllowed)
			logFlags |= utils::LogConfigurations::USE_THREADS;

		utils::Logger::instance()->initialize(requirements.logFile, requirements.logVerbosity, logFlags);
	}
}

void Engine::shutdown()
{
	SDL_Quit();

	utils::Logger::instance()->destroy();
}
