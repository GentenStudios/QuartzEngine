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

#include <Quartz/Core/QuartzPCH.hpp>
#include <Quartz/Core/Graphics/IWindow.hpp>
#include <Quartz/Core/Platform/GLWindow.hpp>
#include <Quartz/Core/Graphics/ContextManager.hpp>
#include <Quartz/Core/Engine.hpp>

using namespace qz::gfx;

IWindow* IWindow::requestWindow(const std::string& title, const unsigned int width, const unsigned int height, WindowFlags flags)
{
	if (!Engine::instance()->graphicsReady())
	{
		LFATAL("A window is being created without initialization of Quartz's Graphics subsystem. \n"
			"Please initialize the graphics subsystem through the Engine class.");

		exit(EXIT_FAILURE);
	}

	RenderingAPI renderingAPI = ContextManager::getRenderingAPI();

	switch (renderingAPI)
	{
	case RenderingAPI::OPENGL:
		return new api::gl::GLWindow(title, width, height, flags);
	
	default:
		return nullptr;
	}
}

void IWindow::destroyWindow(IWindow* window)
{
	window->close();

	delete window;
}

qz::Vector2 IWindow::requestPrimaryMonitorResolution()
{
	SDL_DisplayMode dm;
	SDL_GetCurrentDisplayMode(0, &dm);

	return {
		static_cast<float>(dm.w),
		static_cast<float>(dm.h)
	};
}
