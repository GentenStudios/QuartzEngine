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

#include <Quartz.hpp>
#include <Quartz/Core/Graphics/API/IRenderDevice.hpp>

namespace sandbox
{
	class Sandbox : public qz::Application
	{
	public:
		Sandbox();
		~Sandbox() = default;

		const ApplicationRequirements* getAppRequirements() override { return m_appRequirements; }
		void setAppData(qz::ApplicationData* appData) override { m_appData = appData; }

		void run() override;

		void onEvent(events::Event& event);
		bool onKeyPress(events::KeyPressedEvent& event);

	private:
		void showDebugUi();

		qz::ApplicationRequirements* m_appRequirements = nullptr;
		qz::ApplicationData* m_appData = nullptr;

		qz::gfx::FPSCamera* m_camera = nullptr;
		qz::gfx::api::IRenderDevice* m_renderDevice = nullptr;

		bool m_debugMode = false;
	};
}

inline qz::Application* qz::createApplication()
{
	return new sandbox::Sandbox();
}

