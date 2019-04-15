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

#include <Sandbox/Sandbox.hpp>

#include <Quartz.hpp>
#include <glad/glad.h>

using namespace sandbox;

Sandbox::Sandbox()
{
	using namespace qz::gfx;
	const auto size = IWindow::requestPrimaryMonitorResolution();
	m_window = IWindow::requestWindow("test", static_cast<uint>(size.x), static_cast<uint>(size.y), WindowFlags::WINDOW_VSYNC | WindowFlags::WINDOW_FULLSCREEN);
	LDEBUG("WElcome to sandbox!");
}

Sandbox::~Sandbox()
{
	qz::gfx::IWindow::destroyWindow(m_window);
}

void Sandbox::run()
{
	while (m_window->isRunning())
	{
		m_window->startFrame();

		glClearColor(0.3f, 0.7f, 0.9f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT);

		m_window->endFrame();
	}
}

int main(int argc, char** argv)
{
	using namespace qz;

	Engine::instance()->initialize(EngineOptions::INIT_EVERYTHING, { "quartz.log", utils::LogVerbosity::DEBUG, gfx::RenderingAPI::OPENGL });

	auto time = Measure<>::execution([]()
	{
		for (int i = 0; i < 10000; ++i)
			LDEBUG("This is an amazing debug message: ", i);
	});

	LDEBUG("It takes, ", time, " milliseconds to push 10k log messages.");
	LDEBUG("It takes, ", time / 10000.f, " milliseconds to push a single log message.");

	//Sandbox* application = new Sandbox();
	//application->run();
	//delete application;

	Engine::instance()->shutdown();

	return 0;
}
